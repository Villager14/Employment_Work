/*
* @file		TVOFEffec.h
* @brief	テレビの終了の描画
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "Game/PlayScene/UIManager/UIRender.h"

class TVOFEffec
{
public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

	//		コンストラクタ
	TVOFEffec();
	
	//		デストラクタ
	~TVOFEffec();

	//		頂点
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	/*
	*	テクスチャの読み込み
	* 
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path);

	/*
	*	シェーダーを作成する
	* 
	*	@param	(path)			テクスチャのパス
	*	@param	(position)		座標
	*	@param	(scale)			スケール
	*	@param	(centerPoint)	中心点
	*/
	void Create(
		const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	//		シェーダーの読み込み
	void LoadShader();

	void Render(float time);

private:

	//		バッファー
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;

	//		入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;


	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		ジオメトリックシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometoryShaer;

	//		テクスチャ横サイズ
	int m_textureWidth;
	//		テクスチャ縦サイズ
	int m_textureHeight;

	//		スケール
	DirectX::SimpleMath::Vector2 m_scale;

	//		座標
	DirectX::SimpleMath::Vector2 m_position;

	//		回転
	DirectX::SimpleMath::Matrix m_rotationMatrix;

	//		中心点
	CENTER_POINT m_centerPoint;

public:

	/*
	*	回転を設定する
	*
	*	@param	(rotatonMatrix)	回転
	*/
	void SetRotationMatrix(DirectX::SimpleMath::Matrix rotatonMatrix)
	{
		m_rotationMatrix = rotatonMatrix;
	}

};
