/*
* @file		MenuFlow.h
* @brief	���j���[�̗���
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenu.h"

#include "../Observer/BackGroundUI/MenuBackGroundUIObserver.h"
#include "../Observer/TabUI/MenuTabUIObserver.h"
#include "../Observer/SelectType/MenuSelectTypeObserver.h"
#include "../Observer/Title/MenuTitleUIObserver.h"
#include "../Observer/Icon/MenuIconUIObserver.h"

#include "../Observer/Mouse/IMenuMouseObserver.h"
#include "Library/Mouse/Observer/IMouseKeyInputObserver.h"
#include "../Observer/Collider/IMenuColliderObserver.h"
#include "Library/Keyboard/Observer/IKeyboardObserver.h"

class MenuFlowCommonProcess;

class MenuFlow : public IMenuMouseObserver,
	public IMouseKeyInputObserver,
	public IMenuColliderObserver,
	public IKeyboardObserver
{
public:

	MenuFlow();

	~MenuFlow();

	void Initialize();

	void Update();

	void Finalize();

	void CreateState();

	/*
	*	�}�E�X��X���W�̍X�V
	*
	*	@param	(x) x���W
	*/
	void MousePositionX(int x) override;

	/*
	*	�}�E�X��Y���W�̍X�V
	*
	*	@param	(y) y���W
	*/
	void MousePositionY(int y) override;

	/*
	*	�}�E�X�̉������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyPressed(KeyInputMouse::MouseList key) override;

	/*
	*	�}�E�X�̗������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyReleased(KeyInputMouse::MouseList key) override;

	/*
	*	�}�E�X�̉����������̎��̏���
	*
	*	@param	(key)	�����������L�[
	*/
	void IsKeepPushing(KeyInputMouse::MouseList key) override;

	/*
	*	�L�[�{�[�h�̉������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyPressed(KeyboardList::KeyboardList key) override;

	/*
	*	�L�[�{�[�h�̗������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyReleased(KeyboardList::KeyboardList key) override;

	/*
	*	�L�[�{�[�h�̉����Ă��鎞�̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyState(KeyboardList::KeyboardList key) override;

	/*
	*	��������UI�̃^�C�v
	*
	*	@param	(type)	UI�̃^�C�v
	*/
	void HitUIType(UISubType type) override;

	bool ButtonHitJudgement(UISubType type);

public:

	enum MenuType
	{
		Empty,
		Audio,
		Option,
		GamePlay,
		Standby,
		Start,
		Close,
	};

	enum KeyProcessFlag
	{
		None = 0b00000000,
		TabAudio = 1 << 0,				//		TabAudio�̓��͏���
		TabOption = 1 << 1,				//		TabOption�̓��͏���
		TabGamePlay = 1 << 2,			//		TabGamePlay�̓��͏���
		ButtonExit = 1 << 3,			//		Exit�{�^���̓��͏���
		ButtonMenuClose = 1 << 4,		//		MenuClose�{�^���̓��͏���
		K_MenuClose	= 1 << 5,			//		���j���[�������͏���
	};

