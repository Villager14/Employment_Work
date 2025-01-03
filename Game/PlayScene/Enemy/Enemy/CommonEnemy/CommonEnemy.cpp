/*
* @file		CommonEnemy.cpp
* @brief	一般的な敵
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemy.h"

CommonEnemy::CommonEnemy(EnemyInformation enemyInformation)
	:
	m_istate{ nullptr }
{
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::CommonEnemy);

	m_intarface = std::make_unique<CommonEnemyIntarface>();

	//		エネミーの情報
	m_enemyInformation = enemyInformation;
}

CommonEnemy::~CommonEnemy()
{
}

void CommonEnemy::Initialize()
{
	m_intarface->SetPosition(m_enemyInformation.position);

	m_intarface->SetRotation(DirectX::XMConvertToRadians(90.0f));

	m_stateintarface[State::Stay] = std::make_unique<CommonEnemyStay>(this);
	m_stateintarface[State::Vigilance] = std::make_unique<CommonEnemyVigilance>(this);
	m_stateintarface[State::Charge] = std::make_unique<CommonEnemyCharge>(this);
	m_stateintarface[State::Attack] = std::make_unique<CommonEnemyAttack>(this);

	m_state = State::Stay;

	//		初期状態
	m_istate = m_stateintarface[m_state].get();

	//		状態の初期化
	m_istate->Initialize();

	//		初期化処理
	m_playerAnimation->Initialize();
}

void CommonEnemy::Update(const DirectX::SimpleMath::Vector3& playerPosition,
						 float timeSpeed)
{
	m_intarface->SetPlayerPosition(playerPosition);
	m_intarface->SetTimeSpeed(timeSpeed);

	//		状態の更新処理
	m_istate->Update();

	//m_playerAnimation->Execute(0.0f, m_position, {0.0f, m_rotation}, 4.4f);
}

void CommonEnemy::Render()
{
	//		状態の描画
	m_istate->Render();


	float font = 0;

	if (m_viewJudgement) font = 1;

	LibrarySingleton::GetInstance()->DebugFont(L"ViweJudgement", font, 0, 200);
}

void CommonEnemy::Finalize()
{
}

bool CommonEnemy::FieldOfVision()
{
	DirectX::SimpleMath::Vector3 velocity = DirectX::SimpleMath::Vector3::Zero;

	velocity.x = sinf(m_intarface->GetRotation());
	velocity.z = cosf(m_intarface->GetRotation());

	//		正規化
	velocity.Normalize();

	DirectX::SimpleMath::Vector3 playerVelociry = m_intarface->GetPlayerPosition() - m_intarface->GetPosition();

	//		視野の長さより長い場合は処理をしない
	if (playerVelociry.Length() > m_intarface->GetViewLength())
	{
		m_viewJudgement = false;

		return false;
	}


	//		正規化
	playerVelociry.Normalize();

	float dot = velocity.Dot(playerVelociry);

	if (dot < 0.5f)
	{
		//		視界に入っていない
		m_viewJudgement = false;

		return false;
	}

	m_viewJudgement = true;

	return true;
}
