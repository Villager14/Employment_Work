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

	//		オブジェクトの読み込みクラスの生成
	m_loadObjectInformation = std::make_unique<LoadingObjectInformation>();
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		ステージの読み込み
	m_loadObjectInformation->Load(0);

	int wireNumber = 0;

	for (int i = 0, max = static_cast<int>
		(m_loadObjectInformation->GetObjectInformation().size());
		i < max; ++i)
	{
		//		ワイヤー情報オブジェクトの作製
		CreateWireInformation(i, &wireNumber);

		m_factoryObject.push_back(m_factory->CreateObject(
			Factory::Object(m_loadObjectInformation->GetObjectInformation()[i].objectType),
			m_loadObjectInformation->GetObjectInformation()[i]));

	}

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
	m_playerPosition = playerPosition;

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
}

void ObjectManager::Finalize()
{
	m_objectMesh.clear();

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

void ObjectManager::CreateWireInformation(int index, int *wireNumber)
{
	if (Factory::Object(m_loadObjectInformation->GetObjectInformation()[index].objectType)
		== Factory::Object::Wire)
	{
		WireObjectInformation information;

		//		番号
		information.number = *wireNumber;
		*wireNumber += 1;

		//		座標
		information.position =
			m_loadObjectInformation->GetObjectInformation()[index].position;


		m_wireInformation.push_back(information);
	}
}