private:

	//		���݂̏��
	IMenu* m_state;

	//		���݂̃^�C�v
	MenuType m_type;

	//		���̃^�C�v
	MenuType m_nextType;

	//		���ʏ���
	std::unique_ptr<MenuFlowCommonProcess> m_commonProcess;

	//		���j���[�̏�Ԃ̏��
	std::unordered_map<MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		�w�i��UI�I�u�U�[�o�[
	std::unique_ptr<MenuBackGroundUIObserver> m_menuBackGroundUIObserver;

	//		TabUI�I�u�U�[�o�[
	std::unique_ptr<MenuTabUIObserver> m_menuTabUIObserver;

	//		�I���^�C�v�I�u�U�[�o�[
	std::unique_ptr<MenuSelectTypeObserver> m_selectTypeObserver;

	//		�^�C�g��UI�I�u�U�[�o�[
	std::unique_ptr<MenuTitleUIObserver> m_titleUIObserver;

	//		���j���[�A�C�R���I�u�U�[�o�[
	std::unique_ptr<MenuIconUIObserver> m_menuIconUIObserver;

	//		�}�E�X���WX
	int m_mousePositionX;

	//		�}�E�X���WY
	int m_mousePositoinY;

	//		��������
	bool m_firstProcess;

	//		�t���O
	int m_flag;

	UISubType m_uiSubType;

	//		���j���[���I�����邩���f����
	bool m_menuEndJudgemnet;

	//		���j���[���J�n���邩���f����
	bool m_meneStartJudgement;

	//		���j���[�̊J�n�L�[�����������ǂ���
	bool m_menuOpenKeyJudgement;

public:

	/*
	*	���j���[�̊J�n�L�[�����������ǂ����ݒ肷��
	* 
	*	@param	(judgement) true : ������ false : �����Ă��Ȃ�
	*/
	void SetMenuOpenKeyJudgement(bool judgement) { m_menuOpenKeyJudgement = judgement; }

	/*
	*	���j���[�̊J�n�L�[�����������ǂ����󂯎��
	*
	*	@return true : ������ false : �����Ă��Ȃ�
	*/
	bool GetMenuOpenKeyJudgement() { return m_menuOpenKeyJudgement; }

	/*
	*	���j���[���J�n���邩�ݒ肷��
	* 
	*	@param	(judgement) true : �J�n���� false : �J�n���Ȃ�
	*/
	void SetMenuStartJudgement(bool judgement) { m_meneStartJudgement = judgement; }

	/*
	*	���j���[���J�n���邩�󂯎��
	* 
	*	@return true : �J�n���� false : �J�n���Ȃ�
	*/
	bool GetMenuStartJudgement() { return m_meneStartJudgement; }

	/*
	*	���j���[���I�����邩��ݒ肷��
	*
	*	@param	(judgement)	true : �I������ false : �I�����Ȃ�
	*/
	void SetMenuEndJudgement(bool judgement) { m_menuEndJudgemnet = judgement; }

	/*
	*	���j���[���I�����邩���󂯎��
	* 
	*	@return true : �I������ false : �I�����Ȃ�
	*/
	bool GetMenuEndJugement() { return m_menuEndJudgemnet; }

	/*
	*	�t���O�������Ă��邩
	*
	*	@param	(flag)	�m�F�������t���O
	*	@return true : yes false : no
	*/
	bool FlagJudgement(KeyProcessFlag flag);

	/*
	*	�t���O��On�ɂ���
	*
	*	@param	(flag)	�I���ɂ������t���O
	*/
	void TrueFlag(KeyProcessFlag flag);

	/*
	*	�t���O��of�ɂ���
	*
	*	@param	(flag)	�I�t�ɂ������t���O
	*/
	void FalseFlag(KeyProcessFlag flag);

	/*
	*	�C�[�W���O�֐��ʏ�UI�p
	*
	*	@param	(time)	����
	*/
	float EasingIcon(float time) { return 1.0f - pow(1.0f - time, 3.0f); }

	/*
	*	�C�[�W���O�֐��w�i�p
	*
	*	@param	(time) ����
	*/
	float EasingBackUI(float time) {
		if (time == 1.0f)
		{
			return 1.0f;
		}
		else
		{
			return 1.0f - pow(2.0f, -10.0f * time);
		}
	}

	//		�^�u�̏���
	bool TabProcess(MenuType type);

	void NextScene(MenuType type);

	/*
	*	��Ԃ̐؂�ւ�
	*
	*	@param	(type)	���
	*/
	void ChangState(MenuType type);

	/*
	*	���j���[IconUI�I�u�U�[�o�[�̒ǉ�
	* 
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddMenuIconUIObserver(IMenuIconUIObserver* observer) { m_menuIconUIObserver->AddObserver(observer); }

	void IconMoveProcess(float move) { m_menuIconUIObserver->IconMoveProcess(move); }

	bool GetFirstProcess() { return m_firstProcess; }

	void SetFirestProcess(bool judgement) { m_firstProcess = judgement; }

	MenuTitleUIObserver* GetTitleUIUObserver() { return m_titleUIObserver.get(); }

	MenuSelectTypeObserver* GetSelectTypeObserver() { return m_selectTypeObserver.get(); }

	MenuFlowCommonProcess* GetMenuFlowCommonProcess() { return m_commonProcess.get(); }

	void SetNextType(MenuType type) { m_nextType = type; }

	MenuType GetNextType() { return m_nextType; }

	MenuBackGroundUIObserver* GetMenuBackGroundUIObserver() { return m_menuBackGroundUIObserver.get(); }

	MenuTabUIObserver* GetMenuTabUIObserver() { return m_menuTabUIObserver.get(); }
};