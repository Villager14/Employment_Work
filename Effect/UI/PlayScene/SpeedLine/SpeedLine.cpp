

#include "pch.h"

#include "SpeedLine.h"

SpeedLine::SpeedLine(UIManager* uiManager)
	:
	m_uiManager(uiManager),
	m_time(1.0f),
	m_frontTime(1.0f),
	frontFlag(false),
	m_speed(0.0f),
	m_backTime(0.0f),
	m_playerSpeed(0.0f)
{
}

SpeedLine::~SpeedLine()
{
}

void SpeedLine::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	//		回転シェーダーの作製
	m_shader->Create(UI_SPEED_TEXTURE_PATH,
		SPEED_LINE_VS_PATH, SPEED_LINE_GS_PATH,
		SPEED_LINE_PS_PATH, buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	m_shader->LoadTexture(SPEED_TEXTURE_PATH, 1);

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_frontTime = 1.0f;
	m_time = 1.0f + LINE_LENGTH;
}

void SpeedLine::Update(float speed)
{
	m_playerSpeed = speed;

	//		ダッシュをしているかどうか
	if (!m_uiManager->GetGameManager()->
		FlagJudgement(GameManager::DashJudgement)
		&& m_playerSpeed < MINIMUM_SPEED)
	{
		if (m_frontTime < 1.0f)
		{
			m_frontTime = 1.0f;
			m_time = 1.0f + LINE_LENGTH;
			m_backTime = 0.0f;
		}

		return;
	}

	m_backTime += LibrarySingleton::GetInstance()->GetElpsedTime() * BACK_SPEED;

	//		MINIMUM_SPEED以上MAXIMUM_SPEED以内にする
	float val = Library::Clamp(m_playerSpeed, MINIMUM_SPEED, MAXIMUM_SPEED);
	
	//		レイの速度を求める
	m_speed = Library::Lerp(RAY_SPEED_MIN, RAY_SPEED_MAX, (val - MINIMUM_SPEED) / (MAXIMUM_SPEED - MINIMUM_SPEED));

	//		アルファパワーを求める
	buffer.alphaPower = Library::Lerp(MIN_ALPHA_POWER, MAX_ALPHA_POWER, (val - MINIMUM_SPEED) / (MAXIMUM_SPEED - MINIMUM_SPEED));

	//		経過時間
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_speed;

	if (m_time <= 1.0f - LINE_LENGTH && frontFlag)
	{
		frontFlag = false;

		m_frontTime = 1.0f - LINE_LENGTH;
		m_time = 1.0f;
	}


	m_frontTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_speed;

	if (m_frontTime <= 0.0f)
	{
		m_frontTime = LINE_LENGTH;

		m_time = 1.0f;

		frontFlag = true;
	}


	//		コンストバッファの時間の更新
	buffer.time = { m_time, m_frontTime,
		static_cast<float>(frontFlag), 0.0f};
}

void SpeedLine::Render()
{
	//		ダッシュをしているかどうか
	if (!m_uiManager->GetGameManager()->
		FlagJudgement(GameManager::DashJudgement)
		&& m_playerSpeed < MINIMUM_SPEED)
	{
		return;
	}

	buffer.backTime = m_backTime;

	//		UIの描画
	m_shader->Render(buffer);
}

void SpeedLine::Finalize()
{
	m_shader.reset();
}
