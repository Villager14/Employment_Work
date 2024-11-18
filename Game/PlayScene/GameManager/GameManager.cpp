/*
* @file		GameManager.cpp
* @brief	�Q�[���}�l�[�W���[
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "GameManager.h"

GameManager::GameManager()
	:
	m_time(0.0f),
	m_deathCount(0),
	m_gameSpeed(1.0f),
	m_flag(0),
	m_limitTime(0.0f)
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	m_flag = Flag::None;
	m_time = 0.0f;
	m_deathCount = 0;
	m_gameSpeed = 0.0f;
	m_limitTime = 0.0f;
}

void GameManager::Update(PostEffectInformation* postEffectInformation)
{
	//		�V�[�����I������Ƃ�
	if (FlagJudgement(Flag::EndJudgement))
	{
		//		�|�X�g�G�t�F�N�g�̃t�F�[�h
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::SceneEndFade);
	}

	//		���S���Ă��Ȃ��ꍇ�ȉ��̏��������Ȃ�
	if (!FlagJudgement(Flag::DeathJudgement)) return;

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::FadeJudgement);
	}

	//		�t�F�[�h���I�������
	if (postEffectInformation->FlagJudgement(PostEffectInformation::Flag::FadeEnd))
	{
		//		���S��Ԃ�Flase�ɂ���
		FalseFlag(GameManager::DeathJudgement);
		postEffectInformation->FalseFlag(PostEffectInformation::Flag::FadeEnd);
		postEffectInformation->FalseFlag(PostEffectInformation::Flag::RedScreen);
	}

	if (FlagJudgement(GameManager::DeathJudgement))
	{
		//		��ʂ�Ԃ�����
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::RedScreen);
	}

	//		�V�[�����I������Ƃ�
	if (FlagJudgement(Flag::TimeLimitJudgement))
	{
		//		�|�X�g�G�t�F�N�g�̃t�F�[�h
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::TimeLimitJudgement);
		
		//		��ʂ�Ԃ�����
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::RedScreen);
	}
}

void GameManager::Finalize()
{
	m_flag = Flag::None;
	m_time = 0.0f;
	m_deathCount = 0;
	m_gameSpeed = 0.0f;
	m_limitTime = 0.0f;
}

bool GameManager::FlagJudgement(Flag flag)
{
	//		�����̃r�b�g���P�̏ꍇ
	if (m_flag & flag) return true;

	return false;
}

void GameManager::TrueFlag(Flag flag)
{
    m_flag |= flag;
}

 void GameManager::FalseFlag(Flag flag)
 {
	//		�t���O���I���̎��̓I�t�ɂ���
	m_flag &= ~flag;
 }
