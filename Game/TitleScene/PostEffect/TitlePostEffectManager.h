/*
* @file		TitlePostEffectManager.h
* @brief	�^�C�g���|�X�g�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectManager.h"

#include "../Observer/TitlePostEffectObserver/TitlePostEffectObserver.h"

#include "../Observer/FadeObserver/IFadeObserver.h"

class TitlePostEffectManager : public IFadeObserver
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(postEffectManager)	�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	*/
	TitlePostEffectManager(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~TitlePostEffectManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	/*
	*	�|�X�g�G�t�F�N�g���g�p���邩�ǂ���
	* 
	*	@param	(int)	�t���O�ԍ�
	*	return true : �g�p����@false : �g�p���Ȃ�
	*/
	bool PostEffectUseJudgement(int postEffectFlag);

	/*
	*	�|�X�g�G�t�F�N�g�̍X�V
	* 
	*	@param	(int)	�t���O�ԍ�	
	*/
	void PostEffectUpdate(int postEffectFlag);

	/*
	*	�|�X�g�G�t�F�N�g�̕`�揈��
	*
	*	@param	(int)	�t���O�ԍ�
	*/
	void PostEffectRender(int postEffectFlag);

	//		�|�X�g�G�t�F�N�g�̃e�N�X�`���`�揈��
	void PostEffectTextureRender();

	//		�V�[���ύX�t�F�[�h�A�E�g
	void SceneEndFadeOut() override;

	//		�t�F�[�h�A�E�g
	void FadeOut() override;

	void Finalize();

private:

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_posteffectFlag;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

	//		�^�C�g���|�X�g�G�t�F�N�g�I�u�U�[�o�[
	std::unique_ptr<TitlePostEffectObserver> m_titlePostEffectObserver;

public:

	/*
	*	�^�C�g���|�X�g�G�t�F�N�g�I�u�U�[�o�[��ǉ�����
	* 
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddTitlePostEffectObserver(ITitlePostEffectObserver* observer) { m_titlePostEffectObserver->AddObserver(observer); };
};