/*
* @file		TitleSceneChange.h
* @brief	�^�C�g���̃V�[���ύX
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Scene/SceneManager.h"

#include "../Observer/TitlePostEffectObserver/ITitlePostEffectObserver.h"

#include "../Observer/GameExitObserver/ITitleGameExitObserver.h"

class TitleSceneChange : public ITitlePostEffectObserver,
						 public ITitleGameExitObserver
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(sceneManager)	�V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	TitleSceneChange(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~TitleSceneChange();

	//	�t�F�[�h�C��
	void FadeIn() override;

	//		�t�F�[�h�A�E�g
	void FadeOut() override;

	//		�Q�[���I��
	void GameExit() override;
private:

	//		�V�[���}�l�[�W���[
	SceneManager* m_sceneManager;
};