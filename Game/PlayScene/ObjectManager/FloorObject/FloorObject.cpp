/*
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "FloorObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

FloorObject::FloorObject(ShadowInformation* shadowInformation)
	:
	m_floorModel{},
	m_shadowInformation(shadowInformation)
{
}

FloorObject::~FloorObject()
{

}

void FloorObject::Initialize()
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Floor.cmo", *m_effect);

	/*
	m_floorModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(false);
				basicEffect->SetPerPixelLighting(false);
				basicEffect->SetTextureEnabled(false);
				basicEffect->SetVertexColorEnabled(false);
				basicEffect->SetFogEnabled(false);
			}

		});

	// �s�N�Z���V�F�[�_�[�̍쐬�i�g�[���X�p�j
	std::vector<uint8_t> ps_torus = DX::ReadData(L"Resources/Shader/Model/ModelPS.cso");
	DX::ThrowIfFailed(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice()->CreatePixelShader(ps_torus.data(),
		ps_torus.size(), nullptr, m_floorPS.ReleaseAndGetAddressOf())
	);

	// �e�N�X�`���̃��[�h 
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Textures/floor.png",
		nullptr,
		m_texture.GetAddressOf()
	);
	*/

	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		����������
	m_objectMesh->Initialize(L"Resources/ModelMesh/Floor.obj");

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), {0.0f, 0.0f, 0.0f});

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Floor);

}

void FloorObject::Update()
{
}

void FloorObject::Render(DrawMesh* drawMesh)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto common = LibrarySingleton::GetInstance()->GetCommonState();

	/*
	m_floorModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			////		�萔�o�b�t�@�̐ݒ�
			//ID3D11Buffer* cbuff[] = { m_shadowInformation->GetConstBufferShadow().Get(),
			//						m_shadowInformation->GetConstBufferDepth().Get()};

			//
			//context->VSSetConstantBuffers(1, 1, cbuff);
			//context->PSSetConstantBuffers(1, 2, cbuff);
			//
			////		�V�F�[�_�[���\�[�X�r���[���󂯎��
			//auto srv = m_shadowInformation->GetRenderTexture()->GetShaderResourceView();

			////		�쐬�����V���h�E�}�b�v�����\�[�X�Ƃ��Đݒ肷��
			//context->PSSetShaderResources(1, 1, &srv);

			////		�e�N�X�`���T���v���[�̐ݒ�
			//ID3D11SamplerState* samplers[] = 
			//{ LibrarySingleton::GetInstance()->GetCommonState()->PointWrap(),
			//m_shadowInformation->GetShadowMapSampler().Get() };
			//context->PSSetSamplers(0, 2, samplers);

			////		�V�F�[�_�[�̐ݒ�
			//context->VSSetShader(m_shadowInformation->GetShadowVS().Get(), nullptr, 0);
			//context->PSSetShader(m_shadowInformation->GetShadowPS().Get(), nullptr, 0);

		});
		*/


	m_floorModel->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//ID3D11SamplerState* samplesrs[1] = { common->PointWrap() };
			//context->PSSetSamplers(0, 1, samplesrs);

			//// �I���W�i���s�N�Z���V�F�[�_�[�̐ݒ�
			//context->PSSetShader(m_floorPS.Get(), nullptr, 0);

		});


	//		���b�V���̕`��
	//drawMesh->StaticRender(m_objectMesh.get());
}

void FloorObject::Finalize()
{
}
