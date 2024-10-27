

#pragma once

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class SpeedLine
{
public:

	SpeedLine(UIManager* uiManager);

	~SpeedLine();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 time;				//		����
	};

private:

	const float LINE_LENGTH = 0.1f;

	const float SPEED = 2.0f;

private:

	//		UI�}�l�[�W���̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;
	
	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		����
	float m_time;

	float m_frontTime;

	bool frontFlag;
};