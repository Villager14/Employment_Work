/*
* @file		UIRender.h
* @brief	UI�V�F�[�_�[�̕`��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

enum class CENTER_POINT
{
	ABOVE_LEFT,
	ABOVE_CENTER,
	ABOVE_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	UNDER_LEFT,
	UNDER_CENTER,
	UNDER_RIGHT,
};


class UIRender
{
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
	};

	//		�R���X�g���N�^
	UIRender();
	
	//		�f�X�g���N�^
	~UIRender();

	//		���_
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	/*
	*	�e�N�X�`���̓ǂݍ���
	* 
	*	@param	(path)	�t�@�C���p�X
	*/
	void LoadTexture(const wchar_t* path);

	/*
	*	�V�F�[�_�[���쐬����
	* 
	*	@param	(path)			�e�N�X�`���̃p�X
	*	@param	(position)		���W
	*	@param	(scale)			�X�P�[��
	*	@param	(centerPoint)	���S�_
	*/
	void Create(
		const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	//		�V�F�[�_�[�̓ǂݍ���
	void LoadShader();

	void Render();

private:

	//		�o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;

	//		���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;


	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		�W�I���g���b�N�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometoryShaer;

	//		�e�N�X�`�����T�C�Y
	int m_textureWidth;
	//		�e�N�X�`���c�T�C�Y
	int m_textureHeight;

	//		�X�P�[��
	DirectX::SimpleMath::Vector2 m_scale;

	//		���W
	DirectX::SimpleMath::Vector2 m_position;

	//		��]
	DirectX::SimpleMath::Matrix m_rotationMatrix;

	//		���S�_
	CENTER_POINT m_centerPoint;

public:

	/*
	*	��]��ݒ肷��
	*
	*	@param	(rotatonMatrix)	��]
	*/
	void SetRotationMatrix(DirectX::SimpleMath::Matrix rotatonMatrix)
	{
		m_rotationMatrix = rotatonMatrix;
	}

};
