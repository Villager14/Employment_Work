/*
* @file		GoalObject.cpp
* @brief	ゴールオブジェクトの描画
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
	//		オブジェクトメッシュの生成
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

GoalObject::~GoalObject()
{

}

void GoalObject::Initialize(ObjectInformation information)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
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

	//		初期化処理
	m_objectMesh[0]->Initialize(L"Resources/ModelMesh/Goal.obj", false);
	m_objectMesh[1]->Initialize(L"Resources/ModelMesh/GoalGate.obj", false);

	m_world = DirectX::SimpleMath::Matrix::CreateScale(1.0f);

	//		静的オブジェクトにする
	m_objectMesh[0]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);
	m_objectMesh[1]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);

	m_objectMesh[0]->SetObuectType(ObjectMesh::ObjectType::Floor);
	m_objectMesh[1]->SetObuectType(ObjectMesh::ObjectType::Goal);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		ブルームを掛けるようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

	//		ブルームの深度描画は描画しない
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		アルファの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

void GoalObject::Update()
{
}

void GoalObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	UNREFERENCED_PARAMETER(postEffectObjectShader);
	UNREFERENCED_PARAMETER(flag);

	//		フラグがfalseの場合処理をしない	
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
				//		ポストエフェクト時
				if (flag & PostEffectFlag::Flag::AlphaDepth)
				{
					// ポストエフェクト時のシェーダー設定
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
