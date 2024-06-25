/*
* @file		BackGroundObject.cpp
* @brief	�w�i�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "BackGroundObject.h"

#include "PostProcess.h"

BackGroundObject::BackGroundObject()
{
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::Initialize(std::vector<ObjectMesh*> mesh,
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Background.cmo", *m_effect);

	m_floorModel->UpdateEffects([](DirectX::IEffect* effect)
		{
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

			//std::unique_ptr<DirectX::SkinnedNormalMapEffect> normal = std::make_unique<DirectX::SkinnedNormalMapEffect>(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice());
		});


	//		�w�i�̏��𐶐�����
	m_information = std::make_unique<BackGroundObjectInformation>();

	m_information->Create(mesh, wirePosition);
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
			LibrarySingleton::GetInstance()->GetProj());
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
