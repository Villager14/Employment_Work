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

#include "Library/Mouse/MouseKeyInput.h"
#include "Library/Keyboard/KeyboardManager.h"

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

	//		�I�u�U�[�o�[�̒ǉ�
	void AddObserver();

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
	std::unordered_map<SceneType, IScene*> m_sceneInformation;

	//		�V�[���^�C�v
	SceneType m_sceneType;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<PostEffectManager> m_postEffectManager;

	//		�}�E�X�L�[����
	std::unique_ptr<MouseKeyInput> m_mouseKeyInput;

	//		�L�[�{�[�h����
	std::unique_ptr<KeyboardManager> m_keyboardInput;
	
	//		�V�[���}�l�[�W���[�̏��
	std::unique_ptr<SceneManagerInformation> m_information;

	//		�v���C�V�[��
	std::unique_ptr<PlayScene> m_playScene;

	//		�^�C�g���V�[��
	std::unique_ptr<TitleScene> m_titleScene;

	//		���U���g�V�[��
	std::unique_ptr<ResultScene> m_resultScene;

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
