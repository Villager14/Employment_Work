/*
* @file		MenuManager.cpp
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

#include <Windows.h>

#include "Scene/SceneManager.h"

#include "Library/Mouse/MouseList.h"

MenuManager::MenuManager(SceneManager* sceneManager)
	:
	m_firstAudioMenuJudgement(true),
	m_sceneManager(sceneManager),
	m_menuUseJudgement(false),
	m_menuOpenJudgement(false)
{	
	//		���j���[��UI�̐���
	m_menuUI = std::make_unique<MenuUI>();

	//		���j���[�̗���̐���
	m_menuFlow = std::make_unique<MenuFlow>();

	//		���j���[�̗���̏�����
	m_menuFlow->Initialize();

	//		�}�E�X�̏����̐���
	m_mousePorcess = std::make_unique<MenuMouseProcess>();

	//		UI�̃}�E�X�̓����蔻��̐���
	m_collider = std::make_unique<UIMouseCollider>();

	//		�Q�[���̐ݒ�̐���
	m_gameSetting = std::make_unique<GameSetting>();

	//		���j���[���J���Ă��邩���f����I�u�U�[�o�̐���
	m_menuOpenObserver = std::make_unique<MenuOpenJudgementObserver>();

	//		�I�u�U�[�o�[��ǉ�����
	AddObserver();
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{
	//		���j���[UI�̏���������
	m_menuUI->Initialize();

	//		�}�E�X�̏����̏�����
	m_mousePorcess->Initialize();

	AddMouseObserver();
}

void MenuManager::Update()
{
	//		���j���[���g�p���邱�Ƃ��ł��邩�ǂ���
	if (!m_menuUseJudgement) return;

	if (m_menuFlow->GetMenuStartJudgement())
	{
		//		���j���[�̃I�[�v������
		m_menuOpenObserver->MenuOpen();

		m_menuFlow->SetMenuStartJudgement(false);

		//		����������
		Initialize();

		//		���j���[���g�p���邩�ǂ���
		m_menuOpenJudgement = true;
	}

	//		���j���[�̗���̍X�V
	m_menuFlow->Update();

	//		���j���[���g�p���邩�ǂ���
	if (!m_menuOpenJudgement)
	{
		return;
	}

	//		�}�E�X�̏����̍X�V
	m_mousePorcess->Update();

	//		���j���[UI�̍X�V����
	m_menuUI->Update();

	//		�����蔻��
	m_collider->CollitionProcess(m_menuUI->GetColliderInformation());

	//		���j���[���[�h���I�����邩
	if (m_menuFlow->GetMenuEndJugement())
	{
		//		�I������
		Finalize();

		//		���j���[����鏈��
		m_menuOpenObserver->MenuClose();
	}
}

void MenuManager::Render()
{
	//		���j���[���g�p���Ă��邩�ǂ���
	if (!m_menuOpenJudgement) return;

	m_menuUI->Render();

	//		�f�o�b�N�t�H���g
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionX",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x), 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionY",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y), 0, 30);
}

void MenuManager::Finalize()
{
	//		���j���[�̗���̏I������
	m_menuFlow->Finalize();

	//		���j���[��UI�̏I������
	m_menuUI->Finalize();

	//		�}�E�X�̏����̏I������
	m_mousePorcess->Finalize();

	m_menuOpenJudgement = false;

	//		�}�E�X�L�[�̍폜
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::MenuAudio);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::TabAudio);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::TabOption);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::TabGamePlay);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::ExitButton);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::MenuCloseButton);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeleteKeepPushingObserver(KeyInputMouse::MouseList::Knob);
}

void MenuManager::KeyboardAddObserver()
{
	//		�L�[�{�[�h�I�u�U�[�o�[�ɒǉ�����
	AddKeyboardObserver();
}

void MenuManager::AddObserver()
{
	//		���j���[�w�i�I�u�U�[�o�[�ɒǉ�����i���j���[UI�j
	m_menuFlow->GetMenuBackGroundUIObserver()->AddObserver(m_menuUI.get());
	//		���j���[Tab�I�u�U�[�o�[�ɒǉ�����i���j���[UI�j
	m_menuFlow->GetMenuTabUIObserver()->AddObserver(m_menuUI.get());
	//		�}�E�X�I�u�U�[�o�[�ɒǉ�����i���j���[�j
	m_mousePorcess->AddMenuMouseObserver(m_menuUI.get());
	//		�}�E�X�I�u�U�[�o�[�ɒǉ�����i����j
	m_mousePorcess->AddMenuMouseObserver(m_menuFlow.get());
	//		���j���[�I���I�u�U�[�o�[�ɒǉ�����(���j���[UI)
	m_menuFlow->GetSelectTypeObserver()->AddObserver(m_menuUI.get());
	//		���j���[�^�C�g���I�u�U�[�o�[�ɒǉ�����(���j���[UI)
	m_menuFlow->GetTitleUIUObserver()->AddObserver(m_menuUI.get());
	//		���j���[�A�C�R��UI�I�u�U�[�o�[�ɒǉ�����i���j���[UI�j
	m_menuFlow->AddMenuIconUIObserver(m_menuUI.get());
	//		�}�E�X�I�u�U�[�o�[�ɒǉ�����i�}�E�X�����蔻��j
	m_mousePorcess->AddMenuMouseObserver(m_collider.get());

	//		�����蔻��I�u�U�[�o�[�ɒǉ�����i���j���[�̗���j
	m_collider->AddColliderObserver(m_menuFlow.get());
	//		�����蔻��I�u�U�[�o�[�ɒǉ�����i���j���[UI�j
	m_collider->AddColliderObserver(m_menuUI.get());

	//		�X���C�_�[�̒l��ݒ�ɑ���I�u�U�[�o�[��ǉ�����i�ݒ�j
	m_menuUI->AddSliderSettingValObserver(m_gameSetting.get());
}

void MenuManager::AddMouseObserver()
{
	//		�}�E�X���͏����i���j���[Audio�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::MenuAudio);

	//		�}�E�X���͏����i���j���[TabAudio�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::TabAudio);
	//		�}�E�X���͏����i���j���[TabOption�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::TabOption);
	//		�}�E�X���͏����i���j���[TabGamePlay�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::TabGamePlay);

	//		�}�E�X���͏����i���j���[ButtonExit�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::ExitButton);
	//		�}�E�X���͏����i���j���[ButtonMenuClose�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::MenuCloseButton);

	//		�}�E�X���͏����i���j���[Knob�j
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddKeepPushingObserver(m_menuUI.get(),
			KeyInputMouse::MouseState::keepLeftButton,
			KeyInputMouse::MouseList::Knob);
}

void MenuManager::AddKeyboardObserver()
{
	//		�L�[�{�[�h�̏����̒ǉ�
	m_sceneManager->GetInformation()->GetKeyboardManager()->
		AddKeyboard(m_menuFlow.get(), DirectX::Keyboard::Keys::Tab,
		KeyboardList::MenuOpen, KeyboardManager::Pressed);

	m_sceneManager->GetInformation()->GetKeyboardManager()->
		AddKeyboard(m_menuFlow.get(), DirectX::Keyboard::Keys::Tab,
			KeyboardList::MenuClose, KeyboardManager::Pressed);
}

void MenuManager::MenuUseJudgement(bool judgement)
{
	m_menuUseJudgement = judgement;
}

void MenuManager::MenuOpen()
{
	//		���j���[���J��
	m_menuOpenJudgement = true;
}
