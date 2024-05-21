/*
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WireObject.h"

#include <Effects.h>

WireObject::WireObject()
	:
	m_wireModel{},
	m_wireAvailableJudgement(false),
	m_range(120.0f)
{
}

WireObject::~WireObject()
{

}

void WireObject::Initialize()
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_wireModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Wire.cmo", *m_effect);

	m_wireRangeModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WireRange.cmo", *m_effect);

	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		���W
	m_position = { 0.0f, 30.0f, 700.0f };

	//		���W��ݒ肷��
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		�f�o�b�N���[���h�̔��a�̑傫��
	m_debugWorld = DirectX::SimpleMath::Matrix::CreateScale(m_range);

	//		���W��ݒ肷��
	m_debugWorld *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

void WireObject::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		�v���C���[�Ƃ̋�������肢�Ȃ��̏ꍇ
	if ((playerPosition - m_position).Length() < m_range + 7.0f)
	{
		//		�g�p�\
   		m_wireAvailableJudgement = true;
	}
	//		�g�p�s�\
	else m_wireAvailableJudgement = false;
}

void WireObject::Render(DrawMesh* drawMesh)
{
	//		�f�o�b�N�\�����ǂ���
	if (LibrarySingleton::GetInstance()->GetDebugJudgement())
	{
		//		���C���[���͂��͈�(����������)
		for (const auto& it : m_wireRangeModel->meshes)
		{
			auto mesh = it.get();

			mesh->PrepareForRendering(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
				*LibrarySingleton::GetInstance()->GetCommonState(), true);

			mesh->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
				m_debugWorld, LibrarySingleton::GetInstance()->GetView(),
				LibrarySingleton::GetInstance()->GetProj());
		}
	}

	//		���f���̕`��
	m_wireModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());
}

void WireObject::Finalize()
{
}
