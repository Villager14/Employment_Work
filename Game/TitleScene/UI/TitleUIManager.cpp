
#include "pch.h"

#include "TitleUIManager.h"

TitleUIManager::TitleUIManager(TitleSelectManager* titleSceneManager)
	:
	m_titleSceneManager(titleSceneManager)
{
}

TitleUIManager::~TitleUIManager()
{
}

void TitleUIManager::Initialize()
{
	m_shader->Create(L"Resources/Texture/TitleScene/TitleRogo.png",
		L"Resources/Shader/UI/UIShaderVS.cso",
		L"Resources/Shader/UI/UIShaderGS.cso",
		L"Resources/Shader/UI/UIShaderPS.cso",
		m_constBuffer,
		{ 0.0f, -170.0f , }, { m_titleSceneManager->GetMaxScale(),
		m_titleSceneManager->GetMaxScale()},
		CENTER_POINT::MIDDLE_CENTER);

	CreateUIInformation({ 0.0f, -170.0f}, { m_titleSceneManager->GetMaxScale(),
		m_titleSceneManager->GetMaxScale()},
		TitleSelectManager::UIType::TitleRogo);
}

void TitleUIManager::CreateUIInformation(DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 size,
	TitleSelectManager::UIType type)
{
	UIInformation uiInformation;

	uiInformation.position = position;
	uiInformation.scale = size;

	m_shaderInformation.insert({ type, uiInformation });
}

void TitleUIManager::Update()
{
}

void TitleUIManager::Render()
{
}
