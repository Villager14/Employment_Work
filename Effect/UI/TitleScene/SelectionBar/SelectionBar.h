/*
* @file		SelectionBar.h
* @brief	�I���o�[
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Library/Shader/StandardShader.h"

#include "SelectionBarMoveProcess.h"

class SelectionBar
{
public:

	//		�R���X�g���N�^
	SelectionBar();

	//		�f�X�g���N�^
	~SelectionBar();

	//		����������
	void Initialize();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	/*
	*	���I�������Ƃ��̏���
	* 
	*	@param	(processingTime)	��������
	*/
	void UpSelect(float processingTime);

	/*
	*	����I�������Ƃ��̏���
	*
	*	@param	(processingTime)	��������
	*/
	void DownSelect(float processingTime);

private:

	enum UIType
	{
		Play,		//		�v���C
		End,		//		�I��
		Setting,	//		�ݒ�
	};

public:

	//		�^�C�g���v���C�e�N�X�`���p�X
	const wchar_t* TITLE_PLAY_TEXTURE_PATH = L"Resources/Texture/TitleScene/Select/TitlePlay.png";

	//		�^�C�g���I���e�N�X�`���p�X
	const wchar_t* TITLE_END_TEXTURE_PATH = L"Resources/Texture/TitleScene/Select/TitleEnd.png";

	//		�^�C�g���I���e�N�X�`���p�X
	const wchar_t* TITLE_SETTING_TEXTURE_PATH = L"Resources/Texture/TitleScene/Select/TitleSetting.png";

	//		���S�n�_
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		���n�_
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		��n�_
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

	//		�ő�X�P�[��
	const float MAX_SCALE = 1.0f;

	//		�ŏ��X�P�[��
	const float MIN_SCALE = 0.5f;

private:

	//		�^�C�g��UI�}�l�[�W���[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		�I���o�[�ړ�����
	std::unique_ptr<SelectionBarMoveProcess> m_selectionBarMoveProcess;

	//		���S�^�C�v
	UIType m_centerType;
};