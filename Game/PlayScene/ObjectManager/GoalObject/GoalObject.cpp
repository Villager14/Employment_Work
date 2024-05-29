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

GoalObject::GoalObject()
	:
	m_floorModel{}
{
}

GoalObject::~GoalObject()
{

}

void GoalObject::Initialize()
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Goal.cmo", *m_effect);

	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	DirectX::SimpleMath::Vector3 position = { 0.0f, 39.0f, 810.0f };

	//		����������
	m_objectMesh->Initialize(L"Resources/ModelMesh/Goal.obj");

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Goal);

}

void GoalObject::Update()
{
}

void GoalObject::Render(DrawMesh* drawMesh)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	m_floorModel->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());
}

void GoalObject::Finalize()
{
}
