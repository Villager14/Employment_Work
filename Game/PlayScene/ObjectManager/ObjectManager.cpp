/*
* @file		ObjectManager.cpp
* @brief	オブジェクトマネージャー
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager(ShadowInformation* shadowInformation, GameManager* gameManager)
	:
	m_shadowInformation(shadowInformation),
	m_gameManager(gameManager)
{
	//		メッシュの描画を生成する
	m_drawMesh = std::make_unique<DrawMesh>();

	//		背景オブジェクトの生成
	m_backGroundObject = std::make_unique<BackGroundObject>();

	//		ファクトリー
	m_factory = std::make_unique<Factory>(this);
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	m_wireObjectPosition.push_back({ 0.0f, 70.0f, 297.0f });

	for (int i = 0; i < m_wireObjectPosition.size(); ++i)
	{
		//		ワイヤーオブジェクトの生成
		m_wireObject.push_back(std::make_unique<WireObject>());

		//		ワイヤーオブジェクトの初期化
		m_wireObject[i]->Initialize(m_wireObjectPosition[i], i);

		//		ワイヤーの情報を設定する
		m_wireInformation.push_back(m_wireObject[i]->GetWireInformation());
	}

	//		グラインダーオブジェクト
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Grider, { -383.0f, 30.0f, 349.0f }, {0.0f, 0.0f, 0.0f}));
	//		壁オブジェクト
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Wall, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	//		床オブジェクト
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Floor, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	//		ゴールオブジェクト
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Goal, { -580.0f, 17.0f, 350.0f }, { 0.0f, 90.0f, 0.0f }));

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		グライダーのメッシュ
		if (m_factoryObject[i]->GetObjectType() == Factory::Grider)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(1));
		}

		//		壁のメッシュ 床メッシュ　ゴールオブジェクト
		if (m_factoryObject[i]->GetObjectType() == Factory::Wall ||
			m_factoryObject[i]->GetObjectType() == Factory::Goal ||
			m_factoryObject[i]->GetObjectType() == Factory::Floor)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
		}
	}

	//		背景オブジェクトの初期化
	m_backGroundObject->Initialize(m_objectMesh, m_wireObjectPosition);

}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	for (int i = 0; i < m_wireObject.size(); ++i)
	{
		//		カリングするかどうか
		if (!Culling(m_wireObject[i]->GetPosition()))
		{
			//		ワイヤーオブジェクトの更新処理
			m_wireObject[i]->Update(playerPosition);
		}
	}

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		更新処理
		m_factoryObject[i]->Update();
	}
}

void ObjectManager::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	m_cameraVelocity = cameraVelocity;
	m_cameraPosition = cameraPosition;

	m_backGroundObject->Render(cameraVelocity, cameraPosition);

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		描画処理
		m_factoryObject[i]->Render();
	}

	for (const auto& e : m_wireObject)
	{
		//		カリングするかどうか
		if (!Culling(e->GetPosition()))
		{
			//		ワイヤーオブジェクトの処理
			e->Render();
		}
	}
}

void ObjectManager::Finalize()
{
	m_objectMesh.clear();

	m_wireObject.clear();

	m_backGroundObject->Finalize();

	m_factoryObject.clear();
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
