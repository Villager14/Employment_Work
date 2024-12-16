/*
* @file		TitleFlowManager.h
* @brief	�^�C�g���̗���}�l�[�W���[
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitleSelect.h"

#include "../Observer/TitlePostEffectObserver/ITitlePostEffectObserver.h"

#include "../Observer/TitleUIObserver/TitleUIObserver.h"

#include "../Observer/FadeObserver/FadeObserver.h"

#include "../Observer/GameExitObserver/TitleGameExitObserver.h"

#include "../Observer/MenuUseObserver/TitleMenuUseObserver.h"

#include "../Observer/TitlePlayerAnimationObserver/TitlePlayerAnimationObserver.h"

class TitleFlowManager : public ITitlePostEffectObserver
{
public:

	//		�R���X�g���N�^
	TitleFlowManager();

	//		�f�X�g���N�^
	~TitleFlowManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�I������
	void Finalize();

	//		�t�F�[�h�C��
	void FadeIn() override;

	//		�t�F�[�h�A�E�g
	void FadeOut() override;

	//		�L�[����
	void InputKey();

	/*
	*
	*	�I���o�[�̈ړ�����
	*
	*	@return true : �ړ��������I�� false : �ړ�������OR�ړ����������Ă��Ȃ�
	*/
	bool SelectionBarMoveProcess();

	//		�I�����̃��Z�b�g
	void SelectionInfromationReset();

public:

	//		���
	enum State
	{
		PlayState,		//		�v���C���
		EndState,		//		�I�����
		SettingState,	//		�ݒ���
		ChangState,		//		�ύX���
		StartState		//		�X�^�[�g���
	};

	//		�I���o�[�̈ړ�����
	enum SelectionBarMoveDirection
	{
		Not,		//		�����Ă��Ȃ�
		Up,			//		��ɓ���
		Down,		//		���ɓ���
	};

public:

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(State state);

private:

	//		�ړ����x
	const float MOVE_SPEED = 7.0f;

private:

	//		��Ԃ̏��
	std::unordered_map<State, std::unique_ptr<ITitleSelect>> m_stateInformation;

	//		���݂̏��
	State m_state;

	//		��Ԃ������C���^�[�t�F�C�X
	ITitleSelect* m_iState;

	//		�^�C�g��UI�I�u�U�[�o�[
	std::unique_ptr<TitleUIObserver> m_titleUIObserver;

	//		�I���o�[�̈ړ�����
	SelectionBarMoveDirection m_selectionBarMoveDirection;

	//		�t�F�[�h�I�u�U�[�o�[
	std::unique_ptr<FadeObserver> m_fadeObserver;

	//		�Q�[���I���I�u�U�[�o�[
	std::unique_ptr<TitleGameExitObserver> m_gameExitObserver;

	//		���j���[���g�p����I�u�U�[�o�[
	std::unique_ptr<TitleMenuUseObserver> m_menuUseObserver;

	//		�A�j���[�V�����I�u�U�[�o�[
	std::unique_ptr<TitlePlayerAnimationObserver> m_animationObserver;

	//		�L�[�������Ă��邩���f����
	bool m_keyInputJudgement;

	//		�t�F�[�h�C�����I����Ă��邩�ǂ���
	bool m_fadeInEndJudgement;

	//		�o�ߎ���
	float m_time;

	//		�X�N���[���z�C�[���̒l
	int m_scrollWheel;
public:

	/*
	*	�t�F�[�h�C�����I����Ă��邩�ǂ���
	*
	*	@return true : �I����Ă��� false : �I����Ă��Ȃ�
	*/
	const bool GetFadeInEndJudgement() { return m_fadeInEndJudgement; }

	/*
	*	�I���o�[�̈ړ�����
	*
	*	@return �ړ�����
	*/
	SelectionBarMoveDirection GetSelectionBarMoveDirection() { return m_selectionBarMoveDirection; }

	/*
	*	�^�C�g��UI�I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddITitleUIObserver(ITitleUIObserver* observer) { m_titleUIObserver->AddObserver(observer); }

	/*
	*	�t�F�[�h�I�u�U�[�o�[���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	FadeObserver* GetFadeObserver() { return m_fadeObserver.get(); }

	/*
	*	�^�C�g���̃t�F�[�h�I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddIFadeObserver(IFadeObserver* observer) { m_fadeObserver->AddObserver(observer); }

	/*
	*	�Q�[���I���I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddGameExitObserver(ITitleGameExitObserver* observer) { m_gameExitObserver->AddObserver(observer); }

	//		�Q�[���I���I�u�U�[�o�[
	void GameExitObserver() { m_gameExitObserver->GameExit(); }

	/*
	*	���j���[�g�p�I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddMenUseObserver(ITitleMenuUseObserver* observer) { m_menuUseObserver->AddObserver(observer); }

	//		���j���[���J��
	void MenuUse() { m_menuUseObserver->MenuUse(); }

	//		���j���[���g�p�ł���悤�ɂ���
	void MenuEnableMenu() { m_menuUseObserver->EnableMenu(); }

	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	void MenuDisableMenu() { m_menuUseObserver->DisableMenu(); }

	//		�A�j���[�V�����I�u�U�[�o�[�̒ǉ�
	void AddAnimationObserver(ITitlePlayerAnimationObserver* observer) { m_animationObserver->AddObserver(observer); }

	/*
	*	�A�j���[�V�����I�u�U�[�o�̃C���X�^���X�̃|�C���^
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	TitlePlayerAnimationObserver* AnimationObserver() { return m_animationObserver.get(); }
};