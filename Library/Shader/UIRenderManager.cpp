/*
* @file		UIRender.h
* @brief	UIシェーダーの描画
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIRenderManager.h"

#include <WICTextureLoader.h>
#include "Game/PlayScene/UIManager/BinaryFile.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> UIRenderManager::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),	D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,	sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0},
};

UIRenderManager::UIRenderManager()
{
}

UIRenderManager::~UIRenderManager()
{
}

void UIRenderManager::LoadTexture(const wchar_t* path)
{
	//		画像ファイルの読み込み
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, m_resource.ReleaseAndGetAddressOf(),
		m_texture.ReleaseAndGetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

	//		テクスチャ化
	DX::ThrowIfFailed(m_resource.As(&texture));

	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	//		テクスチャのサイズを取得
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

void UIRenderManager::LoadShader(
	const wchar_t* vsPath,
	const wchar_t* gsPath,
	const wchar_t* psPath)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(vsPath);
	BinaryFile GSData = BinaryFile::LoadFile(gsPath);
	BinaryFile PSData = BinaryFile::LoadFile(psPath);

	//		インプットレイアウトの作製
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//		頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//		エラー
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		return;
	}

	//		ジオメトリックシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometoryShaer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader failed", NULL, MB_OK);

		return;
	}

	//		ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Failde", NULL, MB_OK);
		return;
	}
}

/*
void UIRenderManager::Render()
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto commonState = LibrarySingleton::GetInstance()->GetCommonState();

	//		画像の中心
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_centerPoint)),
		DirectX::SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)),
		DirectX::SimpleMath::Vector2(1.0f,0.0f))
	};

	//		コンストバッファのバインド
	m_constBufferManager->BindBuffer();

	//		画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { commonState->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//		半透明描画指定
	ID3D11BlendState* blendestate = commonState->NonPremultiplied();

	//		透明判定処理
	context->OMSetBlendState(blendestate, nullptr, 0xFFFFFFFF);

	//		深度バッファに書き込み参照
	context->OMSetDepthStencilState(commonState->DepthDefault(), 0);

	//		カリングは左回り
	context->RSSetState(commonState->CullNone());

	//		シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometoryShaer.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//		ピクセルシェーダにテクスチャを登録する
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//		インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//		板ポリゴンを描画
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Begin();
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->
		Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->End();

	//		シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
*/
