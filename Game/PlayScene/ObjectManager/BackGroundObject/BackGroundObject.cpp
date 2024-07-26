/*
* @file		BackGroundObject.cpp
* @brief	�w�i�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "BackGroundObject.h"

#include "PostProcess.h"

#include "Common/ReaData.h"

BackGroundObject::BackGroundObject()
{
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::Initialize(std::vector<ObjectMesh*> mesh,
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Background.cmo", *m_effect);

	m_floorModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			/*
			auto fog = dynamic_cast<DirectX::IEffectFog*>(effect);

			if (fog)
			{
				fog->SetFogEnabled(true);
				fog->SetFogStart(100.0f);
				fog->SetFogEnd(300.0f);
				fog->SetFogColor(DirectX::Colors::MediumSeaGreen);
			}

			auto light = dynamic_cast<DirectX::IEffectLights*>(effect);

			if (light)
			{
				light->SetAmbientLightColor(DirectX::SimpleMath::Vector3::Zero);
				light->SetLightEnabled(0, false);
				light->SetLightEnabled(1, false);
				light->SetLightEnabled(2, false);
			}

			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
			*/

			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
			}

		});

	//		�w�i�̏��𐶐�����
	m_information = std::make_unique<BackGroundObjectInformation>();

	m_information->Create(mesh, wirePosition);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�g�[���X�p�j
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	UNREFERENCED_PARAMETER(m_constBuffer);

	ConstBuffer buffer = {};

	//		�V�F�[�_�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(buffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateBuffer(&bd, nullptr, &m_buffer);

	m_constBuffer.fogLength = {100.0f, 300.0f, 0.0f,0.0f};
	m_constBuffer.fogColor = DirectX::Colors::MediumSeaGreen;
}

void BackGroundObject::Update()
{
}

void BackGroundObject::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	for (int i = 0, max = static_cast<int>(m_information->GetObjectPosition().size()); i < max; ++i)
	{
		//		�J�����O�̏���
		if (!Culling(i, cameraVelocity, cameraPosition)) continue;

		//		��]����
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::
			CreateFromQuaternion(m_information->GetObjectQuaternion()[i]);

		//		���W
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_information->GetObjectPosition()[i]);

		//		���f���̕`��
		m_floorModel->Draw(context,
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), false, [&]() {

				m_constBuffer.cameraPosition = { cameraPosition.x, cameraPosition.y, cameraPosition.z, 0.0f };

				//		�󂯓n���p�o�b�t�@
				context->UpdateSubresource(m_buffer.Get(), 0, NULL, &m_constBuffer, 0, 0);

				//		�萔�o�b�t�@�̐ݒ�
				ID3D11Buffer* cbuff[] = { m_buffer.Get()};

				context->PSSetConstantBuffers(0, 1, cbuff);

				context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
			});
	}
}

void BackGroundObject::Finalize()
{
}

bool BackGroundObject::Culling(int index,
	DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	if ((DirectX::SimpleMath::Vector3(m_information->GetObjectPosition()[index].x,
		0.0f, m_information->GetObjectPosition()[index].z) -
		DirectX::SimpleMath::Vector3(cameraPosition.x, 0.0f, cameraPosition.z)).Length() > 400.0f)
	{
		return false;
	}

	//		�J��������̃I�u�W�F�N�g�̋���
	DirectX::SimpleMath::Vector3 objectVelocityUnder =
		m_information->GetObjectPosition()[index] - cameraPosition;

	//		���K������
	objectVelocityUnder.Normalize();

	//		�I�u�W�F�N�g�̍��W
	DirectX::SimpleMath::Vector3 velocity = m_information->GetObjectPosition()[index];

	//		�I�u�W�F�N�g�̏㕔�̍��W
	velocity += DirectX::SimpleMath::Vector3::Transform({0.0f, 1.0f, 0.0f},
		m_information->GetObjectQuaternion()[index]) * 400.0f;

	//		�J��������̃I�u�W�F�N�g�̋����㕔
	DirectX::SimpleMath::Vector3 objectVelocityTop =
		velocity - cameraPosition;

	//		���K������
	objectVelocityTop.Normalize();

	//		���ς��O��菬�����ꍇ���������Ȃ�
	if (cameraVelocity.Dot(objectVelocityUnder) < 0.0f &&
		cameraVelocity.Dot(objectVelocityTop) < 0.0f)
	{
		return false;
	}

	return true;
}
