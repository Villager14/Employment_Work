/*
* @file		UIRender.h
* @brief	UI�V�F�[�_�[�̕`��
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
	//		�摜�t�@�C���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, m_resource.ReleaseAndGetAddressOf(),
		m_texture.ReleaseAndGetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

	//		�e�N�X�`����
	DX::ThrowIfFailed(m_resource.As(&texture));

	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	//		�e�N�X�`���̃T�C�Y���擾
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

void UIRenderManager::LoadShader(
	const wchar_t* vsPath,
	const wchar_t* gsPath,
	const wchar_t* psPath)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(vsPath);
	BinaryFile GSData = BinaryFile::LoadFile(gsPath);
	BinaryFile PSData = BinaryFile::LoadFile(psPath);

	//		�C���v�b�g���C�A�E�g�̍쐻
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//		���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//		�G���[
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		return;
	}

	//		�W�I���g���b�N�V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometoryShaer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader failed", NULL, MB_OK);

		return;
	}

	//		�s�N�Z���V�F�[�_�쐬
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

	//		�摜�̒��S
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_centerPoint)),
		DirectX::SimpleMath::Vector4(m_position.x, m_position.y, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)),
		DirectX::SimpleMath::Vector2(1.0f,0.0f))
	};

	//		�R���X�g�o�b�t�@�̃o�C���h
	m_constBufferManager->BindBuffer();

	//		�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { commonState->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//		�������`��w��
	ID3D11BlendState* blendestate = commonState->NonPremultiplied();

	//		�������菈��
	context->OMSetBlendState(blendestate, nullptr, 0xFFFFFFFF);

	//		�[�x�o�b�t�@�ɏ������ݎQ��
	context->OMSetDepthStencilState(commonState->DepthDefault(), 0);

	//		�J�����O�͍����
	context->RSSetState(commonState->CullNone());

	//		�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometoryShaer.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//		�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//		�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//		�|���S����`��
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Begin();
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->
		Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->End();

	//		�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
*/
