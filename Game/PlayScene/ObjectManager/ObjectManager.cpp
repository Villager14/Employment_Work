/*
* @file		ObjectManager.cpp
* @brief	オブジェクトマネージャー
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager(ShadowInformation* shadowInformation)
	:
	m_shadowInformation(shadowInformation)
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		床の生成
	m_floorObject = std::make_unique<FloorObject>(m_shadowInformation);

	//		床の初期化処理
	m_floorObject->Initialize();

	for (int i = 0; i < 2; ++i)
	{
		//		ワイヤーオブジェクトの生成
		m_wireObject.push_back(std::make_unique<WireObject>());
	}

	//		ワイヤーオブジェクトの初期化
	m_wireObject[0]->Initialize({ -100.0f, 70.0f, 467.0f });
	m_wireObject[1]->Initialize({ -200.0f, 100.0f, 850.0f });

	//		壁オブジェクトの生成
	m_wallObject = std::make_unique<WallObject>();

	//		壁オブジェクトの初期化
	m_wallObject->Initialize();

	//		ゴールオブジェクトの生成
	m_goalObject = std::make_unique<GoalObject>();

	//		ゴールオブジェクトの初期化処理
	m_goalObject->Initialize();

	//		背景オブジェクトの生成
	m_backGroundObject = std::make_unique<BackGroundObject>();

	//		背景オブジェクトの初期化
	m_backGroundObject->Initialize();

	//		オブジェクトメッシュを追加する
	m_objectMesh.push_back(m_floorObject->GetObjectMesh());
	m_objectMesh.push_back(m_wallObject->GetObjectMesh());
	m_objectMesh.push_back(m_goalObject->GetObjectMesh());

	//		メッシュの描画を生成する
	m_drawMesh = std::make_unique<DrawMesh>();
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_wirePosition.clear();

	for (int i = 0; i < m_wireObject.size(); ++i)
	{
		m_wireObject[i]->Update(playerPosition);

		if (m_wireObject[i]->GetWireAvailableJudgement())
		{
			m_wirePosition.push_back(m_wireObject[i]->GetPosition());
		}
	}

	//m_backGroundObject->Update();
}

void ObjectManager::Render()
{
	m_backGroundObject->Render();

	//		床の描画処理
	m_floorObject->Render(m_drawMesh.get());

	//		壁の描画
	m_wallObject->Render(m_drawMesh.get());

	for (const auto& e : m_wireObject)
	{
		//		ワイヤーオブジェクトの処理
		e->Render(m_drawMesh.get());
	}

	m_goalObject->Render(m_drawMesh.get());
}

void ObjectManager::Finalize()
{
}
