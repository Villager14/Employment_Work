/*
* @file		ResultManager.h
* @brief	���U���g�}�l�[�W���[
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "IResultManager.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/PlayScene/UIManager/Fade/FadeRender.h"

#include "Game/PlayScene/UIManager/UIRender.h"


#include "Game/ResultScene/UI/AboveNumber.h"

#include "State/ResultStart.h"
#include "State/ResultNumberMove.h"
#include "State/ResultEvaluation.h"
#include "State/ResultStay.h"
#include "State/ResultEnd.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"
#include "Game/PlayScene/Player/Bons/PlayerAnimation.h"

class ResultStart;
class ResultNumberMove;
class ResultEvaluation;
class ResultStay;
class ResultEnd;

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

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(IResultManager* state);

	//		��Ԃ��쐬����
	void CreateState();

	/*
	*	�����̕`��
	* 
	*	@param	(time)	����
	*/
	void NumberRender(float time);

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

	//		�A�j���[�V�����X�L�b�v
	void AnimationSkip();

private:

	//		���
	IResultManager* m_state;

	//		���U���g�X�^�[�g���
	std::unique_ptr<ResultStart> m_resultStart;

	//		���U���g�V�[���̔ԍ��ړ����
	std::unique_ptr<ResultNumberMove> m_resultNumberMove;

	//		���U���g�]�����
	std::unique_ptr<ResultEvaluation> m_resultEvaluation;

	//		���U���g�ҋ@���
	std::unique_ptr<ResultStay> m_resultStay;

	//		���U���g�I������
	std::unique_ptr<ResultEnd> m_resultEnd;
public:

	/*
	*	�X�^�[�g��Ԃ𐶐�����
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultStart* GetResultStart() { return m_resultStart.get(); }

	/*
	*	�ԍ��ړ���Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultNumberMove* GetNumberMove() { return m_resultNumberMove.get(); }

	/*
	*	�]����Ԃ��󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultEvaluation* GetEvaluation() { return m_resultEvaluation.get(); }

	/*
	*	�ҋ@��Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultStay* GetResultStay() { return m_resultStay.get(); }

	/*
	*	�I����Ԃ��󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultEnd* GetResultEnd() { return m_resultEnd.get(); }

private:
	
	//		�w�i�ړ��̕`��
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		�t�F�[�h�C���`��
	std::unique_ptr<FadeRender> m_fadeRender;

	//		��Ɉړ�����ԍ�
	std::vector<std::unique_ptr<AboveNumber>> m_aboveNumber;

	//		UI�̕`��
	std::vector<std::unique_ptr<UIRender>> m_uiRender;

	//		�X�R�A
	int m_score;
	//		����
	int m_time;
	//		���S�J�E���g
	int m_deathCount;

	//		�|�W�W����
	std::vector<DirectX::SimpleMath::Vector2> m_uiPosition;

	//		�T�C�Y
	std::vector<DirectX::SimpleMath::Vector2> m_uiSize;

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<PlayerAnimation> m_playerAnimation;

	//		��]��
	float m_rotation;

	//		�V�[����؂�ւ���
	bool m_changeScene;

public:

	/*
	*	�t�F�[�h�̕`��
	* 
	*	@param	(time)	����
	*/
	void FadeViewProcess(float time) { m_fadeRender->Render(time); }

	/*
	*	UI�`��̏���
	* 
	*	@param	(index)	�v�f��
	*/
	void UIViewProcess(int index) { m_uiRender[index]->Render(); }

	/*
	*	UI�`��̃X�P�[��
	*
	*	@param	(index)	�v�f��
	*	@param	(size)	�T�C�Y
	*/
	void UIScare(int index, float size) { m_uiRender[index]->SetSize({size, size}); }

	/*
	*	�オ�鐔���̏���
	* 
	*	@param	(index)	 �v�f��
	*	@param	(number) �ԍ�
	*	@param	(time)	 ����
	*/
	void AboveNumberView(int index, int number, float time) { m_aboveNumber[index]->Render(number, time); }

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
};