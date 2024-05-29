/*
* @file		SceneManager.h
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "IScene.h"

#include "SceneState/PlayScene.h"

#include "SceneState/TitleScene.h"

#include "SceneState/ResultScene.h"

class PlayScene;

class TitleScene;

class ResultScene;

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

	//		��Ԃ�؂�ւ���
	void ChangeState(IScene* scene);

private:
	//		�V�[��
	IScene* m_scene;

	//		�v���C�V�[��
	std::unique_ptr<PlayScene> m_playScene;

	//		�^�C�g���V�[��
	std::unique_ptr<TitleScene> m_titleScene;

	//		���U���g�V�[��
	std::unique_ptr<ResultScene> m_resultScene;

public:

	/*
	*	�v���C�V�[�����󂯎��
	*
	*	@return �v���C�V�[���̃C���X�^���X�̃|�C���^
	*/
	PlayScene* GetPlayScene() { return m_playScene.get(); }

	/*
	*	�^�C�g���V�[�����󂯎��
	* 
	*	@return �^�C�g���V�[���̃C���X�^���X�̃|�C���^
	*/
	TitleScene* GetTitleScene() { return m_titleScene.get(); }

	/*
	*	���U���g�V�[�����󂯎��
	* 
	*	@return ���U���g�V�[���̃C���X�^���X�̃|�C���^
	*/
	ResultScene* GetResultScene() { return m_resultScene.get(); }

private:

	//		�N���A�^�C��
	int m_clearTime;

	//		���S��
	int m_deathCount;

public:

	/*
	*	�N���A�^�C����ݒ肷��
	* 
	*	@param	(time)	����
	*/
	void SetClearTime(int time) { m_clearTime = time; }

	/*
	*	�N���A�^�C�����󂯎��
	* 
	*	@return ����
	*/
	int GetClearTime() { return m_clearTime; }

	/*
	*	���S�񐔂�ݒ肷��
	* 
	*	@param	(count)	��
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*	���S�񐔂��󂯎��
	* 
	*	@return ��
	*/
	int GetDeathCount() { return m_deathCount; }
};
