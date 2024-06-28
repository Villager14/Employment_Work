/*
* @file		PlayerWallWalk.cpp
* @brief	�v���C���[�̕Ǖ������
* @author	Morita
* @date		2024/04/30
*/

#include "pch.h"

#include "PlayerWallWalk.h"

#include "../Player.h"

PlayerWallWalk::PlayerWallWalk(Player* player)
	:
	m_player(player),
	m_heightMove(7.0f),
	m_moveAngle(0.0f)
{
}

PlayerWallWalk::~PlayerWallWalk()
{
}

void PlayerWallWalk::Initialize()
{
	//		�ړ�����
	float moveRadian = DirectX::XMConvertToRadians(90.0f);
	m_moveAngle.y = 1.0f;

	DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

	acceleation.Normalize();

	//		�ǂɓ�������������ړ��������o��
	DirectX::SimpleMath::Vector3 corss =
		m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().Cross(acceleation);

	//		�O�ς��O�ȏ�̏ꍇ���΂̕��ɐi��
	if (corss.y > 0)
	{
		moveRadian *= -1.0f;
		m_moveAngle.y *= -1.0f;
	}

	//		�ŏ��ɓ��������ǂ̖@�����󂯎��
	DirectX::SimpleMath::Vector2 normalize =
	{ m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x,
	 m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z };

	normalize.Normalize();

	float radian = atan2(normalize.y, normalize.x);

	m_moveAngle.x = radian + moveRadian;

	//		�x�N�g�����o��
	m_velocity = DirectX::SimpleMath::Vector3(cosf(radian + moveRadian),
		0.0f, sinf(radian + moveRadian));

	m_velocity.Normalize();

	float speed = m_player->GetInformation()->GetAcceleration().Length();

	//		�������x���x�������ꍇ
	if (speed < m_player->GetInformation()->GetWalkSpeed())
	{
		//		�������x�ɂ���
		speed = m_player->GetInformation()->GetWalkSpeed();
	}

	//		�ړ����x
	m_player->GetInformation()->SetAcceleration(m_velocity * speed);

	//		�ړ�����
	m_player->GetInformation()->SetDirection(m_velocity);

	//		�A�j���[�V�����Ǖ���
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->WallWalk);
}

void PlayerWallWalk::Update()
{
	MoveProcessing();
}

void PlayerWallWalk::Move()
{
	if (m_player->GetCollitionInformation()->GetWallWalkPlayerPosition().size() != 0)
	{
		m_player->GetInformation()->SetPlanPosition(m_player->GetCollitionInformation()
			->GetWallWalkPlayerPosition()[0]);
	}

	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		���̓���
	HeadMove();

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerWallWalk::Animation()
{
	//		�Ǖ���
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_moveAngle,
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerWallWalk::Render()
{
}

void PlayerWallWalk::Finalize()
{
	//		�������Ԃ�����������
	m_player->GetInformation()->SetFallTime(0.0f);

	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	//		�����Ă���Ƃ��̍���
	m_heightMove = m_player->GetInformation()->GetStandingHeight();
}

void PlayerWallWalk::MoveProcessing()
{
	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition()
		+ (m_velocity * m_player->GetInformation()->GetAcceleration().Length()) *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWallWalk::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = 
		*LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		space�ŃW�����v
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) || 
		m_player->GetCollitionInformation()->GetWallWalkPlayerPosition().size() == 0)
	{
		DirectX::SimpleMath::Vector3 velo = DirectX::SimpleMath::Vector3
		(cosf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x)),
			0.0f, sinf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x)));

		velo.Normalize();

		float dot = m_velocity.Dot(velo);

		if (dot < 0.3f)
		{
			//		�ړ��������v�Z����
			DirectX::SimpleMath::Vector3 velocity =
				DirectX::SimpleMath::Vector3::Lerp(m_velocity,
					m_player->GetPlayerInformationCollition()->GetWallWalkNormalize(), 0.3f);

			velocity.Normalize();

			float speed = m_player->GetInformation()->GetAcceleration().Length();

			//		�W�����v�������
			m_player->GetInformation()->SetAcceleration(velocity * speed);

			//		��Ԃ�؂�ւ���(�W�����v)
			m_player->ChangeState(m_player->PlayerState::Jump);
		}
		else
		{
			//		�W�����v�������
			m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f));

			//		�W�����v�������
			m_player->GetInformation()->SetAcceleration(m_player->MoveDirection(m_player->GetInformation()->GetDirection()) * m_player->GetInformation()->GetAcceleration().Length());

			//		��Ԃ�؂�ւ���(�W�����v)
			m_player->ChangeState(m_player->PlayerState::Jump);
		}
	}

	DirectX::SimpleMath::Vector3 velo = DirectX::SimpleMath::Vector3
	(cosf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x + 90.0f)),
		0.0f, sinf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x + 90.0f)));

	velo.Normalize();

	float dot = m_velocity.Dot(velo);

	//		�v���C���[���i�s�������炾���Ԃ��ꂽ�ꏊ�������ꍇ
	if (dot < 0.0f)
	{
		//		������Ԃɂ���
		m_player->ChangeState(m_player->PlayerState::Walk);
	}
}

void PlayerWallWalk::HeadMove()
{
	//		���݂̍��W���󂯎��
	DirectX::SimpleMath::Vector3 height = m_player->GetInformation()->GetPosition();

	//		���̍�����5�ȏ�Ȃ珈��������
	if (m_heightMove > HEAD_WALLWALK_HEIGHT)
	{
		//		
		m_heightMove -= m_player->GetInformation()->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		�����̐���������
		m_heightMove = Library::Clamp(m_heightMove, HEAD_WALLWALK_HEIGHT, m_player->GetInformation()->GetStandingHeight());
	}

	//		�����𑫂�
	height.y += m_heightMove;

	//		���̈ړ��ʂ��󂯎��
	float move = m_player->GetInformation()->GetHeadMove();

	//		�ړ����x
	move += m_player->GetInformation()->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�ړ��ʂ̐���
	move = Library::Clamp(move, 0.0f, m_player->GetInformation()->GetHeadMoveMAX());

	//		���̈ړ��ʂ�ݒ肷��
	m_player->GetInformation()->SetHeadMove(move);

	//		���̈ړ��ʂ𑫂�
	height.x += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x * m_player->GetInformation()->GetHeadMove();;
	height.z += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z * m_player->GetInformation()->GetHeadMove();;

	//		�v���C���[�̍������X�V
	m_player->GetInformation()->SetPlayerHeight(height);
}
