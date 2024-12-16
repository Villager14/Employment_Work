
#include "pch.h"

#include "ModelMake.h"

ModelMake::ModelMake()
{

}

ModelMake::~ModelMake()
{

}

std::unique_ptr<DirectX::Model> ModelMake::Make()
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models/Player");

	//		モデルの読み込み
	std::unique_ptr<DirectX::Model> model = DirectX::Model::CreateFromCMO(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Player/Head.cmo", *m_effect);

	return std::move(model);
}
