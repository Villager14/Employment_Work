/*
* @file		SceneManager.h
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include <unordered_map>

#include "Scene/IScene.h"

#include "Effect/PostEffect/PostEffectManager.h"

#include "SceneManagerInformation.h"

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
		Tutorial,
	};

private:

	//		�V�[��
	IScene* m_scene;

	//		���j���[�}�l�[�W���[
	std::unique_ptr<MenuManager> m_menuManager;

	//		�V�[���̏��
	std::unordered_map<SceneType, std::unique_ptr<IScene>> m_sceneInformation;

	//		�V�[���^�C�v
	SceneType m_sceneType;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<PostEffectManager> m_postEffectManager;
	
	//		�V�[���}�l�[�W���[�̏��
	std::unique_ptr<SceneManagerInformation> m_information;

public:

	/*
	*	�V�[����؂�ւ���
	* 
	*	@param	(type)	���̃V�[��
	*/
	void ChangeScene(SceneType type);

	/*
	*	�V�[���}�l�[�W���̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	SceneManagerInformation* GetInformation() { return m_information.get(); }
};
