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

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	float m_time;

	float m_move;

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