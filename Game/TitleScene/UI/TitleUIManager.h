

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include "Select/TitleSelectManager.h"

class TitleUIManager
{
public:

	//		�R���X�g���N�^
	TitleUIManager(TitleSelectManager* titleSceneManager);

	//		�f�X�g���N�^
	~TitleUIManager();

	void Initialize();

	//		UI�̏����쐬����
	void CreateUIInformation(DirectX::SimpleMath::Vector2 position,
							DirectX::SimpleMath::Vector2 size,
							TitleSelectManager::UIType type);

	void Update();

	void Render();

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;
		DirectX::SimpleMath::Vector2 scale;
	};

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�^�C�g���V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleSelectManager* m_titleSceneManager;

	//		�V�F�[�_�[�̏��
	std::unordered_map<TitleSelectManager::UIType, UIInformation> m_shaderInformation;

public:

	/*
	*	�R���X�g�o�b�t�@���󂯎��
	* 
	*	@return	�R���X�g�o�b�t�@�̃|�C���^
	*/
	ConstBuffer* GetConsutBuffer() { return &m_constBuffer; }
};