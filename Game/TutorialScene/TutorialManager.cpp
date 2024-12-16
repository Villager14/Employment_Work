/*
* @file		TutorialManager.cpp
* @brief	チュートリアル管理
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
	//		生成
	Generation();
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Initialize()
{
	//		チュートリアルをマップに追加
	m_tutorialInformation[TutorialState::Walk] = std::make_unique<TutorialWalkState>(this);

	//		初期の状態(Walk)
	m_tutorialState = TutorialState::Walk;

	//		現在のチュートリアル状態オブジェクトを取得
	m_state = m_tutorialInformation[m_tutorialState].get();

	//		初期化処理
	m_state->Initialize();

	//		レンダラーの生成
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
	//		チュートリアルの情報を生成する
	m_information = std::make_unique<TutorialInformation>();
}
