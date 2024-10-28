/*
* @file		PlayScene.h
* @brief	�v���C�V�[��
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"
#include "Game/PlayScene/UIManager/UIManager.h"
#include "Game/PlayScene/Enemy/EnemyManager.h"
#include "Game/Camera/PlaySceneCamera/PlayerCameraManager.h"
#include "Game/PlayScene/Player/Player.h"
#include "Game/PlayScene/ObjectManager/ObjectManager.h"
#include "Game/PlayScene/CollitionManager/CollitionManager.h"
//#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"
#include "Library/Effect/PostEffect/PostEffectManager.h"
#include "Game/PlayScene/Effect/EffectManager.h"
#include "Game/PlayScene/Respawn/RespawnManager.h"

#include "Library/Effect/PostEffect/PostEffectFlag.h"

#include "../SceneManager.h"

#include "Scene/IScene.h"

class SceneManager;

class PlayScene : public IScene
{
public:
	/*
	*	�R���X�g���N�^
	* 
	*	@param	(sceneManager) �V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	PlayScene(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~PlayScene();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	void Generation();

	//		���j���[�̏��
	bool MenuInformation();

private:
	//		�V�[���}�l�[�W���[
	SceneManager* m_sceneManager;

	//		�v���C���[�̃J�����}�l�[�W���[
	std::unique_ptr<PlayerCameraManager> m_playerCameraManager;

	//		�v���C���[
	std::unique_ptr<Player> m_player;

	//		�I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager> m_objectManager;

	//		�����蔻��I�u�W�F�N�g
	std::unique_ptr<CollitionManager> m_collitionManager;

	//		�G�l�~�[�}�l�[�W���[
	std::unique_ptr<EnemyManager> m_enemyManager;

	//		UI�}�l�[�W���[
	std::unique_ptr<UIManager> m_uiManager;

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[
	//std::unique_ptr<ScreenEffectManager> m_screenEffectManager;
	
	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<PostEffectManager> m_postEffectManager;
	//		�Q�[���}�l�[�W���[
	std::unique_ptr<GameManager> m_gameManager;

	//		�G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<EffectManager> m_effectManager;

	//		���X�|�[���}�l�[�W���[
	std::unique_ptr<RespawnManager> m_respawnManager;

	bool m_menuCloseJugement;
};