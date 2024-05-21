/*
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
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_wireModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Wire.cmo", *m_effect);

	m_wireRangeModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WireRange.cmo", *m_effect);

	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		座標
	m_position = { 0.0f, 30.0f, 700.0f };

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
}

void WireObject::Render(DrawMesh* drawMesh)
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
}

void WireObject::Finalize()
{
}
