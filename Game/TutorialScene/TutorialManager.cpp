/*
* @file		TutorialManager.cpp
* @brief	チュートリアル管理
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "TutorialManager.h"

#include "Scene/SceneManager.h"

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
}

void TutorialManager::Update()
{

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
