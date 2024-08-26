/*
* @file		CommonEnemy.cpp
* @brief	��ʓI�ȓG
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemy.h"

CommonEnemy::CommonEnemy()
	:
	m_istate{ nullptr },
	m_rotation(0.0f),
	m_attackJudgement(false),
	m_timeSpeed(0.0f)
{
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::CommonEnemy);
}

CommonEnemy::~CommonEnemy()
{
}

void CommonEnemy::Initialize()
{
	m_position = { 10.0f, 0.0f, 0.0f };

	m_stateintarface[State::Stay] = std::make_unique<CommonEnemyStay>(this);
	m_stateintarface[State::Vigilance] = std::make_unique<CommonEnemyVigilance>(this);
	m_stateintarface[State::Charge] = std::make_unique<CommonEnemyCharge>(this);
	m_stateintarface[State::Attack] = std::make_unique<CommonEnemyAttack>(this);

	m_state = State::Stay;

	//		�������
	m_istate = m_stateintarface[m_state].get();

	//		��Ԃ̏�����
	m_istate->Initialize();

	//		����������
	m_playerAnimation->Initialize();
}

void CommonEnemy::Update(const DirectX::SimpleMath::Vector3& playerPosition,
						 float timeSpeed)
{
	m_playerPosition = playerPosition;
	m_timeSpeed = timeSpeed;

	//		��Ԃ̍X�V����
	m_istate->Update();

	m_playerAnimation->Execute(0.0f, m_position, {0.0f, m_rotation}, 4.4f);
}

void CommonEnemy::Render()
{
	//		��Ԃ̕`��
	m_istate->Render();
}

void CommonEnemy::Finalize()
{
}
