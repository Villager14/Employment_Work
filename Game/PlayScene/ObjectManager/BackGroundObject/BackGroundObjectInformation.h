/*
* @file		BackGroundObjectInformation.h
* @brief	�w�i�I�u�W�F�N�g�̏��
* @author	Morita
* @date		2024/06/05
*/

#include "Library/Mesh/ObjectMesh.h"

class BackGroundObjectInformation
{
public:

	//		�R���X�g���N�^
	BackGroundObjectInformation();

	//		�f�X�g���N�^
	~BackGroundObjectInformation();

	/*
	*	�I�u�W�F�N�g�̍��W�̐���
	* 
	*	@param	(mesh)	�I�u�W�F�N�g�̃��b�V���̏��̃|�C���^
	*/	
	void Create(std::vector<ObjectMesh*> mesh, 
		const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	/*
	*	���b�V���̏����g������̂��ǂ����`�F�b�N����
	*
	*	@param	(mesh)	�I�u�W�F�N�g�̃��b�V���̏��̃|�C���^
	*/
	void MeshChackProcess(ObjectMesh* mesh);

	/*
	*	���b�V���̖@���̏�񂩂画�f����
	* 
	*	@param	(normalize)	���b�V���̖@��
	*	@return �̖@�����g�����ǂ���
	*/
	bool ChackNormalize(DirectX::SimpleMath::Vector3 normalize);
	
	/*
	*	���b�V���̒��S�_���v�Z����
	* 
	*	@param	(mesh)	�I�u�W�F�N�g�̃��b�V���̏��̃|�C���^
	*	@param	(index)	�v�f
	*	@return ���b�V���̒��S���W
	*/
	DirectX::SimpleMath::Vector3 MeshCenter(ObjectMesh* mesh, int index);

	/*
	*	���b�V���̒��S���璸�_�̍ő勗�������߂�
	* 
	*	@param	(mesh)				�I�u�W�F�N�g�̃��b�V���̏��̃|�C���^
	*	@param	(index)				�v�f��
	*	@param	(centerPosition)	���S���W
	*/
	float MeshMaxSide(ObjectMesh* mesh, int index, DirectX::SimpleMath::Vector3 centerPosition);

	//		�I�u�W�F�N�g�̍��W���쐬
	void CreateObjectPosition();

	/*
	*	�����_���ȃI�u�W�F�N�g�̍��W�̏���
	* 
	*	@param	(maxX)	X�̍ő勗��
	*	@praam	(minX)	X�̍ŏ�����
	*	@param	(maxZ)	Z�̍ő勗��
	*	@param	(minZ)	Z�̍ŏ�����
	*/
	void RandomObjectPosition(float maxX, float minX, float maxZ, float minZ);

	/*
	*	�I�u�W�F�N�g�ƃ��b�V���̋������v�Z����
	* 
	*	@param	(randomPosition)	�I�u�W�F�N�g�̍��W
	*/
	bool ObjectMeshLength(DirectX::SimpleMath::Vector3 randomPosition);

	//		�I�u�W�F�N�g�̉�]��ݒ肷��
	void ObjectCreateRotation();

	//		����Ȃ������J������
	void Clear();

private:
	
	//		���������݂��Ȃ�����
	const float NOT_EXSIT_LENGTH = 50.0f;

	//		���������݂���ő勗��
	const float MAX_LENGTH = 300.0f;

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		���b�V���̒��S�_
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;

	//		���b�V���̋���
	std::vector<float> m_meshLength;

	//		�I�u�W�F�N�g�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_objectPosition;

	//		�I�u�W�F�N�g�̉�]
	std::vector<DirectX::SimpleMath::Vector3> m_objectRotation;

	//		�I�u�W�F�N�g�̃N�I�[�^�j�I��
	std::vector<DirectX::SimpleMath::Quaternion> m_objectQuaternion;

public:

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectPosition() { return m_objectPosition; }

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectRotation() { return m_objectRotation; }

	const std::vector<DirectX::SimpleMath::Quaternion>& GetObjectQuaternion() { return m_objectQuaternion; }
};
