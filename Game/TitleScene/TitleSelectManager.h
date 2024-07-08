/*
* @file		TitleSelectManager.h
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include <unordered_map>

#include "ITitleSelect.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/PlayScene/UIManager/Fade/FadeRender.h"

#include "Library/Shader/StandardShader.h"

class TitleUIManager;

class TitleSelectManager
{
public:

	//		UI�̎��
	enum TitleUIType
	{
		Play,		//		�v���C
		End,		//		�I��
		Setting,	//		�ݒ�
		TitleRogo	//		�^�C�g�����S
	};

	//		���
	enum State
	{
		PlayState,		//		�v���C���
		EndState,		//		�I�����
		SettingState,	//		�ݒ���
		ChangState,		//		�ύX���
		StartState		//		�X�^�[�g���
	};

public:

	//		�R���X�g���N�^
	TitleSelectManager();

	//		�f�X�g���N�^
	~TitleSelectManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�L�[����
	void InputKey();

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	void CreateStandardShader();

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(State state);

	/*
	*	���S�����ւ̏���
	* 
	*	@bool (direction)	true : ��ֈړ����� false : ���S�ֈړ�����
	*/
	void CentreUP(bool direction, float time, TitleUIType type);

	/*
	*	���S���牺�ւ̏���
	* 
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void CenterUnder(bool direction, float time, TitleUIType type);

	/*
	*	���S���牺�ւ̏���
	*
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void UPUnder(bool direction, float time, TitleUIType type);

private:

	//		���S�n�_
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		���n�_
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		��n�_
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

	//		�ړ����x
	const float MOVE_SPEED = 7.0f;

	//		�ő�X�P�[��
	const float MAX_SCALE = 1.0f;

	//		�ŏ��X�P�[��
	const float MIN_SCALE = 0.5f;

private:

	//		�I��
	ITitleSelect* m_iState;

	//		��Ԃ̏��
	std::unordered_map<State, std::unique_ptr<ITitleSelect>> m_stateInformation;

	//		���݂̏��
	State m_state;

	//		�`�揇��ݒ肷��
	std::vector<TitleUIType> m_drawOder;

	//		�L�[���͂����������ǂ���
	bool m_inputKey;

	//		�ړ�����
	bool m_direction;

	//		�X�N���[���̒l
	int m_scrollWheeel;

	//		�V�[����ύX���邩�ǂ���
	bool m_changeSceneJudgement;

	//		�t�F�[�h
	std::unique_ptr<FadeRender> m_fade;

	//		���j���[���J���Ă��邩�ǂ���
	bool m_menuJudgement;

	//		�w�i�ړ�����
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		�^�C�g��UI�}�l�[�W���[
	std::unique_ptr<StandardShader<TitleUIType>> m_standardShader;

public:

	/*
*	�ő�X�P�[�����󂯎��
*
*	@return �傫��
*/
	const float GetMaxScale() { return MAX_SCALE; }

	/*
	*	�ŏ��X�P�[�����󂯎��
	*
	*	@return �傫��
	*/
	const float GetMinScale() { return MIN_SCALE; }

	/*
	*	���S�|�C���g���󂯎��
	* 
	*	@return ���S�|�C���g
	*/
	const DirectX::SimpleMath::Vector2& GetCenterPoint() { return CENTER_POINT; }

	/*
	*	���|�C���g���󂯎��
	*
	*	@return ���|�C���g
	*/
	const DirectX::SimpleMath::Vector2& GetUnderPoint() { return UNDER_POINT; }

	/*
	*	��|�C���g���󂯎��
	*
	*	@return ��|�C���g
	*/
	const DirectX::SimpleMath::Vector2& GetUPPoint() { return UP_POINT; }

	/*
	*	�L�[���͂����邩�ǂ����󂯎��
	* 
	*	@return true : �L�[���͂����� false : �L�[���͂��Ȃ�
	*/
	bool GetKeyInput() { return m_inputKey; }

	/*
	*	�L�[���͂����邩�ǂ����󂯎��
	*
	*	@param	(judgement) true : �L�[���͂����� false : �L�[���͂��Ȃ�
	*/
	void SetKeyInput(bool judgement) { m_inputKey = judgement; }

	/*
	*	�ړ��������󂯎��
	*
	*	@return true : �� false : ��
	*/
	bool GetDirection() { return m_direction; }

	/*
	*	�ړ������󂯎��
	*
	*	@param	(direction) true : �� false : ��
	*/
	void SetDirection(bool direction) { m_direction = direction; }

	/*
	*	�ړ����x���󂯎��
	* 
	*	@return �ړ����x
	*/
	float GetMoveSpeed() { return MOVE_SPEED; }

	/*
	*	�V�[����؂�ւ��邩�ǂ������f����
	*
	*	@param	(judgement)	true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeSceneJudgement = judgement; }


	/*
	*	�V�[����؂�ւ��邩�ǂ������f����
	* 
	*	@return true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	bool GetChangeScnenJudgemnet() { return m_changeSceneJudgement; }


	/*
	*	�t�F�[�h�̕`��
	*
	*	@param	(time)	����
	*/
	void FadeViewProcess(float time) { m_fade->Render(time); }

	/*
	*	���j���[���J���Ă��邩�ǂ����󂯎��
	* 
	*	@param	(judgement)	true : �J���Ă���@false : �J���Ă��Ȃ�
	*/
	void SetMenuJudgement(bool judgement) { m_menuJudgement = judgement; }

	/*
	*	�^�C�g��UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<TitleUIType>* GetStandardShader() { return m_standardShader.get(); }
};