/*
* @file		Instancing.h
* @brief	インスタンシングの処理
* @author	Morita
* @date		2024/07/26
*/

#pragma once

class Instancing
{
public:

	//		コンストラクタ
	Instancing();

	//		デストラクタ
	~Instancing();

	//		初期化処理
	void Initialize();

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
private:

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_instanceLayout;
	
	//		テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

};