/*
* @file		CoolTime.h
* @brief	�N�[���^�C��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Library/Shader/UIRenderManager.h"

#include "../UIManager.h"

class CoolTime
{
public:

	//		�R���X�g���N�^
	CoolTime(UIManager* uiManager);

	//		�f�X�g���N�^
	~CoolTime();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*	
	*	�v���C���[�̏����󂯂Ƃ�
	*/
	void Update(float coolTime);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�����̕`��
	void NumberView();

private:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 number;			//		����
	};

	//		�R���X�g�o�b�t�@��]
	struct ConstBufferCircle
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 rotation;
	};


private:

	//		�����̒��S�̍��W
	const float NUMBER_CENTER_POSITION = 1179.0f;

	//		�����̊Ԋu
	const float NUMBER_INTERVAL = 30.0f;

	//		�N�[���^�C���̍��W
	const DirectX::SimpleMath::Vector2 COOL_TIME_POSITION = { 270.0f, 0.0f };

	//		�ő�p�x
	const float MAX_ANGLE = 360.0f;
	
	//		���[�g
	const float RATO = 100.0f;

	//		�_�b�V���̑��x
	const float DASH_SPEED = 2.0f;

	//		�N�[���^�C���̑��x
	const float COOL_TIME_SPEED = 0.67f;

	//		�N�[���^�C���e�N�X�`���p�X
	const wchar_t* COOL_TIME_TEXTURE_PATH = L"Resources/Texture/UI/CoolTime/CoolTime.png";

	//		�N�[���^�C��VS�p�X
	const wchar_t* COOL_TIME_VS_PATH = L"Resources/Shader/UI/CoolTime/CoolTimeVS.cso";

	//		�N�[���^�C��GS�p�X
	const wchar_t* COOL_TIME_GS_PATH = L"Resources/Shader/UI/CoolTime/CoolTimeGS.cso";

	//		�N�[���^�C��PS�p�X
	const wchar_t* COOL_TIME_PS_PATH = L"Resources/Shader/UI/CoolTime/CoolTimePS.cso";

	//		�N�[���^�C���e�N�X�`���p�X
	const wchar_t* COOL_TIME_NUMBER_TEXTURE_PATH = L"Resources/Texture/UI/CoolTime/cooltimeNumber.png";

	//		�ԍ�VS�p�X
	const wchar_t* NUMBER_VS_PATH = L"Resources/Shader/UI/Number/NumberVS.cso";

	//		�ԍ�GS�p�X
	const wchar_t* NUMBER_GS_PATH = L"Resources/Shader/UI/Number/NumberGS.cso";

	//		�ԍ�PS�p�X
	const wchar_t* NUMBER_PS_PATH = L"Resources/Shader/UI/Number/NumberPS.cso";

private:

	//		UI�}�l�[�W���̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�p�x
	float m_angle;

	//		����
	float m_time;

	//		�p�[�Z���g
	float m_ratio;

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_coolTimeNumberShader;

	//		��]�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_coolTImeShader;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		��]�R���X�g�o�b�t�@
	ConstBufferCircle circleBuffer;
};
