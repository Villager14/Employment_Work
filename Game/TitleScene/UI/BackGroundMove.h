/*
* @file		BackGroundMove.h
* @brief	�w�i�̈ړ�
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/UIRenderManager.h"

class BackGroundMove
{
public:

	BackGroundMove();

	~BackGroundMove();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		UI�`��}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		����
	float m_time;

	//		�t�F�[�h�C�������邩�ǂ������f����
	bool m_fadeinResetJudgement;

	//		�t�F�[�h�A�E�g�����邩�ǂ������f����
	bool m_fadeoutResetJudgement;

	ConstBuffer buffer;
};
