/*
* @file		Shwdow.h
* @brief	�e�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "Shadow.h"

#include "Common/ReaData.h"

Shadow::Shadow()
	:
	m_lightRange(90.0f),
	m_shadowSize(256)
{
}

Shadow::~Shadow()
{
}

void Shadow::Initialize()
{
	m_information = std::make_unique<ShadowInformation>();

	CreateShadow();

	// ���C�g�̉�]
	m_lightRotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(89.0f), 0.0f);


	ConstantBuffer2 cb = {};
	cb.fCosTheta = cosf(DirectX::XMConvertToRadians(m_lightRange / 2.0f));

	LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDeviceContext()->UpdateSubresource
		(m_constantBuffer2.Get(), 0, nullptr, &cb, 0, 0);
}

void Shadow::Finalize()
{
}

void Shadow::CreateShadow()
{
	//		�f�o�C�X�̎擾
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(m_lightRange),
			1.0f, 0.1f, 100.0f);

	//		�T�C�Y
	RECT rect = { 0,0,static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	//		�����_�[�e�N�X�`���̍쐻�i�V���h�E�}�b�v�j
	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_renderTexture->SetDevice(device);
	m_renderTexture->SetWindow(rect);

	//		�[�x�X�e���V���̍쐻�i�V���h�E�}�b�v�j
	m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_depthStencil->SetDevice(device);
	m_depthStencil->SetWindow(rect);

	//		���_�[�x�V�F�[�_�[�̍쐻�i�V���h�E�}�b�v�j
	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthVS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs_depth.data(), vs_depth.size(),
			nullptr, m_shadowDepthShaderVS.ReleaseAndGetAddressOf()));

	//		�s�N�Z���[�x�V�F�[�_�[�̍쐻�i�V���h�E�}�b�v�j
	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_depth.data(), ps_depth.size(),
			nullptr, m_shadowDepthShaderPS.ReleaseAndGetAddressOf()));

	//		���_�V�F�[�_�[�̍쐻�i�V���h�E�}�b�v�j
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shader/Shadow/ShadowVS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(),
			nullptr, m_shadowShaderVS.ReleaseAndGetAddressOf()));

	//		�s�N�Z���V�F�[�_�[�̍쐻�i�V���h�E�}�b�v�j
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shader/Shadow/ShadowPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(),
			nullptr, m_shadowShaderPS.ReleaseAndGetAddressOf()));

	//		�萔�o�b�t�@�̍쐻
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf()));

	//		�萔�o�b�t�@�Q�̍쐻
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer2));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;				// GPU�̓ǂݎ��Ə������݂��\�Ȉ�ʓI�ȃ��\�[�X
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = 0;						// CPU�̓A�N�Z�X���Ȃ��̂�0
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer2.ReleaseAndGetAddressOf()));

	//		�T���v���[�̍쐻
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;

	device->CreateSamplerState(&sampler_desc,
		m_shadowMapSampler.ReleaseAndGetAddressOf());
}

void Shadow::Render()
{
	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_lightRotate);

	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_lightPosition);
}

void Shadow::ChangeRenderTarget(const DirectX::SimpleMath::Vector3& playerpos)
{

	playerPostion = playerpos;

	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->
		GetD3DDeviceContext();

	//		�V���h�E�}�b�v�̍쐻
	auto rtv = m_renderTexture->GetRenderTargetView();
	auto srv = m_renderTexture->GetShaderResourceView();
	auto dsv = m_depthStencil->GetDepthStencilView();

	//		�����_�[�^�[�Q�b�g��ύX����
	context->ClearRenderTargetView(rtv, DirectX::SimpleMath::Color(1, 1, 1, 1));
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);

	D3D11_VIEWPORT vp = { 0.0f,0.0f,LibrarySingleton::GetInstance()->GetScreenSize().x,
					LibrarySingleton::GetInstance()->GetScreenSize().y, 0.0f, 1.0f };

	context->RSSetViewports(1, &vp);

	//------------
	//		���C�g�̏���
	//-----------

	// ���C�g�̕���
	m_rightDirection = DirectX::SimpleMath::Vector3::
		Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_lightRotate);

	m_lightPosition = DirectX::SimpleMath::Vector3
	(playerPostion.x, playerPostion.y + 3, playerPostion.z);

	m_view = DirectX::SimpleMath::Matrix::
		CreateLookAt(m_lightPosition,
			m_rightDirection + m_lightPosition,
			DirectX::SimpleMath::Vector3::UnitY);

	//------------------------------
	//		�萔�o�b�t�@���X�V����
	//------------------------------

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//		GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);

	//		�萔�o�b�t�@���X�V
	ConstantBuffer cb = {};
	DirectX::SimpleMath::Matrix m = m_view * m_proj;
	cb.lightViewProj = XMMatrixTranspose(m);
	cb.lightPosition = m_lightPosition;
	cb.lightDirection = m_rightDirection;
	cb.lightAmbient = DirectX::SimpleMath::Color(0.3f, 0.3f, 0.3f);

	*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;

	//		GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
	context->Unmap(m_constantBuffer.Get(), 0);

}


//
//Shadow::Shadow(PlayerInformation* playerInformation)
//	:
//	m_playerInformation(playerInformation)
//{
//}
//
//Shadow::~Shadow()
//{
//}
//
//void Shadow::Initialize()
//{
//	//		�e�̏��𐶐�����
//	m_information = std::make_unique<ShadowInformation>();
//
//	//		�[�x�o�b�t�@�̍쐻
//	m_information->CreateDepthStencil();
//	//		�����_�[�e�N�X�`���̍쐻
//	m_information->CreateRenderTexture();
//
//	//		�e�̍쐻
//	CreateShadow();
//
//	// ���C�g�̉�]
//	DirectX::SimpleMath::Quaternion m_lightRotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
//		DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(89.0f), 0.0f);
//
//	// ���C�g�̕�����ݒ肷��
//	m_information->SetLightDirection(DirectX::SimpleMath::Vector3::
//		Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_lightRotate));
//
//	ConstantBufferDepth  cb = {};
//	cb.fCosTheta = cosf(DirectX::XMConvertToRadians(90.0f / 2.0f));
//
//	LibrarySingleton::GetInstance()->GetDeviceResources()
//		->GetD3DDeviceContext()->UpdateSubresource
//		(m_constantDepthBuffer.Get(), 0, nullptr, &cb, 0, 0);
//
//	m_information->SetConstBufferDepth(m_constantDepthBuffer);
//}
//
//void Shadow::ChangeTarget()
//{
//	/*
//	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->
//		GetD3DDeviceContext();
//	
//	auto states = LibrarySingleton::GetInstance()->GetCommonState();
//
//	//		�V���h�E�}�b�v�̍쐻
//	auto rtv = m_information->GetRenderTexture()->GetRenderTargetView();
//	auto srv = m_information->GetRenderTexture()->GetShaderResourceView();
//	auto dsv = m_information->GetDepthStencil()->GetDepthStencilView();
//
//	//		�����_�[�^�[�Q�b�g��ύX����
//	context->ClearRenderTargetView(rtv, DirectX::SimpleMath::Color(1, 1, 1, 1));
//	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
//	context->OMSetRenderTargets(1, &rtv, dsv);
//
//	D3D11_VIEWPORT vp = { 0.0f,0.0f,LibrarySingleton::GetInstance()->GetScreenSize().x,
//					LibrarySingleton::GetInstance()->GetScreenSize().y, 0.0f, 1.0f };
//
//	context->RSSetViewports(1, &vp);
//
//	//------------
//	//		���C�g�̏���
//	//-----------
//
//	DirectX::SimpleMath::Vector3 m_lightPosition = DirectX::SimpleMath::Vector3
//	(m_playerInformation->GetPlayerHeight().x,
//	 m_playerInformation->GetPlayerHeight().y + 3,
//	 m_playerInformation->GetPlayerHeight().z);
//	
//	DirectX::SimpleMath::Vector3 m_lightPosition;
//
//	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::
//		CreateLookAt(m_lightPosition,
//			m_information->GetLightDirection() + m_lightPosition,
//			DirectX::SimpleMath::Vector3::UnitY);
//
//	m_information->SetView(view);
//	
//
//	//------------------------------
//	//		�萔�o�b�t�@���X�V����
//	//------------------------------
//
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	//		GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
//	context->Map(m_constantShadowBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD,
//		0, &mappedResource);
//
//	//		�萔�o�b�t�@���X�V
//	ConstantBufferShadow cb = {};
//	DirectX::SimpleMath::Matrix m = view * m_information->GetProj();
//	cb.lightViewProj = XMMatrixTranspose(m);
//	cb.lightPosition = m_lightPosition;
//	cb.lightDirection = m_information->GetLightDirection();
//	cb.lightAmbient = DirectX::SimpleMath::Color(0.3f, 0.3f, 0.3f);
//
//	*static_cast<ConstantBufferShadow*>(mappedResource.pData) = cb;
//
//	//		GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
//	context->Unmap(m_constantShadowBuffer.Get(), 0);
//
//	//		�R���X�g�o�b�t�@��ݒ肷��
//	m_information->SetConstBufferShadow(m_constantShadowBuffer);
//	*/
//}
//
//void Shadow::CreateShadow()
//{
//	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();
//
//	RECT rect = { 0,0,LibrarySingleton::GetInstance()->GetScreenSize().x,
//			  LibrarySingleton::GetInstance()->GetScreenSize().y };
//
//	//		�����_�[�e�N�X�`���̍쐻�i�V���h�E�}�b�v�j
//	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
//	m_renderTexture->SetDevice(device);
//	m_renderTexture->SetWindow(rect);
//
//	//		�[�x�X�e���V���̍쐻�i�V���h�E�}�b�v�j
//	m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
//	m_depthStencil->SetDevice(device);
//	m_depthStencil->SetWindow(rect);
//
//	CreateShader();
//
//	CreateConstBuffer();
//
//	m_information->SetProj(DirectX::SimpleMath::Matrix::
//		CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(90.0f),
//			1.0f, 0.1f, 100.0f));
//
//
//	//		�T���v���[�̍쐻
//	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
//	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
//	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
//	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
//	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
//	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
//
//	device->CreateSamplerState(&sampler_desc,
//		m_shadowMapSampler.ReleaseAndGetAddressOf());
//
//	//m_information->SetShadowMapSampler(m_shadowMapSampler);
//}
//
//void Shadow::CreateShader()
//{
//	//		�f�o�C�X�̎擾
//	auto device = LibrarySingleton::GetInstance()
//		->GetDeviceResources()->GetD3DDevice();
//
//	//		���_�[�x�V�F�[�_�[�̍쐻�i�[�x�j
//	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthVS.cso");
//	DX::ThrowIfFailed(
//		device->CreateVertexShader(vs_depth.data(), vs_depth.size(),
//			nullptr, m_shadowDepthVS.ReleaseAndGetAddressOf()));
//
//	//		�[�x�p���_�V�F�[�_�[��ݒ肷��
//	//m_information->SetShadowDepthVS(m_shadowDepthVS);
//
//	//		�s�N�Z���[�x�V�F�[�_�[�̍쐻�i�[�x�j
//	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthPS.cso");
//	DX::ThrowIfFailed(
//		device->CreatePixelShader(ps_depth.data(), ps_depth.size(),
//			nullptr, m_shadowDepthPS.ReleaseAndGetAddressOf()));
//
//	//		�[�x�p�s�N�Z���V�F�[�_�[��ݒ肷��
//	//m_information->SetShadowDepthPS(m_shadowDepthPS);
//
//	//		���_�V�F�[�_�[�̍쐻�i�e�`��j
//	//std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shader/Shadow/ShadowVS.cso");
//	//DX::ThrowIfFailed(
//	//	device->CreateVertexShader(vs.data(), vs.size(),
//	//		nullptr, m_shadowVS.ReleaseAndGetAddressOf()));
//
//	//		�e�`��p���_�V�F�[�_�[��ݒ肷��
//	//m_information->SetShadowVS(m_shadowVS);
//
//	//		�s�N�Z���V�F�[�_�[�̍쐻�i�e�`��j
//	//std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shader/Shadow/ShadowPS.cso");
//	//DX::ThrowIfFailed(
//	//	device->CreatePixelShader(ps.data(), ps.size(),
//	//		nullptr, m_shadowPS.ReleaseAndGetAddressOf()));
//
//	//		�e�`��p�s�N�Z���V�F�[�_�[��ݒ肷��
//	//m_information->SetShadowPS(m_shadowPS);
//}
//
//void Shadow::CreateConstBuffer()
//{
//	
//	//		�f�o�C�X�̎擾
//	auto device = LibrarySingleton::GetInstance()
//		->GetDeviceResources()->GetD3DDevice();
//
//	//		�e�萔�o�b�t�@��ݒ肷��
//	D3D11_BUFFER_DESC bufferDesc = {};
//	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBufferShadow));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
//	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
//	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
//	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
//	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantShadowBuffer.ReleaseAndGetAddressOf()));
//
//	//		�[�x�萔�o�b�t�@�Q�̍쐻
//	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBufferDepth));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;				// GPU�̓ǂݎ��Ə������݂��\�Ȉ�ʓI�ȃ��\�[�X
//	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
//	bufferDesc.CPUAccessFlags = 0;						// CPU�̓A�N�Z�X���Ȃ��̂�0
//	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantDepthBuffer.ReleaseAndGetAddressOf()));
//	
//}
