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

BackGroundObject::BackGroundObject(ObjectManager* objectManager)
	:
	m_objectManager(objectManager)
{
	//		�w�i�̏��𐶐�����
	m_information = std::make_unique<BackGroundObjectInformation>();

	//		�|�X�g�G�t�F�N�g�t���O
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
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
	m_backGroundModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Background.cmo", *m_effect);

	
	m_backGroundModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			
			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
			}
		});
	//*/

	m_information->Create(mesh, wirePosition);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�g�[���X�p�j
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	//		�u���[�����|����悤�ɂ���
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

	//		�ʏ�`�掞�ɂ��`�悷��悤�ɂ����
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		�u���[���̐[�x�`��͕`�悵�Ȃ�
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

	//		�t�H�O�̏����̏ꍇ�`�悷��
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);
}

void BackGroundObject::Update()
{
}

void BackGroundObject::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition,
	PostEffectFlag::Flag flag,
	PostEffectObjectShader* objectShader)
{
	UNREFERENCED_PARAMETER(objectShader);

	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		�t���O��false�̏ꍇ���������Ȃ�	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}


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
		m_backGroundModel->Draw(context,
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), false, [&]() {

				context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
			});

	}
}

void BackGroundObject::Finalize()
{
	m_information->Finalize();
}

bool BackGroundObject::Culling(int index,
	DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	if ((DirectX::SimpleMath::Vector3(m_information->GetObjectPosition()[index].x,
		0.0f, m_information->GetObjectPosition()[index].z) -
		DirectX::SimpleMath::Vector3(cameraPosition.x, 0.0f, cameraPosition.z)).Length() > 500.0f)
	{
		return false;
	}

	//		�J��������̃I�u�W�F�N�g�̕���
	DirectX::SimpleMath::Vector3 objectVelocityUnder =
		m_information->GetObjectPosition()[index] - cameraPosition;

	//		Y���͋C�ɂ��Ȃ��悤�ɂ���
	objectVelocityUnder.y = 0.0f;

	DirectX::SimpleMath::Vector3 cameraDirection = cameraVelocity;

	cameraDirection.y = 0.0f;

	//		���K������
	objectVelocityUnder.Normalize();

	if (cameraDirection.Dot(objectVelocityUnder) < -0.2f)
	{
		return false;
	}


	return true;
}
