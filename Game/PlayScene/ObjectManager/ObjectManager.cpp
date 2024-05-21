/*
* @file		ObjectManager.cpp
* @brief	オブジェクトマネージャー
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		床の生成
	m_floorObject = std::make_unique<FloorObject>();

	//		床の初期化処理
	m_floorObject->Initialize();

	//		ワイヤーオブジェクトの生成
	m_wireObject = std::make_unique<WireObject>();

	//		ワイヤーオブジェクトの初期化
	m_wireObject->Initialize();

	//		壁オブジェクトの生成
	m_wallObject = std::make_unique<WallObject>();

	//		壁オブジェクトの初期化
	m_wallObject->Initialize();

	//		オブジェクトメッシュを追加する
	m_objectMesh.push_back(m_floorObject->GetObjectMesh());

	m_objectMesh.push_back(m_wallObject->GetObjectMesh());

	//		メッシュの描画を生成する
	m_drawMesh = std::make_unique<DrawMesh>();
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_wirePosition.clear();

	m_wireObject->Update(playerPosition);

	if (m_wireObject->GetWireAvailableJudgement())
	{
		m_wirePosition.push_back(m_wireObject->GetPosition());
	}
}

void ObjectManager::Render()
{
	//		床の描画処理
	m_floorObject->Render(m_drawMesh.get());

	//		壁の描画
	m_wallObject->Render(m_drawMesh.get());

	//		ワイヤーオブジェクトの処理
	m_wireObject->Render(m_drawMesh.get());
}

void ObjectManager::Finalize()
{
}
