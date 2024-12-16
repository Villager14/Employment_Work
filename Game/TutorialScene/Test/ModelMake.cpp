
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
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models/Player");

	//		���f���̓ǂݍ���
	std::unique_ptr<DirectX::Model> model = DirectX::Model::CreateFromCMO(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Player/Head.cmo", *m_effect);

	return std::move(model);
}
