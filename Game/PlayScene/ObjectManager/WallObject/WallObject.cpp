/*
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WallObject.h"

#include <Effects.h>

WallObject::WallObject()
	:
	m_floorModel{}
{
}

WallObject::~WallObject()
{

}

void WallObject::Initialize()
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WallObject01.cmo", *m_effect);

	m_floorModel->UpdateEffects([](DirectX::IEffect* effect)
	{
		auto fog = dynamic_cast<DirectX::IEffectFog*>(effect);

		if (fog)
		{
			fog->SetFogEnabled(true);
			fog->SetFogStart(200.0f);
			fog->SetFogEnd(350.0f);
			fog->SetFogColor(DirectX::Colors::MediumSeaGreen);
		}
	});

	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		����������
	m_objectMesh->Initialize(L"Resources/ModelMesh/WallObject01.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationY(0.0f);

	m_move = { 0.0f, 0.0f, 0.0f };

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh->StaticProcess(m_world, m_move);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_move);

	//		�I�u�W�F�N�g�^�C�v�̐ݒ�i�ǁj
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Wall);
}

void WallObject::Update()
{
}

void WallObject::Render(DrawMesh* drawMesh)
{
	UNREFERENCED_PARAMETER(drawMesh);

	//		���f���̕`��
	m_floorModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());

	//		���b�V���̕`��
	//drawMesh->StaticRender(m_objectMesh.get());
}

void WallObject::Finalize()
{
}
