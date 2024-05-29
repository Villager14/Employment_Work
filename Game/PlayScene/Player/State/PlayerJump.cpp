/*
* @file		PlayerWalk.cpp
* @brief	�v���C���[�̕������
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerJump.h"

#include "../Player.h"

PlayerJump::PlayerJump(Player* player)
	:
	m_player(player),
	m_elapsedTime(0.0f),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_stopJump(false),
	m_rayprocessJudgement(false),
	m_rayHitJudgement(false),
	m_nowSpeed(0.0f)
{


}

PlayerJump::~PlayerJump()
{
}

void PlayerJump::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		���݂̑��x���󂯎��
	m_nowSpeed = m_player->GetInformation()->GetAcceleration().Length();

	//		�J�����̉�]�ʂ��󂯎��
	m_cameraMatrix = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x));

	//		�ړ����Ă��Ȃ����ǂ���
	if (m_player->GetInformation()->GetDirection().Length() < FLT_EPSILON)
	{
		//		�ړ����Ă��Ȃ�
		m_stopJump = true;
	}
	//		�ړ����Ă���
	else m_stopJump = false;

	m_player->GetInformation()->SetGravity(0.0f);
	m_player->GetInformation()->SetFallTime(0.0f);

	//		�W�����v�ł��Ȃ���Ԃɂ���
	m_player->GetInformation()->SetJumpJudgement(false);
}

void PlayerJump::Update()
{
	//		�W�����v�̏���
	Jump();

	//		�ړ�����
	MoveProcessing();

	//		�d�͏���
	m_player->Gravity();
}

void PlayerJump::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		���C�̏������s�����ǂ���
	if (m_rayprocessJudgement)
	{
		//		���������ꏊ���Ȃ���Ώ��������Ȃ�
		if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
		{
			if (abs(m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y -
				m_player->GetInformation()->GetPlanPosition().y) < 1.0f)
			{
				DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

				position.y = m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y;

				m_player->GetInformation()->SetPlanPosition(position);

				m_player->GetInformation()->SetFallTime(0.0f);

				m_rayHitJudgement = true;
			}
		}
	}

	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��Ԃ�J�ڂ��邩�ǂ���
	ChangeStateJudgement();
}

void PlayerJump::Render()
{
}

void PlayerJump::Finalize()
{
	m_elapsedTime = 0.0f;

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_rayprocessJudgement = false;

	m_rayHitJudgement = false;

	m_nowSpeed = 0.0f;
}

void PlayerJump::MoveProcessing()
{
	
	//		�L�[�������Ă��邩�ǂ���
	m_keyInputJudgement = false;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = 
		DirectX::SimpleMath::Vector3::Zero;

	//		�ړ�����������󂯎��
	direction = m_player->Direction(&m_keyInputJudgement);

	if (m_keyInputJudgement && m_stopJump)
	{
		//		�ړ����������ݒ肷��
		m_player->GetInformation()->SetDirection(direction);

		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation += DirectX::SimpleMath::Vector3::Transform(
			direction, m_cameraMatrix.Invert()) * 40.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

		m_player->GetInformation()->SetAcceleration(acceleation);

	}
	else if (!m_stopJump && m_keyInputJudgement)
	{
		//		�ړ����������ݒ肷��
		m_player->GetInformation()->SetDirection(direction);

		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation += DirectX::SimpleMath::Vector3::Transform(
			direction, m_cameraMatrix.Invert()) * 60.0f * LibrarySingleton::GetInstance()->GetElpsedTime();
		
		if (acceleation.Length() > m_nowSpeed)
		{
			acceleation.Normalize();

			acceleation *= m_nowSpeed;
		}

		m_player->GetInformation()->SetAcceleration(acceleation);
	}

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPosition();

	position.y = m_player->GetInformation()->GetPlanPosition().y;

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(position +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerJump::Jump()
{
	//		��b�ȏ�͏��������Ȃ�
	if (m_elapsedTime >= 1.0f)
	{
		return;
	}

	//		�W�����v���鎞��
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * JUMP_SPEED;

	//		��ȏ�ɂȂ�Ȃ��悤�ɂ���
	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	//		�v���C���[�̍��W���󂯎��
	DirectX::SimpleMath::Vector3 m_jumpPosition = m_player->GetInformation()->GetPosition();

	//		easeInCirc
	float move = 1.0f - std::sqrt(1.0f - pow(m_elapsedTime, 2.0f));

	//		�������������Ȃ���
	float speed = Library::Lerp(JUMP_MAX_SPEED, JUMP_MIN_SPEED, move);

	//		�ړ��ʂ��v�Z����
	m_jumpPosition.y += speed * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���W�ɃZ�b�g����
	m_player->GetInformation()->SetPlanPosition(m_jumpPosition);
}

void PlayerJump::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�Ǖ�����Ԃ��ǂ���
	m_player->WallWalkJudgement();

	//		��b�o�ߌ㏈��������
	if (m_elapsedTime >= 1.0f) { m_rayprocessJudgement = true; }

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�L�[�{�[�h�X�e�[�g�̎擾
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		Shift���������ꍇ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{		
		//		�_�b�V���ł��邩�ǂ���
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		��Ԃ�؂�ւ���(�_�b�V��)
			m_player->ChangeState(m_player->GetDashState());
		}
	}

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->GetGoalJudgement())
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->GetGoalState());
	}

	//		���ɓ���������ʂ̏�Ԃɂ���
	if (m_rayHitJudgement)
	{
		//		�L�[��������Ă��Ȃ��ꍇ
		if (!m_keyInputJudgement)
		{
			//		��Ԃ�J�ڂ���(�ҋ@���)
			m_player->ChangeState(m_player->GetStayState());
		}
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::LeftControl))
		{
			//		��Ԃ�J�ڂ���(�X���C�f�B���O)
			m_player->ChangeState(m_player->GetSlidingState());
		}
		else
		{
			//		��Ԃ�؂�ւ���(�������)
			m_player->ChangeState(m_player->GetWalkState());
		}

		return;
	}
}