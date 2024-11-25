/*
* @file		TitleSelectManager.h
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include <unordered_map>

#include "ITitleSelect.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "Library/Shader/StandardShader.h"

#include "Game/Menu/MenuInformation.h"

#include "TitleInformation.h"

#include "TitleCommonProcess.h"

#include "Library/Animation/AnimationManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectManager.h"

class TitleUIManager;

class TitleSelectManager
{
public:

	//		�R���X�g���N�^
	TitleSelectManager(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~TitleSelectManager();

	//		����������
	void Initialize();

	//		����
	void Generation();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	void CreateStandardShader();

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(TitleInformation::State state);

private:

	//		�I��
	ITitleSelect* m_iState;

	//		���݂̏��
	TitleInformation::State m_state;

	//		���j���[�̏��
	MenuInformation* m_menuInformation;

	//		���
	std::unique_ptr<TitleInformation> m_information;

	//		�w�i�ړ�����
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		�^�C�g��UI�}�l�[�W���[
	std::unique_ptr<StandardShader<TitleInformation::TitleUIType>> m_standardShader;

	//		���ʏ���
	std::unique_ptr<TitleCommonProcess> m_commonProcess;

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_posteffectFlag;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

public:

	/*
	*	�^�C�g���̏����󂯎��
	* 
	*	@return	�C���X�^���X�̃|�C���^
	*/
	TitleInformation* GetInformation() { return m_information.get(); }

	/*
	*	���j���[�̏���ݒ肷��
	* 
	*	@param	(information)	�J�����̃C���X�^���X�̃|�C���^
	*/
	void SetMenuInformation(MenuInformation* information) { m_menuInformation = information; }

	/*
	*	���j���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuInformation* GetMenuInformation() { return m_menuInformation; }

	/*
	*	�^�C�g�����ʏ������󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	TitleCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	�A�j���[�V�������󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	AnimationManager* GetAnimation() { return m_playerAnimation.get(); }

	/*
	*	�|�X�g�G�t�F�N�g�}�l�[�W�����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectManager* GetPostEffectManager() { return m_postEffectManager; }
};