/*
* @file		Shwdow.h
* @brief	影オブジェクト
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

	// ライトの回転
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
	//		デバイスの取得
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(m_lightRange),
			1.0f, 0.1f, 100.0f);

	//		サイズ
	RECT rect = { 0,0,static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	//		レンダーテクスチャの作製（シャドウマップ）
	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_renderTexture->SetDevice(device);
	m_renderTexture->SetWindow(rect);

	//		深度ステンシルの作製（シャドウマップ）
	m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_depthStencil->SetDevice(device);
	m_depthStencil->SetWindow(rect);

	//		頂点深度シェーダーの作製（シャドウマップ）
	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthVS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs_depth.data(), vs_depth.size(),
			nullptr, m_shadowDepthShaderVS.ReleaseAndGetAddressOf()));

	//		ピクセル深度シェーダーの作製（シャドウマップ）
	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_depth.data(), ps_depth.size(),
			nullptr, m_shadowDepthShaderPS.ReleaseAndGetAddressOf()));

	//		頂点シェーダーの作製（シャドウマップ）
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shader/Shadow/ShadowVS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(),
			nullptr, m_shadowShaderVS.ReleaseAndGetAddressOf()));

	//		ピクセルシェーダーの作製（シャドウマップ）
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shader/Shadow/ShadowPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(),
			nullptr, m_shadowShaderPS.ReleaseAndGetAddressOf()));

	//		定数バッファの作製
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer));	// 確保するサイズ（16の倍数で設定する）
	// GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセスできるリソース
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUが内容を変更できるようにする
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf()));

	//		定数バッファ２の作製
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer2));	// 確保するサイズ（16の倍数で設定する）
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;				// GPUの読み取りと書き込みが可能な一般的なリソース
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
	bufferDesc.CPUAccessFlags = 0;						// CPUはアクセスしないので0
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer2.ReleaseAndGetAddressOf()));

	//		サンプラーの作製
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

	//		シャドウマップの作製
	auto rtv = m_renderTexture->GetRenderTargetView();
	auto srv = m_renderTexture->GetShaderResourceView();
	auto dsv = m_depthStencil->GetDepthStencilView();

	//		レンダーターゲットを変更する
	context->ClearRenderTargetView(rtv, DirectX::SimpleMath::Color(1, 1, 1, 1));
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);

	D3D11_VIEWPORT vp = { 0.0f,0.0f,LibrarySingleton::GetInstance()->GetScreenSize().x,
					LibrarySingleton::GetInstance()->GetScreenSize().y, 0.0f, 1.0f };

	context->RSSetViewports(1, &vp);

	//------------
	//		ライトの処理
	//-----------

	// ライトの方向
	m_rightDirection = DirectX::SimpleMath::Vector3::
		Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_lightRotate);

	m_lightPosition = DirectX::SimpleMath::Vector3
	(playerPostion.x, playerPostion.y + 3, playerPostion.z);

	m_view = DirectX::SimpleMath::Matrix::
		CreateLookAt(m_lightPosition,
			m_rightDirection + m_lightPosition,
			DirectX::SimpleMath::Vector3::UnitY);

	//------------------------------
	//		定数バッファを更新する
	//------------------------------

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//		GPUが定数バッファに対してアクセスを行わないようにする
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);

	//		定数バッファを更新
	ConstantBuffer cb = {};
	DirectX::SimpleMath::Matrix m = m_view * m_proj;
	cb.lightViewProj = XMMatrixTranspose(m);
	cb.lightPosition = m_lightPosition;
	cb.lightDirection = m_rightDirection;
	cb.lightAmbient = DirectX::SimpleMath::Color(0.3f, 0.3f, 0.3f);

	*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;

	//		GPUが定数バッファに対してのアクセスを許可する
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
//	//		影の情報を生成する
//	m_information = std::make_unique<ShadowInformation>();
//
//	//		深度バッファの作製
//	m_information->CreateDepthStencil();
//	//		レンダーテクスチャの作製
//	m_information->CreateRenderTexture();
//
//	//		影の作製
//	CreateShadow();
//
//	// ライトの回転
//	DirectX::SimpleMath::Quaternion m_lightRotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
//		DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(89.0f), 0.0f);
//
//	// ライトの方向を設定する
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
//	//		シャドウマップの作製
//	auto rtv = m_information->GetRenderTexture()->GetRenderTargetView();
//	auto srv = m_information->GetRenderTexture()->GetShaderResourceView();
//	auto dsv = m_information->GetDepthStencil()->GetDepthStencilView();
//
//	//		レンダーターゲットを変更する
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
//	//		ライトの処理
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
//	//		定数バッファを更新する
//	//------------------------------
//
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	//		GPUが定数バッファに対してアクセスを行わないようにする
//	context->Map(m_constantShadowBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD,
//		0, &mappedResource);
//
//	//		定数バッファを更新
//	ConstantBufferShadow cb = {};
//	DirectX::SimpleMath::Matrix m = view * m_information->GetProj();
//	cb.lightViewProj = XMMatrixTranspose(m);
//	cb.lightPosition = m_lightPosition;
//	cb.lightDirection = m_information->GetLightDirection();
//	cb.lightAmbient = DirectX::SimpleMath::Color(0.3f, 0.3f, 0.3f);
//
//	*static_cast<ConstantBufferShadow*>(mappedResource.pData) = cb;
//
//	//		GPUが定数バッファに対してのアクセスを許可する
//	context->Unmap(m_constantShadowBuffer.Get(), 0);
//
//	//		コンストバッファを設定する
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
//	//		レンダーテクスチャの作製（シャドウマップ）
//	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
//	m_renderTexture->SetDevice(device);
//	m_renderTexture->SetWindow(rect);
//
//	//		深度ステンシルの作製（シャドウマップ）
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
//	//		サンプラーの作製
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
//	//		デバイスの取得
//	auto device = LibrarySingleton::GetInstance()
//		->GetDeviceResources()->GetD3DDevice();
//
//	//		頂点深度シェーダーの作製（深度）
//	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthVS.cso");
//	DX::ThrowIfFailed(
//		device->CreateVertexShader(vs_depth.data(), vs_depth.size(),
//			nullptr, m_shadowDepthVS.ReleaseAndGetAddressOf()));
//
//	//		深度用頂点シェーダーを設定する
//	//m_information->SetShadowDepthVS(m_shadowDepthVS);
//
//	//		ピクセル深度シェーダーの作製（深度）
//	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shader/Shadow/Depth/ShadowDepthPS.cso");
//	DX::ThrowIfFailed(
//		device->CreatePixelShader(ps_depth.data(), ps_depth.size(),
//			nullptr, m_shadowDepthPS.ReleaseAndGetAddressOf()));
//
//	//		深度用ピクセルシェーダーを設定する
//	//m_information->SetShadowDepthPS(m_shadowDepthPS);
//
//	//		頂点シェーダーの作製（影描画）
//	//std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shader/Shadow/ShadowVS.cso");
//	//DX::ThrowIfFailed(
//	//	device->CreateVertexShader(vs.data(), vs.size(),
//	//		nullptr, m_shadowVS.ReleaseAndGetAddressOf()));
//
//	//		影描画用頂点シェーダーを設定する
//	//m_information->SetShadowVS(m_shadowVS);
//
//	//		ピクセルシェーダーの作製（影描画）
//	//std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shader/Shadow/ShadowPS.cso");
//	//DX::ThrowIfFailed(
//	//	device->CreatePixelShader(ps.data(), ps.size(),
//	//		nullptr, m_shadowPS.ReleaseAndGetAddressOf()));
//
//	//		影描画用ピクセルシェーダーを設定する
//	//m_information->SetShadowPS(m_shadowPS);
//}
//
//void Shadow::CreateConstBuffer()
//{
//	
//	//		デバイスの取得
//	auto device = LibrarySingleton::GetInstance()
//		->GetDeviceResources()->GetD3DDevice();
//
//	//		影定数バッファを設定する
//	D3D11_BUFFER_DESC bufferDesc = {};
//	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBufferShadow));	// 確保するサイズ（16の倍数で設定する）
//	// GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセスできるリソース
//	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
//	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUが内容を変更できるようにする
//	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantShadowBuffer.ReleaseAndGetAddressOf()));
//
//	//		深度定数バッファ２の作製
//	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBufferDepth));	// 確保するサイズ（16の倍数で設定する）
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;				// GPUの読み取りと書き込みが可能な一般的なリソース
//	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
//	bufferDesc.CPUAccessFlags = 0;						// CPUはアクセスしないので0
//	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantDepthBuffer.ReleaseAndGetAddressOf()));
//	
//}
