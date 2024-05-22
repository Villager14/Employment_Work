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

#include "Game/PlayScene/Player/Player.h"

class UIManager
{
public:
	//		�R���X�g���N�^
	UIManager(Player* player);

	//		�f�X�g���N�^
	~UIManager();

	//		��������
	void Initialize();

	void Update();

	void Render();

private:
	//		���v�̔w�i
	std::unique_ptr<ClockManager> m_clockManager;

	//		�N�[���^�C��
	std::unique_ptr<CoolTime> m_coolTime;

	std::unique_ptr<FadeIn> m_fadeIn;

	//		�v���C���[�̏����󂯎��
	Player* m_player;
};