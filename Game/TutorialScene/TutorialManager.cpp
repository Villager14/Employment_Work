/*
* @file		TutorialManager.cpp
* @brief	�`���[�g���A���Ǘ�
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "TutorialManager.h"

#include "Scene/SceneManager.h"

#include "Test/ObjectMoveR.h"

TutorialManager::TutorialManager(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
	//		����
	Generation();
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Initialize()
{
	//		�`���[�g���A�����}�b�v�ɒǉ�
	m_tutorialInformation[TutorialState::Walk] = std::make_unique<TutorialWalkState>(this);

	//		�����̏��(Walk)
	m_tutorialState = TutorialState::Walk;

	//		���݂̃`���[�g���A����ԃI�u�W�F�N�g���擾
	m_state = m_tutorialInformation[m_tutorialState].get();

	//		����������
	m_state->Initialize();

	//		�����_���[�̐���
	m_renderer = std::make_unique<Renderer>();

	m_objectMove.push_back(std::unique_ptr<ObjectMoveR>());

	m_object = std::make_unique<RendererObject>(1);
	m_object2 = std::make_unique<RendererObject>(22222);

	m_object->Initialize();
	m_object2->Initialize();

	m_renderer->SetRenderer(m_object.get());
	m_renderer->SetRenderer(m_object2.get());
}

void TutorialManager::Update()
{
	m_renderer->AllRender();
}

void TutorialManager::Render()
{
}

void TutorialManager::Finalize()
{
}

void TutorialManager::Generation()
{
	//		�`���[�g���A���̏��𐶐�����
	m_information = std::make_unique<TutorialInformation>();
}
