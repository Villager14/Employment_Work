/*
* @file		Factory.h
* @brief	ファクトリー
* @author	Morita
* @date		2024/08/21
*/

#pragma once

//#include "IFactory.h"

//#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include <unordered_map>

class IFactory;

class ObjectManager;

class Factory
{
public:
	Factory(ObjectManager* ObjectManager);

	~Factory();

public:

	enum Object
	{
		None,
		Grider,		//		破壊オブジェクト
		Wall,		//		壁オブジェクト
		Goal,		//		ゴールオブジェクト
		Floor,		//		床オブジェクト
	};

public:

	std::unique_ptr<IFactory> CreateObject(Object type,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 rotation);
	
private:

	//		オブジェクトマネージャー
	//ObjectManager* m_objectManager;

	//		オブジェクトの情報
	std::unordered_map<Object, std::function<std::unique_ptr<IFactory>()>> m_objectInformation;
};
