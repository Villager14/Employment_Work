/*
* @file		ResultManager.h
* @brief	�㏸�ԍ��V�F�[�_�[
* @author	Morita
* @date		2024/07/05
*/

#include "pch.h"

#include "RiseNumberShader.h"

RiseNumberShader::RiseNumberShader()
{
}

RiseNumberShader::~RiseNumberShader()
{
}

void RiseNumberShader::Initialize(int dethCount, int clearTime, int score)
{
	//		UI�`��̐���
	m_uiRenderManager = std::make_unique<UIRenderManager>();

	//		�V�F�[�_�[�̐���
	m_uiRenderManager->Create(L"Resources/Texture/ResultScene/nomber.png",
		L"Resources/Shader/AboveNumber/AboveNumberVS.cso",
		L"Resources/Shader/AboveNumber/AboveNumberGS.cso",
		L"Resources/Shader/AboveNumber/AboveNumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_uiRenderManager->GetRotationMatrix();

	//		�����̏��̍쐻
	CreateNumber(DethCount1, { 970.0f, 140.0f }, (dethCount / 100) % 10, 0);
	CreateNumber(DethCount2, { 1030.0f, 140.0f }, (dethCount / 10) % 10, 1);
	CreateNumber(DethCount3, { 1090.0f, 140.0f }, dethCount % 10, 2);
	CreateNumber(ClearCount1, { 910.0f, 250.0f }, clearTime / 60 / 10, 3);
	CreateNumber(ClearCount2, { 970.0f, 250.0f }, clearTime / 60 % 10, 4);
	CreateNumber(ClearCount3, { 1030.0f, 250.0f }, clearTime % 60 / 10, 5);
	CreateNumber(ClearCount4, { 1090.0f, 250.0f }, clearTime % 60 % 10, 6);
	CreateNumber(Score1, { 910.0f, 360.0f }, score / 1000, 7);
	CreateNumber(Score2, { 970.0f, 360.0f }, (score / 100) % 10, 8);
	CreateNumber(Score3, { 1030.0f, 360.0f }, (score / 10) % 10, 9);
	CreateNumber(Score4, { 1090.0f, 360.0f }, (score / 10) % 10, 10);
}

void RiseNumberShader::Render(float time)
{
	//		�����̕`��
	for (auto const& pair : m_numberinformation)
	{
		//		�R���X�g�o�b�t�@�̒l�̍X�V
		buffer.time = { Library::Lerp(0.0f, 1.0f, Library::Clamp((time -0.3f * pair.second.viewNumber), 0.0f, 1.0f)), 0.0f, 0.0f, 0.0f };
		buffer.number = { static_cast<float>(pair.second.number), 0.0f, 0.0f, 0.0f };

		//		���W��ύX����
		m_uiRenderManager->SetPosition(pair.second.position);

		//		�`��
		m_uiRenderManager->Render(buffer);
	}
}

void RiseNumberShader::Finalize()
{
}

void RiseNumberShader::CreateNumber(NumberType type,
	DirectX::SimpleMath::Vector2 position,
	int number, int viewNumber)
{
	NumberInformation information;

	information.position = position;
	information.number = number;
	information.viewNumber = viewNumber;

	//		�����̏���ݒ肷��
	m_numberinformation.insert({ type, information });
}
