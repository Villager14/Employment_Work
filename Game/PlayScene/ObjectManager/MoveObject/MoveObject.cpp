/*
* @file		MoveObject.cpp
* @brief	�ړ��I�u�W�F�N�g�̕`��
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
	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

MoveObject::~MoveObject()
{

}

void MoveObject::Initialize(ObjectInformation information)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		���f���̓ǂݍ���
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

	//		����������
	m_objectMesh->Initialize(oss2.str().c_str(), false);

	m_firstPosition = information.position;
	m_secondPosition = information.movePosition;
	m_rotation = information.rotation;
	m_position = m_firstPosition;
	m_speed = information.speed;

	m_objectMesh->MoveProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::MoveObject);

	// �s�N�Z���V�F�[�_�[�̍쐬
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	//		�ʏ�`�������悤�ɂ���
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		�u���[�����|����悤�ɂ���
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

	//		�u���[���̐[�x�`��͕`�悵�Ȃ�
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);

	//		�t�H�O�̏����̏ꍇ�`�悷��
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		�A���t�@�̏����̏ꍇ�`�悷��
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

void MoveObject::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_speed;

	m_position = DirectX::SimpleMath::Vector3::Lerp(m_firstPosition, m_secondPosition, (cosf(m_time) + 1.0f) / 2.0f);

	//		���b�V���̍X�V
	m_objectMesh->MoveProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);
}

void MoveObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto common = LibrarySingleton::GetInstance()->GetCommonState();

	//		�t���O��false�̏ꍇ���������Ȃ�	
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

			//		�|�X�g�G�t�F�N�g��
			if (flag & PostEffectFlag::Flag::Bloom)
			{
				//		�|�X�g�G�t�F�N�g��
				if (flag & PostEffectFlag::Flag::AlphaDepth)
				{
					// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
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
