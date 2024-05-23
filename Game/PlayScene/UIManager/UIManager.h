/*
* @file		UIManager.h
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Clock/ClockManager.h"

#include "CoolTime/CoolTime.h"

#include "Fade/FadeIn.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/UIManager/GameOver/GameOverManager.h"

#include "Game/PlayScene/UIManager/ScreenRay/ScreenRay.h"

class UIManager
{
public:
	//		�R���X�g���N�^
	UIManager(PlayerInformation* playerInformation, GameManager* gameManager);

	//		�f�X�g���N�^
	~UIManager();

	//		��������
	void Initialize();

	void Update();

	void FrontRender();

	void BackRender();

private:
	//		���v�̔w�i
	std::unique_ptr<ClockManager> m_clockManager;

	//		�N�[���^�C��
	std::unique_ptr<CoolTime> m_coolTime;

	//		�t�F�[�h
	std::unique_ptr<FadeIn> m_fadeIn;
		
	//		�Q�[���I�[�o�[
	std::unique_ptr<GameOverManager> m_gameOver;

	//		�X�N���[���̃��C
	std::unique_ptr<ScreenRay> m_screenRay;

	//		�v���C���[�̏����󂯎��
	PlayerInformation* m_playerInformation;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;
};