/*
* @file		TitlePlayer.cpp
* @brief	�^�C�g���v���C���[�̏���
* @author	Morita
* @date		2024/12/13
*/

#include "pch.h"

#include "TItlePlayer.h"

TitlePlayer::TitlePlayer()
{
	//		�v���C���[�̃A�j���[�V�����̍쐻
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Title);

	//		�|�X�G�t�F�N�g�t���O
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Initialize()
{
	//		�v���C���[�̃A�j���[�V����������
	m_playerAnimation->Initialize();
	//		�|�X�g�G�t�F�N�g�t���O
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
	//		�ʏ�`�������悤�ɂ���
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
	//		�u���[�����|����悤�ɂ���
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);
	//		�u���[���̐[�x�`��͕`�悵�Ȃ�
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);
	//		�t�H�O�̏����̏ꍇ�`�悷��
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);
}

void TitlePlayer::Update()
{
	//		�v���C���[�̃A�j���[�V����
	m_playerAnimation->Execute(0.0f, { 0.0f, 2.0f, 0.0f },
		{ 180.0f, 0.0f }, 2.5f);
}

void TitlePlayer::Render(PostEffectFlag::Flag flag)
{
	//		�t���O���I�t�̏ꍇ���������Ȃ�
	if (!m_postEffectFlag->FlagJudgement(flag)) return;

	m_playerAnimation->Render();
}

void TitlePlayer::Finalize()
{
	m_playerAnimation->Finalize();
}

void TitlePlayer::PlayAnimation()
{
	m_playerAnimation->ChangeState(AnimationManager::Stay);
}

void TitlePlayer::SettingAnimation()
{
	m_playerAnimation->ChangeState(AnimationManager::Upright);
}

void TitlePlayer::ExitAnimation()
{
	m_playerAnimation->ChangeState(AnimationManager::Sliding);
}
