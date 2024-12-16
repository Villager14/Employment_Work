/*
* @file		TitleKeyGuidance.h
* @brief	�^�C�g���̃L�[�K�C�h
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Library/Shader/StandardShader.h"


class TitleKeyGuidance
{
public:

	//		�R���X�g���N�^
	TitleKeyGuidance();

	//		�f�X�g���N�^
	~TitleKeyGuidance();

	//		����������
	void Initialize();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	/*
	*	��I�����̏���
	* 
	*	@param	(processingTime)	��������
	*/
	void UpSelect(float processingTime);

	/*
	*	���I�����̏���
	*
	*	@param	(processingTime)	��������
	*/
	void DownSelect(float processingTime);

private:

	enum UIType
	{
		Space,		//		�X�y�[�X
		W,			//		W
		A,			//		A
	};

	enum CenterUIType
	{
		Not,
		Play,		//		�v���C
		End,		//		�I��
		Setting,	//		�ݒ�
	};

private:

	//		W�̃v���C�����W
	const DirectX::SimpleMath::Vector2 W_PLAY = { 120.0f, 40.0f };

	//		�X�y�[�X�̃G���h�����W
	const DirectX::SimpleMath::Vector2 SPACE_END = { 270.0f, 120.0f };

	//		�X�y�[�X�̃v���C�����W
	const DirectX::SimpleMath::Vector2 SPACE_PLAY = { 300.0f, 120.0f };

	//		�X�y�[�X�̐ݒ莞���W
	const DirectX::SimpleMath::Vector2 SPACE_SETTING = { 410.0f, 120.0f };

	//		W�̃G���h�����W
	const DirectX::SimpleMath::Vector2 W_END = { 110.0f, 40.0f };

	//		A�̐ݒ莞���W
	const DirectX::SimpleMath::Vector2 A_SETTING = { 180.0f, 200.0f };

	//		�ő�X�P�[��
	const float MAX_SCALE = 1.0f;
private:

	//		�^�C�g��UI�}�l�[�W���[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		���S��UI�^�C�v
	CenterUIType m_centerUIType;
};