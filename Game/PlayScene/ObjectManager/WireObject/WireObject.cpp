/*
* 
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WireObject.h"

#include "Library/Factory/IFactory.h"

#include <Effects.h>

WireObject::WireObject(ObjectManager* objectManager)
	:
	m_wireModel{},
	m_rotation(0.0f),
	m_objectManager(objectManager),
	m_number(0)
{
}

WireObject::~WireObject()
{

}

void WireObject::Initialize(ObjectInformation information)
{
	int size = static_cast<int>((*m_objectManager->GetUseWireInformation()).size());

	if (size == 0) m_number = 0;
	else m_number = size - 1;

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_wireModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Drone.cmo", *m_effect);

	m_wireModel->UpdateEffects([](DirectX::IEffect* effect)
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

	m_wireRangeModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WireRange.cmo", *m_effect);

	m_wingModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Wing.cmo", *m_effect);

	m_wingModel->UpdateEffects([](DirectX::IEffect* effect)
		{
			auto fog = dynamic_cast<DirectX::IEffectFog*>(effect);

			if (fog)
			{
				fog->SetFogEnabled(true);
				fog->SetFogStart(100.0f);
				fog->SetFogEnd(300.0f);
				fog->SetFogColor(DirectX::Colors::MediumSeaGreen);
			}
		});

	//		�H�̍��W
	m_wingPosition.push_back(WING_POSITION_0);
	m_wingPosition.push_back(WING_POSITION_1);
	m_wingPosition.push_back(WING_POSITION_2);
	m_wingPosition.push_back(WING_POSITION_3);

	//		���W��ݒ肷��
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	//		�f�o�b�N���[���h�̔��a�̑傫��
	m_debugWorld = DirectX::SimpleMath::Matrix::CreateScale(WIRE_RANGE);

	//		���W��ݒ肷��
	m_debugWorld *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);
}

void WireObject::Update()
{
	//		�v���C���[�Ƃ̋�������肢�Ȃ��̏ꍇ
	if ((m_objectManager->GetPlayerPosition()
		- (*m_objectManager->GetUseWireInformation()
		)[m_number].position).Length() < WIRE_RANGE + 7.0f)
	{
		//		�g�p�\
		(*m_objectManager->GetUseWireInformation())
			[m_number].m_usedJudgement = true;
	}
	//		�g�p�s�\
	else (*m_objectManager->GetUseWireInformation())
			[m_number].m_usedJudgement = false;

	//		�H�̉�]��
	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * WING_ROTATION_SPEED;
}

void WireObject::Render()
{
	//		�f�o�b�N�̕`��
	DebugRender();

	//		�J�������猩���Ȃ��悤�ɃJ�����O����
	//if (m_objectManager->Culling(m_objectManager->GetPlayerPosition())) return;

	//		���f���̕`��
	m_wireModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());

	//		�H�̕`��
	WingRender();
}

void WireObject::Finalize()
{
}

void WireObject::DebugRender()
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
}

void WireObject::WingRender()
{
	for (int i = 0; i < 4; ++i)
	{
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation);

		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_wingPosition[i]);
		world *= DirectX::SimpleMath::Matrix::CreateTranslation({ m_world._41, m_world._42, m_world._43 });

		//		�H���f���̕`��
		m_wingModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj());
	}
}
