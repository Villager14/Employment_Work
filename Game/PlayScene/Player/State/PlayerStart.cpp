/*
* @file		PlayerStart.cpp
* @brief	�v���C���[�̃X�^�[�g���
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerStart.h"

#include "../Player.h"

PlayerStart::PlayerStart(Player* player)
	:
	m_player(player)
{
}

PlayerStart::~PlayerStart()
{
}

void PlayerStart::Initialize()
{
}

void PlayerStart::Update()
{
}

void PlayerStart::Move()
{
	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerStart::Render()
{
}

void PlayerStart::Finalize()
{
}

void PlayerStart::ChangeStateJudgement()
{
	//		�J�����̉��o���I�������
	if (m_player->GetCameraInformation()->GetStartJudgement())
	{
		//		��Ԃ�J�ڂ���i�ҋ@��ԁj
		m_player->ChangeState(m_player->GetStayState());
	}
}
