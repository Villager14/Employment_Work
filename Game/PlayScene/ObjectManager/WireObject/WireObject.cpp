/*
* 
* @file		FloorObject.cpp
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WireObject.h"

#include <Effects.h>

WireObject::WireObject()
	:
	//m_objectManager(objectManager),
	m_wireModel{},
	m_wireAvailableJudgement(false),
	m_range(120.0f),
	m_rotation(0.0f)
{
}

WireObject::~WireObject()
{

}

void WireObject::Initialize(DirectX::SimpleMath::Vector3 position)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
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


	//		
	m_wingPosition.push_back({ 4.0f, 5.0f, 3.6f });
	m_wingPosition.push_back({ 4.2f, 5.0f, -3.0f });
	m_wingPosition.push_back({ -4.0f, 5.0f, 3.6f });
	m_wingPosition.push_back({ -4.2f, 5.0f, -3.0f });


	//		座標
	m_position = position;

	//		座標を設定する
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		デバックワールドの半径の大きさ
	m_debugWorld = DirectX::SimpleMath::Matrix::CreateScale(m_range);

	//		座標を設定する
	m_debugWorld *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

void WireObject::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		プレイヤーとの距離が一定いないの場合
	if ((playerPosition - m_position).Length() < m_range + 7.0f)
	{
		//		使用可能
   		m_wireAvailableJudgement = true;
	}
	//		使用不可能
	else m_wireAvailableJudgement = false;

	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * 10.0f;
}

void WireObject::Render()
{
	//		デバック表示かどうか
	if (LibrarySingleton::GetInstance()->GetDebugJudgement())
	{
		//		ワイヤーが届く範囲(半透明処理)
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

	//		モデルの描画
	m_wireModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());

	for (int i = 0; i < 4; ++i)
	{
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation);
		
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_wingPosition[i]);
		world *= DirectX::SimpleMath::Matrix::CreateTranslation({m_world._41, m_world._42, m_world._43});

		//		羽モデルの描画
		m_wingModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj());
	}
}

void WireObject::Finalize()
{
}
