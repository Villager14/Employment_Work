/*
* @file		UIManager.h
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Fade/FadeIn.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/StandardShader.h"

class ClockManager;
class CoolTime;
class GameOverManager;
class GameClearManager;

class UIManager
{
public:
	//		�R���X�g���N�^
	UIManager(PlayerInformation* playerInformation, GameManager* gameManager);

	//		�f�X�g���N�^
	~UIManager();

	//		��������
	void Initialize();

	//		�X�V����
	void Update();

	void FrontRender();

	void BackRender();

	//		UI�e�N�X�`���̍쐻
	void CreateStandardUITexture();

public:

	enum UIType
	{
		ClockBackGround,		//		���v�̔w�i
		ClockColon,				//		���v�̃R����
		CloolTimeBackGround,	//		�N�[���^�C���̔w�i
		GameOver,				//		�Q�[���I�[�o�[
		GameOverContinue,		//		�Q�[���I�[�o�[�̃R���e�B�j���[
		NextInduction,			//		���̏�Ԃ̗U��
		ScreenRay,				//		�X�N���[���̃��C
		GameClearBarUnder,		//		�Q�[���N���A�̃o�[
		GameClearBarUp,			//		�Q�[���N���A�̃o�[		
		GameClearBackGround,	//		�Q�[���N���A�̔w�i
	}; 

private:
	//		���v�̔w�i
	std::unique_ptr<ClockManager> m_clockManager;

	//		�N�[���^�C��
	std::unique_ptr<CoolTime> m_coolTime;

	//		�t�F�[�h
	std::unique_ptr<FadeIn> m_fadeIn;
		
	//		�Q�[���I�[�o�[
	std::unique_ptr<GameOverManager> m_gameOver;

	//		�v���C���[�̏����󂯎��
	PlayerInformation* m_playerInformation;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		�Q�[���N���A�}�l�[�W���[
	std::unique_ptr<GameClearManager> m_clearManager;

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	�X�^���_�[�h�V�F�[�_�[���󂯎��
	* 
	*	@return �X�^���_�[�h�V�F�[�_�[���󂯎��
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

};