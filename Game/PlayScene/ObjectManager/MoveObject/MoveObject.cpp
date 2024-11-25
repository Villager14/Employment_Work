/*
* @file		MoveObject.cpp
* @brief	移動オブジェクトの描画
* @author	Morita
* @date		2024/11/13
*/

#include "pch.h"

#include "MoveObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

#include <SpriteFont.h>

MoveObject::MoveObject(ObjectManager* objectManager)
	:
	m_floorModel{},
	m_objectManager(objectManager),
	m_time(0.0f),
	m_speed(0.0f)
{
	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

MoveObject::~MoveObject()
{

}

void MoveObject::Initialize(ObjectInformation information)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);
	
	m_floorModel->UpdateEffects([&](DirectX::IEffect* effect)
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

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		初期化処理
	m_objectMesh->Initialize(oss2.str().c_str(), false);

	m_firstPosition = information.position;
	m_secondPosition = information.movePosition;
	m_rotation = information.rotation;
	m_position = m_firstPosition;
	m_speed = information.speed;

	m_objectMesh->MoveProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::MoveObject);

	// ピクセルシェーダーの作成
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		ブルームを掛けるようにする
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

	//		ブルームの深度描画は描画しない
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);

	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		アルファの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

void MoveObject::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_speed;

	m_position = DirectX::SimpleMath::Vector3::Lerp(m_firstPosition, m_secondPosition, (cosf(m_time) + 1.0f) / 2.0f);

	//		メッシュの更新
	m_objectMesh->MoveProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);
}

void MoveObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto common = LibrarySingleton::GetInstance()->GetCommonState();

	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	m_world = DirectX::SimpleMath::Matrix::Identity;
	
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y));

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_floorModel->Draw(context,
		*common,
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//		ポストエフェクト時
			if (flag & PostEffectFlag::Flag::Bloom)
			{
				//		ポストエフェクト時
				if (flag & PostEffectFlag::Flag::AlphaDepth)
				{
					// ポストエフェクト時のシェーダー設定
					context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
				}
				else
				{
					context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
				}
			}
			else
			{
				m_objectManager->GetGenerationWorld()->Shader(context);
			}
		});
}

void MoveObject::Finalize()
{
	m_floorModel.reset();
	m_objectMesh->Finalize();
}
