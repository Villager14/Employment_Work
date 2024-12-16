/*
* @file		GoalObject.cpp
* @brief	�S�[���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "GoalObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

GoalObject::GoalObject(ObjectManager* objectManager)
	:
	m_goalModel{},
	m_rotation(0.0f),
	m_objectManager(objectManager)
{
	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

GoalObject::~GoalObject()
{

}

void GoalObject::Initialize(ObjectInformation information)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_goalModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Goal.cmo", *m_effect);

	m_goalModel->UpdateEffects([&](DirectX::IEffect* effect)
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

	m_position = information.position;

	m_rotation = information.rotation;

	//		����������
	m_objectMesh[0]->Initialize(L"Resources/ModelMesh/Goal.obj", false);
	m_objectMesh[1]->Initialize(L"Resources/ModelMesh/GoalGate.obj", false);

	m_world = DirectX::SimpleMath::Matrix::CreateScale(1.0f);

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh[0]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);
	m_objectMesh[1]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);

	m_objectMesh[0]->SetObuectType(ObjectMesh::ObjectType::Floor);
	m_objectMesh[1]->SetObuectType(ObjectMesh::ObjectType::Goal);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		�ʏ�`�������悤�ɂ���
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		�u���[�����|����悤�ɂ���
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

	//		�u���[���̐[�x�`��͕`�悵�Ȃ�
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

	//		�t�H�O�̏����̏ꍇ�`�悷��
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		�A���t�@�̏����̏ꍇ�`�悷��
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

void GoalObject::Update()
{
}

void GoalObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	UNREFERENCED_PARAMETER(postEffectObjectShader);
	UNREFERENCED_PARAMETER(flag);

	//		�t���O��false�̏ꍇ���������Ȃ�	
	if ((flag & m_postEffectFlag->GetFlag()) != 0)
	{
		m_world = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation.z));

		m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y));

		m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

		auto context = LibrarySingleton::GetInstance()->GetDeviceResources()
			->GetD3DDeviceContext();

		m_goalModel->Draw(context,
			*LibrarySingleton::GetInstance()->GetCommonState(),
			m_world,
			LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), false, [&]()
			{
				//		�|�X�g�G�t�F�N�g��
				if (flag & PostEffectFlag::Flag::AlphaDepth)
				{
					// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
					context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
				}
				else
				{
					m_objectManager->GetGenerationWorld()->Shader(context);
				}
			}
		);
	}
}

void GoalObject::Finalize()
{
	m_goalModel.reset();

	for (auto& e : m_objectMesh)
	{
		e->Finalize();
	}
}
