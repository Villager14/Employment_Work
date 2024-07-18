/*
* @file		AboveUI.h
* @brief	UI�̏㏸����
* @author	Morita
* @date		2024/07/09
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class AboveUI
{
public:

	//		�R���X�g���N�^
	AboveUI();

	//		�f�X�g���N�^
	~AboveUI();

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

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		���W
		DirectX::SimpleMath::Vector2 scale;							//		�T�C�Y
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;	//		�e�N�X�`��
		DirectX::SimpleMath::Vector2 textureSize;					//		�e�N�X�`���T�C�Y
		float time = 0.0f;											//		����
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER;
	};

	enum UIType
	{
		AudioSelect,
		OptionSelect,
		GamePlaySelect,
		Slide,
		AudioTitle,
		OptionTitle,
		GamePlayTitle,
		SliderBack,
		MastarVolume,
		BGMVolume,
		SoundEffectVolume,
		MasterKnob,
		BGMKnob,
		SoundEffectKnob,
		MenuClose,
		Exit,
		FOV,
		FOVKnob,
		Mouse,
		MouseKnob,

		Empty,
	};

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�V�F�[�_�[�̏��
	std::unordered_map<UIType, UIInformation> m_shaderInformation;


public:

	/*
	*	UI�̏����쐬����
	*
	*	@param	(path)		�e�N�X�`���̃p�X
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*	@param	(type)		UI�̎��
	*/
	void CreateUIInformation(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		UIType type,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	/*
	*	�`�揈��
	*
	*	@param	(type)	�`�悷��UI�̎��
	*/
	void Render(UIType type, float time);

	std::unordered_map<UIType, UIInformation>* GetInformation() { return &m_shaderInformation; }
};