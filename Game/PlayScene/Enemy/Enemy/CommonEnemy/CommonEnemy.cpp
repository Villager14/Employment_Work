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
	m_state{ nullptr },
	m_rotation(0.0f),
	m_attackJudgement(false),
	m_timeSpeed(0.0f)
{
}

CommonEnemy::~CommonEnemy()
{
}

void CommonEnemy::Initialize()
{
	m_position = { 10.0f, 0.0f, 0.0f };

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_model = DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Enemy.cmo", *m_effect);

	//		�ҋ@��Ԃ̐���
	m_stay = std::make_unique<CommonEnemyStay>(this);

	//		�x����Ԃ̐���
	m_vigilance = std::make_unique<CommonEnemyVigilance>(this);

	//		�`���[�W��Ԃ̐���
	m_charge = std::make_unique<CommonEnemyCharge>(this);

	//		�U����Ԃ̐���
	m_attack = std::make_unique<CommonEnemyAttack>(this);

	//		�������
	m_state = m_stay.get();

	//		��Ԃ̏�����
	m_state->Initialize();
}

void CommonEnemy::Update(const DirectX::SimpleMath::Vector3& playerPosition,
						 float timeSpeed)
{
	m_playerPosition = playerPosition;
	m_timeSpeed = timeSpeed;

	//		��Ԃ̍X�V����
	m_state->Update();
}

void CommonEnemy::Render()
{
	//		��Ԃ̕`��
	m_state->Render();
}

void CommonEnemy::Finalize()
{
}
