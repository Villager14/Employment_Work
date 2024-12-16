/*
* @file		TitlePostEffectManager.cpp
* @brief	�^�C�g���|�X�g�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitlePostEffectManager.h"

TitlePostEffectManager::TitlePostEffectManager
		(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
	//		�|�X�g�G�t�F�N�g�t���O�̍쐻
	m_posteffectFlag = std::make_unique<PostEffectFlag>();

	//		�^�C�g���|�X�g�G�t�F�N�g�I�u�U�[�o�[
	m_titlePostEffectObserver = std::make_unique<TitlePostEffectObserver>();
}

TitlePostEffectManager::~TitlePostEffectManager()
{
}

void TitlePostEffectManager::Initialize()
{
	//		�g�p����G�t�F�N�g�̎��
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UI);
	//m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::PlayerView);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UIBack);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Fade);

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̏���������
	m_postEffectManager->Initialize(DirectX::Colors::Black,  m_posteffectFlag.get());
}

void TitlePostEffectManager::Update()
{
	//		�|�X�g�G�t�F�N�g�̍X�V
	for (int i = 1; i <= PostEffectFlag::Fade;)
	{
		//		�t���O�������Ă��Ȃ������͍s��Ȃ�
		if (!m_posteffectFlag->FlagJudgement(PostEffectFlag::Flag(i)))
		{
			i = i + i;

			continue;
		}

		//		�|�X�g�G�t�F�N�g�̍X�V
		m_postEffectManager->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		�t�F�[�h�C���I��
	if (m_postEffectManager->GetInformation()->
		FlagJudgement(PostEffectInformation::Flag::FadeInEnd))
	{
		m_titlePostEffectObserver->FadeIn();
		m_postEffectManager->GetInformation()->FalseFlag
		(PostEffectInformation::Flag::FadeInEnd);
	}

	//		�t�F�[�h�A�E�g�I��
	if (m_postEffectManager->GetInformation()->FlagJudgement
		(PostEffectInformation::Flag::SceneEnd))
	{
		m_titlePostEffectObserver->FadeOut();
	}
}

bool TitlePostEffectManager::PostEffectUseJudgement(int postEffectFlag)
{
	//		�t���O�������Ă��邩�ǂ���
	if (m_posteffectFlag->FlagJudgement(PostEffectFlag::Flag(postEffectFlag))) return true;

	return false;
}

void TitlePostEffectManager::PostEffectUpdate(int postEffectFlag)
{
	//		�|�X�g�G�t�F�N�g�̍X�V
	m_postEffectManager->Render(PostEffectFlag::Flag(postEffectFlag));
}

void TitlePostEffectManager::PostEffectRender(int postEffectFlag)
{
	//		�|�X�g�G�t�F�N�g�̕`��
	m_postEffectManager->RastRender(PostEffectFlag::Flag(postEffectFlag));
}

void TitlePostEffectManager::PostEffectTextureRender()
{
	//		�����_�[�e�N�X�`�������Z�b�g����
	m_postEffectManager->ResetRenderTarget();

	//		�����_�[�e�N�X�`���̕`��
	m_postEffectManager->RenderTextureView();
}

void TitlePostEffectManager::SceneEndFadeOut()
{
	//		�V�[���ύX�t�F�[�h�A�E�g
	m_postEffectManager->GetInformation()->TrueFlag(PostEffectInformation::Flag::SceneEndFade);
}

void TitlePostEffectManager::FadeOut()
{
}

void TitlePostEffectManager::Finalize()
{
	m_postEffectManager->Finalize();

	m_titlePostEffectObserver->Dalete();
}
