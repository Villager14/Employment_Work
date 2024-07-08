/*
* @file		ResultManager.h
* @brief	���U���g�}�l�[�W���[
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include <unordered_map>

#include "IResultManager.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/PlayScene/UIManager/Fade/FadeRender.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"

#include "Game/PlayScene/Player/Bons/PlayerAnimation.h"

#include "Library/Shader/StandardShader.h"

#include "UI/RiseNumberShader.h"

class ResultManager
{
public:

	//		���U���g�}�l�[�W���[
	ResultManager();

	//		���U���g�}�l�[�W���[
	~ResultManager();

	//		����������
	/*
	*	����������
	* 
	*	@param	(score)			�X�R�A
	*	@param	(time)			�^�C��
	*	@param	(deathCount)	���S�J�E���g
	*/
	void Initialize(int score, int time, int deathCount);

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		��Ԃ��쐬����
	void CreateState();

	//		�A�j���[�V�����X�L�b�v
	void AnimationSkip();

	//		�V�F�[�_�[�̍쐻
	void CreateStandardShader();

public:

	//		���
	enum State
	{
		Start,			//		�X�^�[�g
		NumberMove,		//		�ԍ�
		Evaluation,		//		�]��
		Stay,			//		�ҋ@
		End,			//		�I��
	};

	//		���U���g��UI�̎��
	enum ResultUIType
	{
		Back,			//		UI�w�i
		Button,			//		�{�^���q���g
		EvaluationUI	//		�]��
	};

private:

	//		�v���C���[�̉�]���x
	const float PLAYER_ROTATION_SPEED = 30.0f;

	//		�v���C���[�̍���
	const float PLAYER_HEIGHT = 2.5f;

	//		�v���C���[�̍��W
	const DirectX::SimpleMath::Vector3 PLAYER_POSITION = { 0.0f, 0.0f, 8.0f };

private:

	//		���
	IResultManager* m_iState;

	//		��Ԃ̏��
	std::unordered_map<State, std::unique_ptr<IResultManager>> m_stateInformation;

	//		���
	State m_state;
	
	//		�V�F�[�_�[
	std::unique_ptr<StandardShader<ResultManager::ResultUIType>> m_shader;

	//		�w�i�ړ��̕`��
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		�t�F�[�h�C���`��
	std::unique_ptr<FadeRender> m_fadeRender;

	//		�X�R�A
	int m_score;
	//		����
	int m_time;
	//		���S�J�E���g
	int m_deathCount;

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<PlayerAnimation> m_playerAnimation;

	//		��]��
	float m_rotation;

	//		�V�[����؂�ւ���
	bool m_changeScene;

	//		�����̏㏸�V�F�[�_�[
	std::unique_ptr<RiseNumberShader> m_riseNumber;

public:

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(State state);

	/*
	*	�t�F�[�h�̕`��
	* 
	*	@param	(time)	����
	*/
	void FadeViewProcess(float time) { m_fadeRender->Render(time); }

	/*
	*	�V�[����؂�ւ��邩�ݒ肷��
	* 
	*	@param	(judgement)	true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeScene = judgement; }

	/*
	*	�V�[����؂�ւ��邩�󂯎��
	*	
	*	@return true : �؂�ւ��� false : �؂�ւ��Ȃ�
	*/
	bool GetChangeSceneJudgement() { return m_changeScene; }

	/*
	*	���U���gUI�}�l�W���[�̃C���X�^���X�̃|�C���^���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<ResultUIType>* GetStandardShader() { return m_shader.get(); }

	/*
	*	�㏸�����̃C���X�^���X�̃|�C���^���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	RiseNumberShader* GetRiseNumberShader() { return m_riseNumber.get(); }
};