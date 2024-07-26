/*
* @file		Instancing.cpp
* @brief	インスタンシングの処理
* @author	Morita
* @date		2024/07/26
*/

#include "pch.h"

#include "Instancing.h"

#include "Game/PlayScene/UIManager/BinaryFile.h"

#include <DirectXHelpers.h>

#include <WICTextureLoader.h>

const std::vector<D3D11_INPUT_ELEMENT_DESC> Instancing::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),	D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,	sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"InstMatrix",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,   D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	{"InstMatrix",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,   D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
	{"InstMatrix",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,   D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},

};

Instancing::Instancing()
{
}

Instancing::~Instancing()
{
}

void Instancing::Initialize()
{
	//auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();


	////		エフェクトファクトリーを受け取る
	//DirectX::EffectFactory* m_effect = LibrarySingleton
	//	::GetInstance()->GetEffectFactory();

	////		画像の読み込み
	//m_effect->SetDirectory(L"Resources/Models");

	////		モデルの読み込み
	//std::unique_ptr<DirectX::Model> m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
	//	L"Resources/Models/Background.cmo", *m_effect);

	//auto effect = dynamic_cast<DirectX::IEffect*>(m_floorModel->meshes.front()->meshParts.front()->effect.get());

	//DX::ThrowIfFailed(
	//	DirectX::CreateInputLayoutFromEffect(device, effect,
	//		&INPUT_LAYOUT[0], std::size(INPUT_LAYOUT),
	//		m_instanceLayout.ReleaseAndGetAddressOf()));

	//		インプットレイアウトの作製
	//device->CreateInputLayout(
	//	&INPUT_LAYOUT[0],
	//	static_cast<UINT>(INPUT_LAYOUT.size()),
	//	INPUT_LAYOUT.data(), INPUT_LAYOUT.size(),
	//	m_instanceLayout.GetAddressOf());

}
