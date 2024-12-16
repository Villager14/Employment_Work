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
	m_angle(MAX_ANGLE),
	m_time(0.0f),
	m_ratio(RATO),
	m_uiManager(uiManager)
{
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		回転シェーダーの生成
	m_coolTImeShader = std::make_unique<UIRenderManager>();

	//		シェーダー描画マネージャーの生成
	m_coolTimeNumberShader = std::make_unique<UIRenderManager>();

	//		クールタイムUIの作製
	m_coolTImeShader->Create(COOL_TIME_TEXTURE_PATH,
		COOL_TIME_VS_PATH, COOL_TIME_GS_PATH,
		COOL_TIME_PS_PATH, buffer,
		COOL_TIME_POSITION, { 0.6f, 0.6f });

	//		数字シェーダーの作製
	m_coolTimeNumberShader->Create(COOL_TIME_NUMBER_TEXTURE_PATH,
		NUMBER_VS_PATH, NUMBER_GS_PATH,
		NUMBER_PS_PATH, buffer,
		{ 0.0f, 0.0f }, { 0.3f, 0.3f });

	//		ウィンドウサイズを設定する
	circleBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	circleBuffer.rotationMatrix = m_coolTImeShader->GetRotationMatrix();

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_coolTimeNumberShader->GetRotationMatrix();
}

void CoolTime::Update(float coolTime)
{
	//		減らす状態
	if (coolTime <=  0.5f)
	{
		//		ダッシュ時間
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * DASH_SPEED;
	}
	else
	{
		//		クールタイム
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * COOL_TIME_SPEED;
	}

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		角度を設定する
	m_angle = Library::Lerp(MAX_ANGLE, 0.0f, m_time);

	//		割合を設定する
	m_ratio = Library::Lerp(RATO, 0.0f, m_time);
}

void CoolTime::Render()
{
	//		背景の描画
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::CloolTimeBackGround);

	//		回転量を設定する
	circleBuffer.rotation = { m_angle, 0.0f, 0.0f, 0.0f };

	//		周りの描画
	m_coolTImeShader->Render(circleBuffer);

	//		数字の描画
	NumberView();
}

void CoolTime::Finalize()
{
	m_angle = MAX_ANGLE;
	m_time = 0.0f;
	m_ratio = RATO;

	m_coolTImeShader.reset();
	m_coolTimeNumberShader.reset();
}

void CoolTime::NumberView()
{
	//		数字の設定(百の位)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio / 100)), 0.0f, 0.0f, 0.0f };
	//		数字の座標設定(百の位)
	m_coolTimeNumberShader->SetPosition({ NUMBER_CENTER_POSITION - NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（百の位）
	m_coolTimeNumberShader->Render(buffer);

	//		数字の設定(十の位)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 / 10), 0.0f, 0.0f, 0.0f };
	//		数字の座標設定(十の位)
	m_coolTimeNumberShader->SetPosition({ NUMBER_CENTER_POSITION, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（十の位）
	m_coolTimeNumberShader->Render(buffer);

	//		数字の設定(一の位)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 % 10), 0.0f, 0.0f, 0.0f };
	//		数字の座標設定(一の位)
	m_coolTimeNumberShader->SetPosition({ NUMBER_CENTER_POSITION + NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（一の位）
	m_coolTimeNumberShader->Render(buffer);
}
