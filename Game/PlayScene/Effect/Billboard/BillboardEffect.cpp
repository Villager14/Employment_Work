/*
* @file		BillboardEffect.cpp
* @brief	�r���{�[�g�G�t�F�N�g
* @author	Morita
* @date		2024/06/10
*
* @���Ɠ��������Q�l
*/

#include "pch.h"

#include "BillboardEffect.h"

#include <WICTextureLoader.h>
#include "Game/PlayScene/UIManager/BinaryFile.h"


const std::vector<D3D11_INPUT_ELEMENT_DESC> BillboardEffect::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,																			D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(DirectX::SimpleMath::Vector3),										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0},
};


BillboardEffect::BillboardEffect()
{
}

BillboardEffect::~BillboardEffect()
{
}

void BillboardEffect::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture = texture;
}

void BillboardEffect::Create()
{
	CreateShader();

	//		�v���~�e�B�u�o�b�`�̍쐻
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
}

void BillboardEffect::Render(const std::vector<DirectX::SimpleMath::Vector3>& position)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto state = LibrarySingleton::GetInstance()->GetCommonState();

	//		�摜�p�T���v���̓o�^
	ID3D11SamplerState* samPler[1] = {
		state->LinearWrap() };
	context->PSSetSamplers(0, 1, samPler);

	//�������`��w��
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(state->DepthDefault(), 0);

	//		�J�����O��
	context->RSSetState(state->CullNone());

	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	context->IASetInputLayout(m_inputLayout.Get());

	//		�R���X�g�o�b�t�@�̍X�V
	ConstBuffer cbuff;
	DirectX::SimpleMath::Matrix world;

	cbuff.matWorld = m_billboard.Transpose();

	cbuff.matView = LibrarySingleton::GetInstance()->GetView().Transpose();
	cbuff.matProj = LibrarySingleton::GetInstance()->GetProj().Transpose();

	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);

	context->UpdateSubresource(m_constBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11Buffer* cb[1] = { m_constBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	m_batch->Begin();

	for (int i = 0; i < position.size(); ++i)
	{
		DirectX::VertexPositionColorTexture m_vertices{};

		DirectX::VertexPositionColorTexture v;

		v.position = position[i];
		v.color = { 1,1,1,1 };
		v.textureCoordinate = DirectX::XMFLOAT2(10.0f, 0.0f);

		m_vertices = v;

		m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices, 1);
	}

	m_batch->End();

	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

void BillboardEffect::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	m_billboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, eye - target, up);

	DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	m_cameraPosition = eye;
	m_cameraTarget = target;
	m_billboard = rot * m_billboard;
}

void BillboardEffect::CreateShader()
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		�R���p�C�����ꂽ�V�F�[�_�[�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shader/EffectBillboard/EffectBillboardVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shader/EffectBillboard/EffectBillboardGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shader/EffectBillboard/EffectBillboardPS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf()
	);

	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constBuffer);
}