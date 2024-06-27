/*
* @file		GameClearManager.cpp
* @brief	ゲームクリアマネージャー
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "GameClearManager.h"


GameClearManager::GameClearManager(GameManager* gameManager)
	:
	m_gameManager(gameManager),
	m_elapsedTime(0.0f),
	m_scale(0.0f),
	m_move(0.0f)
{
}

GameClearManager::~GameClearManager()
{
}

void GameClearManager::Initialize()
{
	for (int i = 0; i < 6; ++i)
	{
		//		UI描画の生成
		m_gameOverRender.push_back(std::make_unique<UIRender>());
	}

	//		UI描画の作製(Continue)
	m_gameOverRender[0]->Create(L"Resources/Texture/UI/GameClear/Messege.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		UI描画の作製()Continue
	m_gameOverRender[1]->Create(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, 13.0f }, { 0.0f, 1.0f });

	//		UI描画の作製()Continue
	m_gameOverRender[2]->Create(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, -13.0f }, { 0.0f, 1.0f });

	//		UI描画の作製()Continue
	m_gameOverRender[3]->Create(L"Resources/Texture/UI/GameClear/messegeBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 0.0f });

	m_centerShader = std::make_unique<CenterShader>();

	m_centerShader->Create(L"Resources/Texture/UI/GameClear/Messege.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		グリッチシェーダーの生成
	m_glitchShader = std::make_unique<GlitchShader>();

	//		グリッチシェーダーの作製
	m_glitchShader->Create(L"Resources/Texture/UI/GameClear/Messege.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void GameClearManager::Update()
{
	//		ゲームクリア状態ではないなら処理をしない
	if (!m_gameManager->GetGoalJudgement()) return;

	if (m_scale < 1.0f)
	{

		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

		float move = 0.0f;

		if (m_scale == 1.0f)
		{
			move = 1.0f;
		}
		else
		{
			move = 1.0f - pow(2.0f, -10.0f * m_scale);
		}


		m_gameOverRender[1]->SetSize({ move, 1.0f });
		m_gameOverRender[2]->SetSize({ move, 1.0f });
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float move = 0.0f;

		if (m_move == 1.0f)
		{
			move = 1.0f;
		}
		else
		{
			move = 1.0f - pow(2.0f, -10.0f * m_move);
		}

		m_gameOverRender[1]->SetPosition({ 0.0f, Library::Lerp(13.0f, 300.0f, move) });
		m_gameOverRender[2]->SetPosition({ 0.0f, Library::Lerp(-13.0f, -300.0f, move) });
		m_gameOverRender[3]->SetSize({ 1.0f, move });
		m_centerShader->SetTime(move);
	}

}

void GameClearManager::Render()
{
	//		ゲームクリア状態ではないなら処理をしない
	//if (!m_gameManager->GetGoalJudgement()) return;
	
	m_gameOverRender[3]->Render();

	m_centerShader->Render();

	m_gameOverRender[1]->Render();
	m_gameOverRender[2]->Render();


	//m_glitchShader->Render();
}

void GameClearManager::Finalize()
{
}
