/*
* @file		ObjectManager.h
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "FloorObject/FloorObject.h"

#include "WireObject/WireObject.h"

#include "WallObject/WallObject.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

class ObjectManager
{
public:

	//		�R���X�g���N�^
	ObjectManager();

	//		�f�X�g���N�^
	~ObjectManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:
	//		�v���C���[�̍s��
	DirectX::SimpleMath::Matrix m_playerMatrix;

	//		���I�u�W�F�N�g
	std::unique_ptr<FloorObject> m_floorObject;

	//		���C���[�I�u�W�F�N�g
	std::unique_ptr<WireObject> m_wireObject;

	//		�I�u�W�F�N�g�̃��b�V��
	std::vector<ObjectMesh*> m_objectMesh;

	//		���b�V����`�悷��
	std::unique_ptr<DrawMesh> m_drawMesh;

	//		�ǃI�u�W�F�N�g�𐶐�����
	std::unique_ptr<WallObject> m_wallObject;

	//		���C���[�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

public:

	/*
	*	�v���C���[�̃��[���h�s����󂯎��
	* 
	*	@return �s��
	*/
	const DirectX::SimpleMath::Matrix& GetPlayerWorld() { return m_playerMatrix; }

	/*
	*	�v���C���[�̃��[���h�s���ݒ肷��
	* 
	*	@param	(position)	�v���C���[�̍s��
	*/
	void SetPlayerWorld(const DirectX::SimpleMath::Matrix& matrix) { m_playerMatrix = matrix; }

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	* 
	*	@return �I�u�W�F�N�g���b�V���̃C���X�^���X�̃|�C���^
	*/
	std::vector<ObjectMesh*> GetMesh() { return m_objectMesh; }

	/*
	*	���C���[�̍��W���󂯎��
	*
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWirePosition() { return m_wirePosition; }
};
