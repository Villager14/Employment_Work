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
	m_heightMove(7.0f)
{
}

PlayerWallWalk::~PlayerWallWalk()
{
}

void PlayerWallWalk::Initialize()
{
	//		�ړ�����
	float moveRadian = DirectX::XMConvertToRadians(90.0f);

	DirectX::SimpleMath::Vector3 acceleation = m_player->GetAcceleration();

	acceleation.Normalize();

	//		�ǂɓ�������������ړ��������o��
	DirectX::SimpleMath::Vector3 corss =
		m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().Cross(acceleation);

	//		�O�ς��O�ȏ�̏ꍇ���΂̕��ɐi��
	if (corss.y > 0)
	{
		moveRadian *= -1.0f;
	}

	//		�ŏ��ɓ��������ǂ̖@�����󂯎��
	DirectX::SimpleMath::Vector2 normalize =
	{ m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x,
	 m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z };

	float radian = atan2(normalize.y, normalize.x);

	//		�x�N�g�����o��
	m_velocity = DirectX::SimpleMath::Vector3(cosf(radian + moveRadian),
		0.0f, sinf(radian + moveRadian));

	m_velocity.Normalize();

	//		�ړ�����
	m_player->SetAcceleration(m_velocity);

}

void PlayerWallWalk::Update()
{
	MoveProcessing();
}

void PlayerWallWalk::Move()
{
	if (m_player->GetCollitionInformation()->GetWallWalkPlayerPosition().size() != 0)
	{
		m_player->SetPlanPosition(m_player->GetCollitionInformation()
			->GetWallWalkPlayerPosition()[0]);
	}

	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->SetPosition(m_player->GetPlanPosition());

	//		���̓���
	HeadMove();

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerWallWalk::Render()
{
}

void PlayerWallWalk::Finalize()
{
	//		�������Ԃ�����������
	m_player->SetFallTime(0.0f);

	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	//		�����Ă���Ƃ��̍���
	m_heightMove = m_player->GetStandingHeight();
}

void PlayerWallWalk::MoveProcessing()
{
	//		���x
	float speed = m_player->GetWalkSpeed();

	//		���W�ɐݒ肷��
	m_player->SetPlanPosition(m_player->GetPosition() + (m_velocity * speed) *
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
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		DirectX::SimpleMath::Vector3 velo = DirectX::SimpleMath::Vector3
		(cosf(DirectX::XMConvertToRadians(m_player->GetCameraAngle().x)),
			0.0f, sinf(DirectX::XMConvertToRadians(m_player->GetCameraAngle().x)));

		velo.Normalize();

		float dot = m_velocity.Dot(velo);

		if (dot < 0.3f)
		{
			//		�ړ��������v�Z����
			DirectX::SimpleMath::Vector3 velocity =
				DirectX::SimpleMath::Vector3::Lerp(m_velocity,
					m_player->GetPlayerInformationCollition()->GetWallWalkNormalize(), 0.3f);

			//		�W�����v�������
			m_player->SetAcceleration(velocity * m_player->GetWalkSpeed());

			//		��Ԃ�؂�ւ���(�W�����v)
			m_player->ChangeState(m_player->GetWallJumpState());
		}
		else
		{
			//		�W�����v�������
			m_player->SetDirection(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f));

			//		�W�����v�������
			m_player->SetAcceleration(m_player->MoveDirection(m_player->GetDirection()) * m_player->GetWalkSpeed());

			//		��Ԃ�؂�ւ���(�W�����v)
			m_player->ChangeState(m_player->GetJumpState());
		}
	}

	if (m_player->GetCollitionInformation()->GetWallWalkPlayerPosition().size() == 0)
	{
		//		�W�����v�������
		m_player->SetAcceleration(m_velocity * (m_player->GetWalkSpeed() * 0.7f));

		//		�ǃW�����v��Ԃɂ���
		m_player->ChangeState(m_player->GetWallJumpState());
	}

	DirectX::SimpleMath::Vector3 velo = DirectX::SimpleMath::Vector3
	(cosf(DirectX::XMConvertToRadians(m_player->GetCameraAngle().x + 90.0f)),
		0.0f, sinf(DirectX::XMConvertToRadians(m_player->GetCameraAngle().x + 90.0f)));

	velo.Normalize();

	float dot = m_velocity.Dot(velo);

	//		�v���C���[���i�s�������炾���Ԃ��ꂽ�ꏊ�������ꍇ
	if (dot < 0.0f)
	{
		//		������Ԃɂ���
		m_player->ChangeState(m_player->GetWalkState());
	}
}

void PlayerWallWalk::HeadMove()
{
	//		���݂̍��W���󂯎��
	DirectX::SimpleMath::Vector3 height = m_player->GetPosition();

	//		���̍�����5�ȏ�Ȃ珈��������
	if (m_heightMove > HEAD_WALLWALK_HEIGHT)
	{
		//		
		m_heightMove -= m_player->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		�����̐���������
		m_heightMove = Library::Clamp(m_heightMove, HEAD_WALLWALK_HEIGHT, m_player->GetStandingHeight());
	}

	//		�����𑫂�
	height.y += m_heightMove;

	//		���̈ړ��ʂ��󂯎��
	float move = m_player->GetPlayerInformationCamera()->GetHeadMove();

	//		�ړ����x
	move += m_player->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�ړ��ʂ̐���
	move = Library::Clamp(move, 0.0f, m_player->GetHeadMoveMAX());

	//		���̈ړ��ʂ�ݒ肷��
	m_player->GetPlayerInformationCamera()->SetHeadMove(move);

	//		���̈ړ��ʂ𑫂�
	height.x += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x * m_player->GetPlayerInformationCamera()->GetHeadMove();;
	height.z += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z * m_player->GetPlayerInformationCamera()->GetHeadMove();;

	//		�v���C���[�̍������X�V
	m_player->SetPlayerHeight(height);
}
