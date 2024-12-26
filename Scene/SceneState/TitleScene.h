/*
* @file		TitleScene.h
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/TitleScene/UI/TitleUI.h"

#include "Game/TitleScene/Flow/TitleFlowManager.h"

#include "Game/TitleScene/PostEffect/TitlePostEffectManager.h"

#include "Game/TitleScene/SceneChange/TitleSceneChange.h"

#include "Game/TitleScene/Menu/TitleMenuManagement.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Game/TitleScene/Player/TItlePlayer.h"

#include "Game/TitleScene/Effect/TitleEffectManager.h"

#include "Game/TitleScene/Camera/TitleCameraManager.h"

#include "Game/Observer/Menu/MenuOpenJudgementObserver/IMenuOpenJudgementObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/MenuUsedObserver.h"

#include "Game/Observer/Menu/MenuOpenObserver/MenuOpenObserver.h"

class SceneManager;

class TitleScene : public IScene,
				   public IMenuOpenJudgementObserver
{
public:

	//		�R���X�g���N�^
	TitleScene(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~TitleScene();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�I�u�U�[�o�[�̒ǉ�
	void AddObserver();

	//		���j���[���J���Ă���
	void MenuOpen() override;

	//		���j���[����Ă���
	void MenuClose() override;

private:
	//		�V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	SceneManager* m_sceneManager;

	//		�^�C�g����UI����
	std::unique_ptr<TitleUI> m_titleUI;

	//		�^�C�g���̗���}�l�[�W���[
	std::unique_ptr<TitleFlowManager> m_titleFlowManager;

	//		�^�C�g���|�X�g�G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<TitlePostEffectManager> m_titlePostEffectManager;

	//		�^�C�g���V�[���̃`�F���W
	std::unique_ptr<TitleSceneChange> m_titleSceneChange;

	//		���j���[�}�l�W�����g
	std::unique_ptr<TitleMenuManagement> m_menuManagement;

	//		�I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager> m_objectManager;

	//		�^�C�g���̃v���C���[
	std::unique_ptr<TitlePlayer> m_player;

	//		�^�C�g���G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<TitleEffectManager> m_titleEffectManager;

	//		�J�����}�l�[�W���[
	std::unique_ptr<TitleCameraManager> m_cameraManager;

	//		���j���[���g�������f����I�u�U�[�o�[
	std::unique_ptr<MenuUsedObserver> m_menuUsedObserver;

	//		���j���[���J���I�u�U�[�o�[
	std::unique_ptr<MenuOpenObserver> m_menuOpenObserver;

public:

	/*
	*	���j���[���g�p�ł��邩���f����I�u�U�[�o�[
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuUsedObserver* GetMenuUsedObserver() { return m_menuUsedObserver.get(); }

	/*
	*	���j���[���J���I�u�U�[�o�[���󂯎��
	* 
	*	@param	(observer)	�C���X�^���X�̃|�C���^
	*/
	void AddMenuOpenObserver(IMenuOpenObserver* observer) { m_menuOpenObserver->AddObserver(observer); }
};
 