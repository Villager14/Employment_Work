/*
* @file		MenuManager.h
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include <unordered_map>

#include "UI/MenuUI.h"

#include "Flow/MenuFlow.h"

#include "Mouse/MenuMouseProcess.h"

#include "Collider/UIMouseCollider.h"

#include "Setting/GameSetting.h"

#include "Game/Observer/Menu/MenuOpenJudgementObserver/MenuOpenJudgementObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/IMenuUsedObserver.h"
#include "Game/Observer/Menu/MenuOpenObserver/IMenuOpenObserver.h"

class SceneManager;

class MenuManager : public IMenuUsedObserver,
					public IMenuOpenObserver
{
public:
	//		�R���X�g���N�^
	MenuManager(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~MenuManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�L�[�{�[�h�I�u�U�[�o�[�ɓo�^����
	void KeyboardAddObserver();
	
	//		���j���[���g�����Ƃ��ł��邩���f����
	void MenuUseJudgement(bool judgement) override;

	//		���j���[���J���Ă���
	void MenuOpen() override;

private:

	//		�I�u�U�[�o�[�̒ǉ�
	void AddObserver();

	//		�}�E�X���͂̃I�u�U�[�o�[�̒ǉ�
	void AddMouseObserver();

	//		�L�[�{�[�h���͂̃I�u�U�[�o�[�̒ǉ�
	void AddKeyboardObserver();

private:

	//		�V�[���}�l�[�W��
	SceneManager* m_sceneManager;

	//		���j���[UI
	std::unique_ptr<MenuUI> m_menuUI;

	//		���j���[�̗���
	std::unique_ptr<MenuFlow> m_menuFlow;

	//		�}�E�X�̏���
	std::unique_ptr<MenuMouseProcess> m_mousePorcess;

	//		�����蔻��
	std::unique_ptr<UIMouseCollider> m_collider;

	//		���j���[�I�[�v���I�u�U�[�o�[
	std::unique_ptr<MenuOpenJudgementObserver> m_menuOpenObserver;

	//		�Q�[���̐ݒ�
	std::unique_ptr<GameSetting> m_gameSetting;

	//		���j���[���g�p�ł��邩
	bool m_menuUseJudgement;

	//		���߂ĉ��y���j���[���J���Ă��邩�ǂ���
	bool m_firstAudioMenuJudgement;

	//		���j���[���J�����ǂ���
	bool m_menuOpenJudgement;

public:

	/*
	*	Audio���j���[�����j���[���J��������x�����s���������󂯎��
	* 
	*	@retun	true : �s�� false : �s��Ȃ�
	*/
	bool GetFirstAudioMenuJudgement() { return m_firstAudioMenuJudgement; }

	/*
	*	Audio���j���[�����j���[���J��������x�����s��������ݒ肷��
	*
	*	@param	(judgement)	true : �s�� false : �s��Ȃ�
	*/
	void SetFirstAudioMenuJudgement(bool judgement) { m_firstAudioMenuJudgement = judgement; }

	/*
	*	�V�[���}�l�[�W���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	SceneManager* GetSceneManager() { return m_sceneManager; }

	/*
	*	���j���[�I�[�v���I�u�U�[�o�[��ǉ�����
	* 
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddMenuOpenObserver(IMenuOpenJudgementObserver* observer) { m_menuOpenObserver->AddObserver(observer); }

	/*
	*	�J�����̎���p�̃I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddCameraViewAngle(IMenuCameraViewAngle* observer) { m_gameSetting->AddCameraViewAngle(observer); }

	/*
	*	�J�����̑��x�̃I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddCameraSpeed(IMenuCameraSpeed* observer) { m_gameSetting->AddCameraSpeed(observer); }
};