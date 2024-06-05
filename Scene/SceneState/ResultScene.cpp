/*
* @file		ResultScene.h
* @brief	���U���g�V�[��
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

	//		�X�R�A�̌v�Z������
	m_score = ScoreCalculation(m_sceneManager->GetDeathCount(), time);

	//		���U���g�}�l�[�W���[�̐���
	m_resultManager = std::make_unique<ResultManager>();

	//		���U���g�}�l�[�W���[�̏�����
	m_resultManager->Initialize(static_cast<int>(m_score), m_sceneManager->GetClearTime(),
								m_sceneManager->GetDeathCount());
}

void ResultScene::Update()
{
	//		���U���g�}�l�[�W���[�̍X�V����
	m_resultManager->Update();
}

void ResultScene::Render()
{
	//		���U���g�}�l�[�W���[�̕`�揈��
	m_resultManager->Render();
}

void ResultScene::Finalize()
{
}

float ResultScene::ScoreCalculation(int count, float score)
{
	//		�O�̏ꍇ�l�����ǂ�
	if (count == 0) return score;

	score = ScoreCalculation(count - 1, score);

	//	 Score * -3%
	score *= 0.97f;

	return score;
}
