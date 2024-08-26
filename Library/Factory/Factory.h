/*
* @file		Factory.h
* @brief	�t�@�N�g���[
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
		Grider,		//		�j��I�u�W�F�N�g
		Wall,		//		�ǃI�u�W�F�N�g
		Goal,		//		�S�[���I�u�W�F�N�g
		Floor,		//		���I�u�W�F�N�g
	};

public:

	std::unique_ptr<IFactory> CreateObject(Object type,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 rotation);
	
private:

	//		�I�u�W�F�N�g�}�l�[�W���[
	//ObjectManager* m_objectManager;

	//		�I�u�W�F�N�g�̏��
	std::unordered_map<Object, std::function<std::unique_ptr<IFactory>()>> m_objectInformation;
};
