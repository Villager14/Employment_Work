/*
* @file		TitleUI.h
* @brief	�^�C�g����UI
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleUI.h"

TitleUI::TitleUI()
{
	//		�^�C�g���̔w�i�̐���
	m_backGround = std::make_unique<BackGroundMove>();

	//		�I���o�[�̐���
	m_selectionBar = std::make_unique<SelectionBar>();

	//		�L�[�K�C�_���X�̐���
	m_keyGuidance = std::make_unique<TitleKeyGuidance>();

	//		�t�F�[�hUI�̐���
	m_fadeUI = std::make_unique<FadeUI>();
}

TitleUI::~TitleUI()
{
}

void TitleUI::Initalize()
{
	Generation();

	//		�^�C�g���̔w�i�̈ړ������̏�����
	m_backGround->Initialize();

	//		�I���o�[�̏�����
	m_selectionBar->Initialize();

	//		�L�[�K�C�_���X�̏�����
	m_keyGuidance->Initialize();

	//		�t�F�[�hUI�̏�����
	m_fadeUI->Initialize();
}

void TitleUI::Update()
{
	//		�w�i�̍X�V����
	m_backGround->Update();

	//		�t�F�[�h�A�E�g�̍X�V
	m_fadeUI->Update();
}

void TitleUI::Render(int postEffectType)
{
	if (postEffectType == PostEffectFlag::PostEffectFlag::UI)
	{
		//		�t�F�[�hUI�̕`��
		m_fadeUI->Render();
	}
	else if (postEffectType == PostEffectFlag::PostEffectFlag::UIBack)
	{
		//		�^�C�g�����S�̕`��
		m_standardShader->Render(TitleUIType::TitleRogo);

		//		�I���o�[�̕`��
		m_selectionBar->Render();

		//		�L�[�K�C�_���X�̕`��
		m_keyGuidance->Render();
	}
}

void TitleUI::Generation()
{
	//		�^�C�g��UI�}�l�[�W���[�̐���
	m_standardShader = std::make_unique<StandardShader<TitleUIType>>();

	//		�^�C�g��UI�}�l�[�W���̏�����
	m_standardShader->Initialize();

	//		�^�C�g�����S�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		TITLE_POINT, { MAX_SCALE, MAX_SCALE },
		TitleUIType::TitleRogo);
}

void TitleUI::Finalize()
{
	//		�w�i�̏I������
	m_backGround->Finalize();

	//		�I���o�[�̏I������
	m_selectionBar->Finalize();

	//		�L�[�K�C�h�̏I������
	m_keyGuidance->Finalize();

	//		�t�F�[�hUI�̏I������
	m_fadeUI->Finalize();
}

void TitleUI::DownSelect(float processingTime)
{
	//		�I���o�[�̉��ړ�����
	m_selectionBar->DownSelect(processingTime);

	//		�L�[�K�C�h�̉��ړ�����
	m_keyGuidance->DownSelect(processingTime);
}

void TitleUI::UpSelect(float processingTime)
{
	//		�I���o�[�̏�ړ�����
	m_selectionBar->UpSelect(processingTime);

	//		�L�[�K�C�h�̏�ړ�����
	m_keyGuidance->UpSelect(processingTime);
}

void TitleUI::SceneEndFadeOut()
{

}

void TitleUI::FadeOut()
{
	//		�t�F�[�h�A�E�g���s��
	m_fadeUI->FadeOutUse();
}
