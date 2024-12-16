/*
* @file		StaticObject.cpp
* @brief	停止オブジェクトの描画
* @author	Morita
* @date		2024/12/11
*/

#include "pch.h"

#include "StaticObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

#include <SpriteFont.h>

StaticObject::StaticObject(ObjectManager* objectManager)
	:
	m_floorModel{},
	m_objectManager(objectManager)
{
	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

StaticObject::~StaticObject()
{

}

void StaticObject::Initialize(ObjectInformation information)
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

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(information.rotation.y));

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(information.rotation.y)), information.position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Floor);

	// ピクセルシェーダーの作成
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	if (information.effectFlag)
	{
		//		ブルームを掛けるようにする
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

		//		ブルームの深度描画は描画しない
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);
	}
	else
	{
		//		ブルームを掛けるようにする
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

		//		ブルームの深度描画は描画しない
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);
	}

	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		アルファの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

void StaticObject::Update()
{
}

void StaticObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto common = LibrarySingleton::GetInstance()->GetCommonState();

	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	m_floorModel->Draw(context,
		*common,
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//		ポストエフェクト時
			if (flag & PostEffectFlag::Flag::AlphaDepth)
			{
				// ポストエフェクト時のシェーダー設定
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}
			//		ポストエフェクト時
			else if (flag & PostEffectFlag::Flag::Bloom)
			{
				// ポストエフェクト時のシェーダー設定
				context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
			}
			else
			{
				m_objectManager->GetGenerationWorld()->Shader(context);
			}
		});
}

void StaticObject::Finalize()
{
	m_floorModel.reset();
	m_objectMesh->Finalize();
}
