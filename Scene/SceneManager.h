/*
* @file		SceneManager.h
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include <unordered_map>

#include "Scene/IScene.h"

#include "SceneState/PlayScene.h"
#include "SceneState/TitleScene.h"
#include "SceneState/ResultScene.h"

class PlayScene;
class TitleScene;
class ResultScene;

#include "Game/Menu/MenuManager.h"

class SceneManager
{
public:
	//		�R���X�g���N�^
	SceneManager();

	//		�f�X�g���N�^
	~SceneManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	enum SceneType
	{
		Title,
		Play,
		Result,
	};

private:

	//		�V�[��
	IScene* m_scene;

	//		���j���[�}�l�[�W���[
	std::unique_ptr<MenuManager> m_menuManager;

	//        �N���A�^�C��
	int m_clearTime;

	//        ���S�J�E���g
	int m_deathCount;

	std::unique_ptr<bool> m_menuJudgement;

	//		���j���[���g���邩�ǂ������f����
	bool m_menuUseJudgement;

	//		�V�[���̏��
	std::unordered_map<SceneType, std::unique_ptr<IScene>> m_sceneInformation;

	//		�V�[���^�C�v
	SceneType m_sceneType;

public:

	void ChangeScene(SceneType type);

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
	*	���j���[���J���Ă��邩�ǂ����󂯎��
	* 
	*	@return true : �J���Ă��� false : �J���Ă��Ȃ�
	*/
	bool* GetMenuJudgement() 
	{ 
		return m_menuJudgement.get(); }

	/*
	*	���j���[���J���Ă��邩�ǂ����ݒ肷��
	*
	*	@param	(judgement) true : �J���Ă��� false : �J���Ă��Ȃ�
	*/
	//void SetMenuJudgement(bool judgement) { m_menuJudgement = judgement; }

	/*
	*	���j���[���g���邩�ǂ������f����
	* 
	*	@return true : �g���� false : �g���Ȃ�
	*/
	bool GetMenuUseJudgement() { return m_menuUseJudgement; }

	/*
	*	���j���[���g���邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement)	true : �g���� false : �g���Ȃ�
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }
};
