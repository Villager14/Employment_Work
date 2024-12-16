/*
* @file		TitleFlowManager.cpp
* @brief	�^�C�g���̗���}�l�[�W���[
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleFlowManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleFlowManager::TitleFlowManager()
	:
	m_iState(nullptr),
	m_state(State::StartState),
	m_fadeInEndJudgement(false),
	m_keyInputJudgement(false),
	m_time(0.0f),
	m_scrollWheel(0)
{
	//		�^�C�g��UI�I�u�U�[�o�[�̐���
	m_titleUIObserver = std::make_unique<TitleUIObserver>();

	//		�t�F�[�h�I�u�U�[�o�[�̐���
	m_fadeObserver = std::make_unique<FadeObserver>();

	//		�Q�[���I���I�u�U�[�o�[
	m_gameExitObserver = std::make_unique<TitleGameExitObserver>();

	//		���j���[�g�p�I�u�U�[�o�[
	m_menuUseObserver = std::make_unique<TitleMenuUseObserver>();

	//		�^�C�g���v���C���[�A�j���[�V�����I�u�U�[�o�[
	m_animationObserver = std::make_unique<TitlePlayerAnimationObserver>();
}

TitleFlowManager::~TitleFlowManager()
{
}

void TitleFlowManager::Initialize()
{
	//		�t�F�[�h�C�����I�����Ă��Ȃ���Ԃɂ���
	m_fadeInEndJudgement = false;

	//		�ړ��󋵂͉����Ȃ���Ԃɂ��Ă���
	m_selectionBarMoveDirection = SelectionBarMoveDirection::Not;

	//		��Ԃ̏���ݒ肷��
	m_stateInformation.insert({ State::PlayState, std::make_unique<SelectPlayState>(this) });
	m_stateInformation.insert({ State::EndState, std::make_unique<SelectEndState>(this) });
	m_stateInformation.insert({ State::SettingState, std::make_unique<SelectSettingState>(this) });
	m_stateInformation.insert({ State::StartState, std::make_unique<StartSceneState>(this) });
	m_stateInformation.insert({ State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		�����̏��
	m_state = State::StartState;

	//		��Ԃ̍X�V
	m_iState = m_stateInformation[m_state].get();

	//		����������
	m_iState->Initialize();
}

void TitleFlowManager::Update()
{
	//		���݂̏�Ԃ̍X�V
	m_iState->Update();
}

void TitleFlowManager::Finalize()
{
	m_fadeInEndJudgement = false;
	m_keyInputJudgement = false;
	m_scrollWheel = 0;

	//		�I�u�U�[�o�[�̍폜
	m_titleUIObserver->Dalete();
	m_gameExitObserver->Dalete();
	m_fadeObserver->Dalete();
	m_menuUseObserver->Dalete();
}

void TitleFlowManager::FadeIn()
{
	//		�t�F�[�h�C���̏I��
	m_fadeInEndJudgement = true;
}

void TitleFlowManager::FadeOut()
{

}

void TitleFlowManager::InputKey()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		S�{�^��OR�}�E�X�z�C�[����ŏ�Ɉړ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S) || 
		m_scrollWheel < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		�����ړ����������Ă���ꍇ�͏��������Ȃ�
		if (!m_keyInputJudgement)
		{
			//		�L�[�������Ă���
			m_keyInputJudgement = true;
			//		�ړ���������i��j
			m_selectionBarMoveDirection = SelectionBarMoveDirection::Up;

			//		�I�����ʉ�
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		m_scrollWheel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}

	//		W�{�^��OR�}�E�X�z�C�[�������ŉ��Ɉړ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W) ||
		m_scrollWheel > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		�����ړ����������Ă���ꍇ�͏��������Ȃ�
		if (!m_keyInputJudgement)
		{
			//		�L�[�������Ă���
			m_keyInputJudgement = true;

			//		�ړ���������i���j
			m_selectionBarMoveDirection = SelectionBarMoveDirection::Down;

			//		�I�����ʉ�
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		//		�z�C�[���̒l���X�V����
		m_scrollWheel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}
}

bool TitleFlowManager::SelectionBarMoveProcess()
{
	//		�ړ�������Not�̏ꍇ�ړ����Ȃ�
	if (m_selectionBarMoveDirection == SelectionBarMoveDirection::Not) return false;

	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	m_menuUseObserver->DisableMenu();

	//		�ړ����x
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		�ړ���������̏ꍇ
	if (m_selectionBarMoveDirection == SelectionBarMoveDirection::Up)
	{
		m_titleUIObserver->UpSelect(m_time);
	}
	//		�ړ����������̏ꍇ
	else
	{
		m_titleUIObserver->DownSelect(m_time);
	}

	if (m_time >= 1.0f)
	{
		//		���j���[���g�p�ł���悤�ɂ���
		m_menuUseObserver->EnableMenu();

		return true;
	}

	return false;
}

void TitleFlowManager::SelectionInfromationReset()
{
	m_time = 0.0f;

	m_selectionBarMoveDirection = SelectionBarMoveDirection::Not;

	m_keyInputJudgement = false;
}

void TitleFlowManager::ChangeState(State state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_iState->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		��Ԃ�؂�ւ���
	m_iState = m_stateInformation[m_state].get();

	//		�V������Ԃ̏���������������
	m_iState->Initialize();
}