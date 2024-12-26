/*
* @file		SceneManagerInformation.h
* @brief	�V�[���}�l�[�W���[�̏��
* @author	Morita
* @date		2024/11/08
*/

#pragma once

#include "pch.h"

#include "Effect/PostEffect/PostEffectManager.h"

#include "Library/Mouse/MouseKeyInput.h"

#include "Library/Keyboard/KeyboardManager.h"

#include "Game/Menu/MenuManager.h"

class SceneManagerInformation
{
public:

	//		�R���X�g���N�^
	SceneManagerInformation()
		:
		m_clearTime(0),
		m_deathCount(0),
		m_maxTime(0),
		m_endJudgement(false),
		m_postEffectManager{ nullptr },
		m_menuManager{ nullptr },
		m_mouseKeyInput{ nullptr }
	{}

	//		�f�X�g���N�^
	~SceneManagerInformation() {};

	/*
	*	����������
	*
	*	@param	(postEffectManager)	�|�X�g�G�t�F�N�g�}�l�[�W���̃|�C���^
	*	@param	(m_mouseKeyInput)	�}�E�X�̃L�[���͏����̃|�C���^
	*/
	void Initialize(PostEffectManager* postEffectManager,
		MenuManager* menuManager,
		MouseKeyInput* mouseKeyInput,
		KeyboardManager* keyboardManager)
	{
		m_postEffectManager = postEffectManager;
		m_menuManager = menuManager;
		m_mouseKeyInput = mouseKeyInput;
		m_keyboardManager = keyboardManager;
	}

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	PostEffectManager* m_postEffectManager;

	//		�}�E�X�̃L�[���͏����̃|�C���^
	MouseKeyInput* m_mouseKeyInput;

	//		�L�[�{�[�h�̃L�[���͏����̃|�C���^
	KeyboardManager* m_keyboardManager;

	//		���j���[�}�l�[�W���[�̃|�C���^
	MenuManager* m_menuManager;

	//        �N���A�^�C��
	int m_clearTime;

	//        ���S�J�E���g
	int m_deathCount;

	//		�ő�^�C��
	int m_maxTime;

	//		�Q�[�����I�����邩
	bool m_endJudgement;

public:

	/*
	*	�|�X�g�G�t�F�N�g���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectManager* GetPostEffectManager() { return m_postEffectManager; }

	/*
	*	�}�E�X�L�[���͂��󂯎��
	*
	*	@return �}�E�X�̃L�[���͂̃|�C���^
	*/
	MouseKeyInput* GetMouseKeyInput() { return m_mouseKeyInput; }

	/*
	*	�L�[�{�[�h���͂��󂯎��
	* 
	*	@return �L�[�{�[�h�̃L�[���͂̃|�C���^
	*/
	KeyboardManager* GetKeyboardManager() { return m_keyboardManager; }

	/*
	*	���j���[�}�l�[�W���[���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuManager* GetMenuManager() { return m_menuManager; }

	/*
	*    �N���A�^�C����ݒ肷��
	*
	*    @param    (time)    ����
	*/
	void SetClearTime(int time) { m_clearTime = time; }

	/*
	*    �N���A�^�C�����󂯎��
	*
	*    @return ����
	*/
	int GetClearTime() { return m_clearTime; }

	/*
	*    ���S�񐔂�ݒ肷��
	*
	*    @param    (count)    ��
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*    ���S�񐔂��󂯎��
	*
	*    @return ��
	*/
	int GetDeathCount() { return m_deathCount; }

	/*
	*	�ő厞�Ԃ�ݒ肷��
	*	
	*	@param	(time)	����
	*/
	void SetMaxTime(int time) { m_maxTime = time; }

	/*
	*	�ő厞�Ԃ��󂯎��
	* 
	*	@return ����
	*/
	int GetMaxTime() { return m_maxTime; }

	/*
	*	�Q�[�����I�����邩�ݒ肷��
	* 
	*	@param	(judgement)	true : �I������ false : �I�����Ȃ�
	*/
	void SetEndJudgement(bool judgement) { m_endJudgement = judgement; }

	/*
	*	�Q�[�����I�����邩�󂯎��
	* 
	*	@return true : �I������ false : �I�����Ȃ�
	*/
	bool GetEndJudgement() { return m_endJudgement; }
};