/*
* @file		IFactory
* @brief	�t�@�N�g���[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/08/21
*/

#pragma once

#include "pch.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Factory.h"

class IFactory
{
public:
	//		����������
	virtual void Initialize(DirectX::SimpleMath::Vector3 position,
							DirectX::SimpleMath::Vector3 rotation) = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�`�揈��
	virtual void Render() = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�I�u�W�F�N�g�^�C�v
	virtual Factory::Object GetObjectType() = 0;

	//		�I�u�W�F�N�g���b�V�����󂯎��
	virtual ObjectMesh* GetObjectMesh(int index) = 0;

	//		�f�X�g���N�^
	virtual ~IFactory() = default;
};
