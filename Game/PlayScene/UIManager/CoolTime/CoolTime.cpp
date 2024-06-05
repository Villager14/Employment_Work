/*
* @file		CoolTime.h
* @brief	クールタイム
* @author	Morita
* @date		2024/05/20
*/
#include "pch.h"

#include "CoolTime.h"

CoolTime::CoolTime()
	:
	m_angle(360.0f),
	m_time(0.0f),
	m_coolTimeJudgement(false),
	m_ratio(100.0f),
	m_state()
{
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		数字シェーダーの生成
	m_circleShader = std::make_unique<CircleShader>();

	float scale = 0.6f;

	//		クールタイムシェーダーの作製
	m_circleShader->Create(L"Resources/Texture/UI/CoolTime/CoolTime.png",
		{270.0f, 0.0f}, { scale, scale });
		
	//		背景シェーダーの生成
	m_backRender = std::make_unique<UIRender>();

	//		背景シェーダーの作製
	m_backRender->Create(L"Resources/Texture/UI/CoolTime/CoolTimeBack.png",
		{ 539.0f, 0.0f }, { scale, scale });

	//		数字シェーダーの生成
	m_numberShader = std::make_unique<NumberShader>();

	//		数字シェーダーの作製
	m_numberShader->Create(L"Resources/Texture/UI/CoolTime/cooltimeNumber.png",
		{ 1200.0f, 360.0f }, { 0.3f, 0.3f });

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
	m_backRender->Render();


	//		円の描画
	m_circleShader->Render(static_cast<int>(m_angle));

	

	//		数字シェーダーの座標を設定する（百の位）
	m_numberShader->SetPosition({ NUMBER_CENTER_POSITION - NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（百の位）
	m_numberShader->Render(static_cast<int>(m_ratio / 100));
	//		数字シェーダーの座標を設定する（十の位）
	m_numberShader->SetPosition({ NUMBER_CENTER_POSITION, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（十の位）
	m_numberShader->Render(static_cast<int>(m_ratio) % 100 / 10);
	//		数字シェーダーの座標を設定する（一の位）
	m_numberShader->SetPosition({ NUMBER_CENTER_POSITION + NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		数字の描画（一の位）
	m_numberShader->Render(static_cast<int>(m_ratio) % 100 % 10);
}

void CoolTime::Finalize()
{
}
