/*
* @file		Instancing.h
* @brief	�C���X�^���V���O�̏���
* @author	Morita
* @date		2024/07/26
*/

#pragma once

class Instancing
{
public:

	//		�R���X�g���N�^
	Instancing();

	//		�f�X�g���N�^
	~Instancing();

	//		����������
	void Initialize();

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
private:

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_instanceLayout;
	
	//		�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

};