/*
* @file		ResultScene.h
* @brief	リザルトシーン
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultScene.h"

ResultScene::ResultScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager),
	m_score(0.0f)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	float time = static_cast<float>(m_sceneManager->GetClearTime());

	time = 5999 - time;

	time *= 1.5f;

	//		スコアの計算をする
	m_score = ScoreCalculation(m_sceneManager->GetDeathCount(), time);

	//		リザルトマネージャーの生成
	m_resultManager = std::make_unique<ResultManager>();

	//		リザルトマネージャーの初期化
	m_resultManager->Initialize(static_cast<int>(m_score), m_sceneManager->GetClearTime(),
								m_sceneManager->GetDeathCount());
}

void ResultScene::Update()
{
	//		リザルトマネージャーの更新処理
	m_resultManager->Update();
}

void ResultScene::Render()
{
	//		リザルトマネージャーの描画処理
	m_resultManager->Render();
}

void ResultScene::Finalize()
{
}

float ResultScene::ScoreCalculation(int count, float score)
{
	//		０の場合値をもどす
	if (count == 0) return score;

	score = ScoreCalculation(count - 1, score);

	//	 Score * -3%
	score *= 0.97f;

	return score;
}
