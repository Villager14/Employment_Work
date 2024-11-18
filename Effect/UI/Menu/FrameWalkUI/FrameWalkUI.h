/*
* @file		FrameWalk.h
* @brief	�g�̏���
* @author	Morita
* @date		2024/07/18
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include <unordered_map>

class FrameWalkUI
{
public:

	//		�R���X�g���N�^
	FrameWalkUI();

	//		�f�X�g���N�^
	~FrameWalkUI();

	//		����������
	void Initialize();
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 time;					//		����
	};

	enum FrameType
	{
		MenuClear,
		EXIT
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		���W
		float move = 0.0f;											//		�ω�����
		float time = 0.0f;											//		����
		bool boxhitJudgement = false;								//		�{�b�N�X�̒��ɂ��邩		
	};

public:

	//		MenuFrameworkUI�̍��W
	const DirectX::SimpleMath::Vector2 MENU_FRAME_WORK_POSITION = { 200.0f, -100.0f };

	//		EXITUI�̍��W
	const DirectX::SimpleMath::Vector2 EXIT_POSITION = { 200.0f, 50.0f };

	//		�t���[���̑��x
	const float FRAME_SPEED = 5.0f;

	//		���j���[�t���[�����[�N�e�N�X�`��
	const wchar_t* MENU_FRAMEWAORK_TEXTURE_PATH = L"Resources/Texture/Menu/GamePlay/MenuFramework.png";

	//		���j���[�t���[�����_�V�F�[�_�[
	const wchar_t* MENU_FRAMEWAORK_VS_PATH = L"Resources/Shader/UI/FrameWalk/FrameWalkVS.cso";

	//		���j���[�t���[���W�I���g���V�F�[�_�[
	const wchar_t* MENU_FRAMEWAORK_GS_PATH = L"Resources/Shader/UI/FrameWalk/FrameWalkGS.cso";

	//		���j���[�t���[���s�N�Z���V�F�[�_�[
	const wchar_t* MENU_FRAMEWAORK_PS_PATH = L"Resources/Shader/UI/FrameWalk/FrameWalkPS.cso";

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�o�ߎ���
	float m_time;

	float m_move;

	//		�t���[���̏��
	std::unordered_map<FrameType, UIInformation> m_frameInformation;

public:

	/*
	*	�`�揈��
	*
	*	@param	(type)	�`�悷��UI�̎��
	*/
	void Render(float time, FrameType type);

	//		���Ԃ̃��Z�b�g
	void TimeReset() { m_time = 0.0f; };

	//		�t���[���̃^�C�v
	void CreateFrameInformtion(FrameType type, DirectX::SimpleMath::Vector2 position);

	//		���Z�b�g
	void Reset();

	std::unordered_map<FrameType, UIInformation>* GetFrameInformation() { return &m_frameInformation; }
};