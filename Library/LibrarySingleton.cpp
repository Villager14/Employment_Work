/*
* @file		LibraySingleton.cpp
* @brief	ライブラリシングルトン
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "LibrarySingleton.h"

std::unique_ptr<LibrarySingleton> LibrarySingleton::m_library = nullptr;

LibrarySingleton::LibrarySingleton()
	:
	m_debugViewJudgment(false)
{
	//		デバイスリソースを生成する
	m_device = std::make_unique<DX::DeviceResources>();
}

LibrarySingleton::~LibrarySingleton()
{
}

LibrarySingleton* const LibrarySingleton::GetInstance()
{
	if (m_library == nullptr)
	{
		m_library.reset(new LibrarySingleton());
	}

	return m_library.get();
}

void LibrarySingleton::Initialize()
{
	//		コモンステートを生成する
	m_commonState = std::make_unique<DirectX::CommonStates>(m_device->GetD3DDevice());

	//		スプライトバッチを生成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_device->GetD3DDeviceContext());

	//		スプライトフォントを生成する
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device->GetD3DDevice(), L"Resources/Font/SegoeUI_18.spritefont");

	//		バーテックポジションカラーを生成する
	m_vertexPositionColor = std::make_unique
		<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>
		(m_device->GetD3DDeviceContext());

	//		バーテックスポジションカラーテクスチャを生成する
	m_vertexPositionColorTexture = std::make_unique
		<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>
		(m_device->GetD3DDeviceContext());

	//		エフェクトファクトリーを生成する
	m_effectFactory = std::make_unique
		<DirectX::EffectFactory>
		(m_device->GetD3DDevice());
}
