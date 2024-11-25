/*
* @file		GenerationWorld.h
* @brief	���E�̐����I�u�W�F�N�g�V�F�[�_�[
* @author	Morita
* @date		2024/11/19
*/

#pragma once

#include "Library/Shader/ObjectShaderManager.h"

class GenerationWorld
{
public:

	GenerationWorld();

	~GenerationWorld();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	void Shader(ID3D11DeviceContext1* context);

	void Finalize();

public:

	struct ConstBuffer
	{
		float length = 0.0f;
		DirectX::SimpleMath::Vector3 pad;
		float stop = 0.0f;
		DirectX::SimpleMath::Vector3 pad2;
		float time = 0.0f;
		DirectX::SimpleMath::Vector3 pad3;
	};

private:

	//		�R���X�g�o�b�t�@	
	ConstBuffer m_constBuffer;

	//		���[���h�����V�F�[�_�[
	std::unique_ptr<ObjectShaderManager> m_generationWorld;

	//		���������ǂ���
	bool m_generationJudgement;

	float m_time;

	float m_deltaTime;

public:

	/*
	*	���[���h�����V�F�[�_�[
	* 
	*	@return true :�@������ false : �������Ă��Ȃ�
	*/
	bool GetGenerationJdugement() { return m_generationJudgement; }

	ConstBuffer GetConstBuffer() { return m_constBuffer; }
};