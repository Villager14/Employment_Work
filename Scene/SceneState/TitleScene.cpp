/*
* @file		TitleScene.cpp
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//		�^�C�g���I���}�l�[�W���[�̐���
	m_titleSelectManager = std::make_unique<TitleSelectManager>();

	//		�^�C�g���I���}�l�[�W���[�̏�����
	m_titleSelectManager->Initialize();

	//		�^�C�g����BGM�̍Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		UI�V�F�[�_�[�}�l�[�W���[�̐���
	m_uiShaderManager = std::make_unique<UIRenderManager>();

	ConstBuffer buffer;

	//		�V�F�[�_�[�̍쐻
	m_uiShaderManager->Create(L"Resources/Texture/UI/GameOver/GameOver.png",
								L"Resources/Shader/UI/UIShaderVS.cso",
								L"Resources/Shader/UI/UIShaderGS.cso",
								L"Resources/Shader/UI/UIShaderPS.cso",
								buffer,
								{ 0.0f, 0.0f, }, { 1.0f, 1.0f },
								CENTER_POINT::MIDDLE_CENTER);

	//ConstBufferManager::ConstBuffer buffer;

	//m_uiShaderManager->GetConstBufferManager()->CreateConstBuffer(
	//LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(), buffer);
}

void TitleScene::Update()
{
	//		���j���[��Ԃ��ǂ����󂯎��
	m_titleSelectManager->SetMenuJudgement(m_sceneManager->GetMenuJudgement());

	//		�^�C�g���I���}�l�[�W���[�̍X�V����
	m_titleSelectManager->Update();

	//		�V�[�����I�����邩�ǂ���
	if (m_titleSelectManager->GetChangeScnenJudgemnet())
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_sceneManager->ChangeState(m_sceneManager->GetPlayScene());
	}
}

void TitleScene::Render()
{
	//		�^�C�g���I���}�l�[�W���[�̕`�揈��
	m_titleSelectManager->Render();

	ConstBuffer buffer;

	//		��]�s��𑗂�
	buffer.rotationMatrix = m_uiShaderManager->GetRotationMatrix();

	//		�E�B���h�E�T�C�Y�𑗂�
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	m_uiShaderManager->Render(buffer);
}

void TitleScene::Finalize()
{
	m_titleSelectManager.reset();
}
