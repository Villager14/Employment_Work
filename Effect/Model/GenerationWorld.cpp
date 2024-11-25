/*
* @file		GenerationWorld.h
* @brief	世界の生成オブジェクトシェーダー
* @author	Morita
* @date		2024/11/19
*/

#include "pch.h"

#include "GenerationWorld.h"

GenerationWorld::GenerationWorld()
	:
	m_time(0.0f),
	m_generationJudgement(false),
	m_deltaTime(0.0f)
{
}

GenerationWorld::~GenerationWorld()
{
}

void GenerationWorld::Initialize()
{
	//		ワールド生成シェーダー
	m_generationWorld = std::make_unique<ObjectShaderManager>();

	//		シェーダーの読み込み
	m_generationWorld->LoadShader(ObjectShaderManager::PixelShader,
		L"Resources/Shader/Model/GenerationWorld/GenerationWorldPS.cso");
	m_generationWorld->LoadShader(ObjectShaderManager::VertexShader,
		L"Resources/Shader/Model/GenerationWorld/GenerationWorldVS.cso");

	m_generationWorld->CreateConstBuffer(m_constBuffer);

	//m_generationWorld->LoadTexture(L"Resources/Texture/UI/Speed/Speed01.png");

	m_generationJudgement = true;
	m_generationJudgement = false;

	m_constBuffer.stop = 0.0f;
	m_constBuffer.time = 0.0f;
	m_constBuffer.stop = 1.0f;
}

void GenerationWorld::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 100.0f;

	m_deltaTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	if (m_time > 370.0f)
	{
		m_time = 370.0f;

		//m_generationJudgement = false;
		m_constBuffer.stop = 1.0f;
	}

	m_constBuffer.length = m_time;
	//m_constBuffer.time = m_deltaTime;
}

void GenerationWorld::Shader(ID3D11DeviceContext1* context)
{
	m_generationWorld->UpdateBuffer(m_constBuffer);

	m_generationWorld->SetShader(context);
}

void GenerationWorld::Finalize()
{
	m_generationWorld.reset();

	m_generationJudgement = false;
}
