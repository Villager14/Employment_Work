/*
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "FloorObject.h"

#include <Effects.h>

FloorObject::FloorObject()
	:
	m_floorModel{}
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
	//		���f���̕`��
	m_floorModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());

	//		���b�V���̕`��
	drawMesh->StaticRender(m_objectMesh.get());
}

void FloorObject::Finalize()
{
}
