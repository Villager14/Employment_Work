/*
* @file		TitleSelectManager.h
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "ITitleSelect.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/PlayScene/UIManager/Fade/FadeRender.h"

#include "../TVOFEffec.h"

class SelectPlayState;
class SelectEndState;
class SelectSettingState;
class ChangeSceneState;
class StartSceneState;

class TitleSelectManager
{
public:

	enum UIType
	{
		Play,
		End,
		Setting,
		TitleRogo
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

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(ITitleSelect* state);

	/*
	*	���S�����ւ̏���
	* 
	*	@bool (direction)	true : ��ֈړ����� false : ���S�ֈړ�����
	*/
	void CentreUP(bool direction, float time, UIType type);

	/*
	*	���S���牺�ւ̏���
	* 
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void CenterUnder(bool direction, float time, UIType type);

	/*
	*	���S���牺�ւ̏���
	*
	*	@bool (direction)	true : ���ֈړ����� false : ���S�ֈړ�����
	*/
	void UPUnder(bool direction, float time, UIType type);


	/*
	*	UI��ǉ�����
	* 
	*	@param	(path)		�e�N�X�`���t�@�C���p�X
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*/
	void AddRenderUI(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size);

private:

	//		�I��
	ITitleSelect* m_state;

	//		�v���C���
	std::unique_ptr<SelectPlayState> m_selectPlayState;

	//		�I�����
	std::unique_ptr<SelectEndState> m_selectEndState;

	//		�ݒ���
	std::unique_ptr<SelectSettingState> m_selectSettingState;

	//		�V�[����؂�ւ�����
	std::unique_ptr<ChangeSceneState> m_changeSceneState;

	//		�X�^�[�g���
	std::unique_ptr<StartSceneState> m_startSeceneState;
public:

	/*
	*	�v���C�I����Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	SelectPlayState* GetSelectPlayState() { return m_selectPlayState.get(); }

	/*
	*	�I���I����Ԃ��󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	SelectEndState* GetSelectEndState() { return m_selectEndState.get(); }
	
	/*
	*	�ݒ��Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	SelectSettingState* GetSelectSettingState() { return m_selectSettingState.get(); }

	/*
	*	�V�[����؂�ւ����Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ChangeSceneState* GetChangeSceneState() { return m_changeSceneState.get(); }

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

	//		�w�i�ړ�����
	std::unique_ptr<BackGroundMove> m_backGroundMove;

private:

	//		�e���r�폜�G�t�F�N�g
	std::unique_ptr<TVOFEffec> m_tvOffEffect;

	//		UI�}�l�[�W���[
	std::vector<std::unique_ptr<UIRender>> m_uiRender;

	//		UI�̍��W
	std::vector<DirectX::SimpleMath::Vector2> m_uiPosition;

	//		UI�̃T�C�Y
	std::vector<DirectX::SimpleMath::Vector2> m_uiSize;

	//		�`�揇��ݒ肷��
	std::vector<int> m_drawOder;

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

public:

	/*
	*	���W��ݒ肷��
	* 
	*	@parma	(position)	���W
	*	@param	(type)		UI�̃^�C�v
	*/
	void SetUIPosition(const DirectX::SimpleMath::Vector2& position, UIType type) { m_uiPosition[type] = position; }

	/*
	*	UI���W��ݒ肷��
	* 
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetUIPosition() { return m_uiPosition; }

	/*
	*	�T�C�Y��ݒ肷��
	*
	*	@parma	(size)	�T�C�Y
	*	@param	(type)	UI�̃^�C�v
	*/
	void SetUISize(const DirectX::SimpleMath::Vector2& size, UIType type) { m_uiSize[type] = size; }

	/*
	*	UI�T�C�Y��ݒ肷��
	*
	*	@return �T�C�Y
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetUISize() { return m_uiSize; }

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
};