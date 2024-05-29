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


class ResultStart;
class ResultNumberMove;

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

private:

	//		���
	IResultManager* m_state;

	//		���U���g�X�^�[�g���
	std::unique_ptr<ResultStart> m_resultStart;

	//		���U���g�V�[���̔ԍ��ړ�����
	std::unique_ptr<ResultNumberMove> m_resultNumberMove;
public:

	/*
	*	�X�^�[�g��Ԃ𐶐�����
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultStart* GetResultStart() { return m_resultStart.get(); }

	/*
	*	�ԍ��ړ����
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ResultNumberMove* GetNumberMove() { return m_resultNumberMove.get(); }

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
	*	�オ�鐔���̏���
	* 
	*	@param	(index)	 �v�f��
	*	@param	(number) �ԍ�
	*	@param	(time)	 ����
	*/
	void AboveNumberView(int index, int number, float time) { m_aboveNumber[index]->Render(number, time); }
};