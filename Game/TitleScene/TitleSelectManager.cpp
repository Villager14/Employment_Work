/*
* @file		BackGroundMove.cpp
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleSelectManager::TitleSelectManager(PostEffectManager* postEffectManager)
	:
	m_iState(),
	m_state{},
	m_menuInformation(nullptr),
	m_postEffectManager(postEffectManager)
{
	Generation();
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		�}�E�X�̃t�H�[���`�����Z�b�g����
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	CreateStandardShader();

	//		���̏�����
	m_information->Initilaize(m_backGroundMove.get(), m_standardShader.get());

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//		�v���C���[�̃A�j���[�V����������
	m_playerAnimation->Initialize();

	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UI);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::PlayerView);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UIBack);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Fade);

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̏���������
	m_postEffectManager->Initialize(DirectX::Colors::White, m_posteffectFlag.get());

	//----
	//		�^�C�g���̏�Ԃ̍쐻
	//---

	//		�����̏��
	m_state = TitleInformation::State::StartState;
	
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		����������
	m_iState->Initialize();
}

void TitleSelectManager::Generation()
{
	//		�^�C�g������ݒ肷��
	m_information = std::make_unique<TitleInformation>();

	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�^�C�g�����ʏ����̐���
	m_commonProcess = std::make_unique<TitleCommonProcess>(m_information.get());

	//		�v���C���[�̃A�j���[�V�����̍쐻
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Title);

	//		�|�X�g�G�t�F�N�g�t���O�̍쐻
	m_posteffectFlag = std::make_unique<PostEffectFlag>();

	//----
	//		�^�C�g���̏�Ԃ̍쐻
	//---

	auto stateInformation = m_information->GetStateInformation();

	//		��Ԃ̏���ݒ肷��
	(*stateInformation).insert({ TitleInformation::State::PlayState, std::make_unique<SelectPlayState>(this) });
	(*stateInformation).insert({ TitleInformation::State::EndState, std::make_unique<SelectEndState>(this) });
	(*stateInformation).insert({ TitleInformation::State::SettingState, std::make_unique<SelectSettingState>(this) });
	(*stateInformation).insert({ TitleInformation::State::StartState, std::make_unique<StartSceneState>(this) });
	(*stateInformation).insert({ TitleInformation::State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		�`�揇��ݒ肷��
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Play);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Setting);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::End);
}

void TitleSelectManager::Update()
{
	//		�w�i�̍X�V����
	m_backGroundMove->Update();

	//		���j���[���J���Ă���ꍇ�͏��������Ȃ�
	if (m_menuInformation->GetMenuJudgement()) return;

	//		�v���C���[�̃A�j���[�V����
	m_playerAnimation->Execute(0.0f, { 0.5f, -2.0f, 1.05f },
		{ 180.0f, 0.0f }, 2.5f);

	//		�X�V����
	m_iState->Update();

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
}

void TitleSelectManager::Render()
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
		m_postEffectManager->Render(PostEffectFlag::Flag(i));

		if (i == PostEffectFlag::Flag::UI)
		{
			//		�w�i�̕`��
			m_backGroundMove->Render();
		}

		if (i == PostEffectFlag::Flag::PlayerView)
		{
			m_playerAnimation->Render();
		}

		if (i == PostEffectFlag::Flag::UIBack)
		{
			//		�I���̕`��
			for (int j = 0, max = static_cast<int>((*m_information->GetDraowOder()).size()); j < max; ++j)
			{
				//		�I��UI�̕`��
				m_information->GetStandardShader()->Render((*m_information->GetDraowOder())[j]);
			}

			//		�X�y�[�X
			m_standardShader->Render(TitleInformation::TitleUIType::Space);

			//		�^�C�g�����S�̕`��
			m_standardShader->Render(TitleInformation::TitleUIType::TitleRogo);

			//		�`�揈��
			m_iState->Render();
		}

		//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃��X�g�`��
		m_postEffectManager->RastRender(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		�����_�[�e�N�X�`�������Z�b�g����
	m_postEffectManager->ResetRenderTarget();

	//		�����_�[�e�N�X�`���̕`��
	m_postEffectManager->RenderTextureView();
}

void TitleSelectManager::Finalize()
{
	//		���̏�����
	m_information->Finalize();

	m_playerAnimation->Finalize();

	m_backGroundMove->Finalize();

	m_standardShader.reset();

	m_postEffectManager->Finalize();
}

void TitleSelectManager::CreateStandardShader()
{
	//		�^�C�g��UI�}�l�[�W���[�̐���
	m_standardShader = std::make_unique<StandardShader<TitleInformation::TitleUIType>>();

	//		�^�C�g��UI�}�l�[�W���̏�����
	m_standardShader->Initialize();

	//		�^�C�g�����S�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		m_information->TITLE_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::TitleRogo);

	//		Play�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		m_information->CENTER_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Play);

	//		End�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		m_information->UP_POINT , { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::End);

	//		Setting�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		m_information->UNDER_POINT, { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::Setting);

	//		Space�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/Space.png",
		m_information->SPACE_PLAY, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Space);

	//		W�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/W.png",
		m_information->W_END, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::W);

	//		A�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/A.png",
		m_information->A_SETTING, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::A);
}

void TitleSelectManager::ChangeState
(TitleInformation::State state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_iState->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		��Ԃ�؂�ւ���
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		�V������Ԃ̏���������������
	m_iState->Initialize();
}