/*
* @file		FloorObject.h
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

class WallObject
{
public:

	//		�R���X�g���N�^
	WallObject();

	//		�f�X�g���N�^
	~WallObject();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	/*
	*	�`�揈��
	* 
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render(DrawMesh* drawMesh);

	//		�I������
	void Finalize();

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	DirectX::SimpleMath::Vector3 m_move;

public:

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return �C���X�^���X
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
