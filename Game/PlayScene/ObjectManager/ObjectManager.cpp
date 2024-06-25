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

	m_wireObjectPosition.push_back({ 0.0f, 70.0f, 297.0f });
	m_wireObjectPosition.push_back({ -730.0f, 70.0f, 360.0f });
	m_wireObjectPosition.push_back({ -900.0f, 100.0f, 300.0f });
	m_wireObjectPosition.push_back({ -1050.0f, 130.0f, 330.0f });

	for (int i = 0; i < m_wireObjectPosition.size(); ++i)
	{
		//		ワイヤーオブジェクトの生成
		m_wireObject.push_back(std::make_unique<WireObject>());

		//		ワイヤーオブジェクトの初期化
		m_wireObject[i]->Initialize(m_wireObjectPosition[i]);
	}

	//		壁オブジェクトの生成
	m_wallObject = std::make_unique<WallObject>();

	//		壁オブジェクトの初期化
	m_wallObject->Initialize();

	//		ゴールオブジェクトの生成
	m_goalObject = std::make_unique<GoalObject>();

	//		ゴールオブジェクトの初期化処理
	m_goalObject->Initialize();

	//		オブジェクトメッシュを追加する
	m_objectMesh.push_back(m_floorObject->GetObjectMesh());
	m_objectMesh.push_back(m_wallObject->GetObjectMesh());
	m_objectMesh.push_back(m_goalObject->GetObjectMesh());

	//		背景オブジェクトの生成
	m_backGroundObject = std::make_unique<BackGroundObject>();

	//		背景オブジェクトの初期化
	m_backGroundObject->Initialize(m_objectMesh, m_wireObjectPosition);

	//		メッシュの描画を生成する
	m_drawMesh = std::make_unique<DrawMesh>();
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_wirePosition.clear();

	for (int i = 0; i < m_wireObject.size(); ++i)
	{
		//		カリングするかどうか
		if (!Culling(m_wireObject[i]->GetPosition()))
		{
			m_wireObject[i]->Update(playerPosition);

			if (m_wireObject[i]->GetWireAvailableJudgement())
			{
				m_wirePosition.push_back(m_wireObject[i]->GetPosition());
			}
		}
	}

	//m_backGroundObject->Update();
}

void ObjectManager::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	m_cameraVelocity = cameraVelocity;
	m_cameraPosition = cameraPosition;

	m_backGroundObject->Render(cameraVelocity, cameraPosition);

	//		床の描画処理
	m_floorObject->Render(m_drawMesh.get());

	//		壁の描画
	m_wallObject->Render(m_drawMesh.get());

	for (const auto& e : m_wireObject)
	{
		//		カリングするかどうか
		if (!Culling(e->GetPosition()))
		{
			//		ワイヤーオブジェクトの処理
			e->Render();
		}
	}

	m_goalObject->Render(m_drawMesh.get());
}

void ObjectManager::Finalize()
{
}

bool ObjectManager::Culling(DirectX::SimpleMath::Vector3 position)
{
	//		カリングの処理!!!!!
	
	//		距離が400以上の場合カリングする
	if ((position - m_cameraPosition).Length() >= 400.0f)
	{
		return true;
	}

	//		プレイヤーの方向を作成する
	DirectX::SimpleMath::Vector3 objectVelocity =  position - m_cameraPosition;

	//		法線が０より小さい場合カリングする
	if (m_cameraVelocity.Dot(objectVelocity) < 0.0f)
	{
		return true;
	}

	return false;
}
