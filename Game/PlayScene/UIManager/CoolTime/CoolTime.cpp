/*
* @file		CoolTime.h
* @brief	クールタイム
* @author	Morita
* @date		2024/05/20
*/
#include "pch.h"

#include "CoolTime.h"

CoolTime::CoolTime(UIManager* uiManager)
	:
	m_angle(360.0f),
	m_time(0.0f),
	m_coolTimeJudgement(false),
	m_ratio(100.0f),
	m_state(),
	m_uiManager(uiManager)
{
	//		回転シェーダーの生成
	m_rotataionShader = std::make_unique<UIRenderManager>();

	//		回転シェーダーの作製
	m_rotataionShader->Create(L"Resources/Texture/UI/CoolTime/CoolTime.png",
		L"Resources/Shader/CoolTime/CoolTimeVS.cso",
		L"Resources/Shader/CoolTime/CoolTimeGS.cso",
		L"Resources/Shader/CoolTime/CoolTimePS.cso",
		buffer,
		{ 270.0f, 0.0f }, { 0.6f, 0.6f });

	//		シェーダー描画マネージャーの生成
	m_shader = std::make_unique<UIRenderManager>();

	//		数字シェーダーの作製
	m_shader->Create(L"Resources/Texture/UI/CoolTime/cooltimeNumber.png",
		L"Resources/Shader/Number/NumberVS.cso",
		L"Resources/Shader/Number/NumberGS.cso",
		L"Resources/Shader/Number/NumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 0.3f, 0.3f });
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		ウィンドウサイズを設定する
	circleBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	circleBuffer.rotationMatrix = m_rotataionShader->GetRotationMatrix();

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

	//		何もない状態
	m_state = State::None;
}

void CoolTime::Update(PlayerInformation* playerInformation)
{
	//		クールタイムが発生していない場合処理を行う
	if (!m_coolTimeJudgement)
	{
		//		ダッシュクールタイムに入った時
		if (playerInformation->GetDashCoolTime() > 0.0f)
		{
			//		クールタイム状態にする
			m_coolTimeJudgement = true;

			//		角度を最大にする
			m_angle = 360.0f;

			//		割合を最大にする
			m_ratio = 100.0f;

			//		減らす状態
			m_state = State::Reduce;
		}
	}

	//		状態が何もしない場合処理をしない
	if (m_state == State::None) return;

	//		減らす状態
	if (m_state == State::Reduce)
	{
		//		ダッシュ時間
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 3.0f;

		if (m_time >= 1.0f)
		{
			//		増やす状態にする
			m_state = State::Increase;

			m_time = 1.0f;
		}
	}
	//		増やす状態
	else if (m_state == State::Increase)
	{
		//		クールタイム
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 0.6f;

		if (m_time <= 0.0f)
		{
			//		何もしない状態にする
			m_state = State::None;

			m_time = 0.0f;

			m_coolTimeJudgement = false;
		}
	}

	//		角度を設定する
	m_angle = Library::Lerp(360.0f, 0.0f, m_time);

	//		割合を設定する
	m_ratio = Library::Lerp(100.0f, 0.0f, m_time);
}

void CoolTime::Render()
{
	//		背景の描画
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::CloolTimeBackGround);

	//		回転量を設定する
	circleBuffer.rotation = { m_angle, 0.0f, 0.0f, 0.0f };

	//		周りの描画
	m_rotataionShader->Render(circleBuffer);

	//		数字の描画
	NumberView();
}

void CoolTime::Finalize()
{
}

void CoolTime::NumberView()
{
	//		数字の設定(百の位)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio / 100)), 0.0f, 0.0f, 0.0f };
	//		数字の座標設定(百の位)
	m_shader->SetPosition({ NUMBER_CENTER_POSITION - NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（百の位）
	m_shader->Render(buffer);

	//		数字の設定(十の位)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 / 10), 0.0f, 0.0f, 0.0f };
	//		数字の座標設定(十の位)
	m_shader->SetPosition({ NUMBER_CENTER_POSITION, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（十の位）
	m_shader->Render(buffer);

	//		数字の設定(一の位)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 % 10), 0.0f, 0.0f, 0.0f };
	//		数字の座標設定(一の位)
	m_shader->SetPosition({ NUMBER_CENTER_POSITION + NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（一の位）
	m_shader->Render(buffer);
}
