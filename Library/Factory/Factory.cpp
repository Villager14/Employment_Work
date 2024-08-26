/*
* @file		Factory.cpp
* @brief	�t�@�N�g���[
* @author	Morita
* @date		2024/08/21
*/

#include "pch.h"

#include "Factory.h"

#include "IFactory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Game/PlayScene/ObjectManager/GrinderObject/GriderObject.h"

#include "Game/PlayScene/ObjectManager/WallObject/WallObject.h"

#include "Game/PlayScene/ObjectManager/GoalObject/GoalObject.h"

#include "Game/PlayScene/ObjectManager/FloorObject/FloorObject.h"

Factory::Factory(ObjectManager* objectManager)
{
	m_objectInformation[Object::Grider] = [objectManager] {return std::make_unique<GriderObject>(objectManager); };
	m_objectInformation[Object::Wall] = [objectManager] {return std::make_unique<WallObject>(objectManager); };
	m_objectInformation[Object::Goal] = [objectManager] {return std::make_unique<GoalObject>(objectManager); };
	m_objectInformation[Object::Floor] = [objectManager] {return std::make_unique<FloorObject>(objectManager); };
}

Factory::~Factory()
{
}

std::unique_ptr<IFactory> Factory::CreateObject(Object type, 
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Vector3 rotation)
{
	//		�I�u�W�F�N�g�^�C�v�����邩�ǂ���
	auto it = m_objectInformation.find(type);

	if (it != m_objectInformation.end())
	{
		std::unique_ptr<IFactory> factory = it->second();

		//		����������
		factory->Initialize(position, rotation);

		return factory;
	}

	return nullptr;
}
 