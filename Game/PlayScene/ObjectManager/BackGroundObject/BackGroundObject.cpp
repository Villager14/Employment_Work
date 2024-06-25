/*
* @file		BackGroundObject.cpp
* @brief	背景オブジェクト
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
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
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


	//		背景の情報を生成する
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
		//		カリングの処理
		if (!Culling(i, cameraVelocity, cameraPosition)) continue;

		//		回転処理
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::
			CreateFromQuaternion(m_information->GetObjectQuaternion()[i]);

		//		座標
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_information->GetObjectPosition()[i]);

		//		モデルの描画
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

	//		カメラからのオブジェクトの距離
	DirectX::SimpleMath::Vector3 objectVelocityUnder =
		m_information->GetObjectPosition()[index] - cameraPosition;

	//		正規化処理
	objectVelocityUnder.Normalize();

	//		オブジェクトの座標
	DirectX::SimpleMath::Vector3 velocity = m_information->GetObjectPosition()[index];

	//		オブジェクトの上部の座標
	velocity += DirectX::SimpleMath::Vector3::Transform({0.0f, 1.0f, 0.0f},
		m_information->GetObjectQuaternion()[index]) * 400.0f;

	//		カメラからのオブジェクトの距離上部
	DirectX::SimpleMath::Vector3 objectVelocityTop =
		velocity - cameraPosition;

	//		正規化処理
	objectVelocityTop.Normalize();

	//		内積が０より小さい場合処理をしない
	if (cameraVelocity.Dot(objectVelocityUnder) < 0.0f &&
		cameraVelocity.Dot(objectVelocityTop) < 0.0f)
	{
		return false;
	}

	return true;
}
