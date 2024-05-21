/*
* @file		LibraySingleton.cpp
* @brief	���C�u�����V���O���g��
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
	//		�f�o�C�X���\�[�X�𐶐�����
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
	//		�R�����X�e�[�g�𐶐�����
	m_commonState = std::make_unique<DirectX::CommonStates>(m_device->GetD3DDevice());

	//		�X�v���C�g�o�b�`�𐶐�����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_device->GetD3DDeviceContext());

	//		�X�v���C�g�t�H���g�𐶐�����
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device->GetD3DDevice(), L"Resources/Font/SegoeUI_18.spritefont");

	//		�o�[�e�b�N�|�W�V�����J���[�𐶐�����
	m_vertexPositionColor = std::make_unique
		<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>
		(m_device->GetD3DDeviceContext());

	//		�o�[�e�b�N�X�|�W�V�����J���[�e�N�X�`���𐶐�����
	m_vertexPositionColorTexture = std::make_unique
		<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>
		(m_device->GetD3DDeviceContext());

	//		�G�t�F�N�g�t�@�N�g���[�𐶐�����
	m_effectFactory = std::make_unique
		<DirectX::EffectFactory>
		(m_device->GetD3DDevice());
}
