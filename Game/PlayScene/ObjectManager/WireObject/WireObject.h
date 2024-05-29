/*
* @file		FloorObject.h
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

class WireObject
{
public:

	//		�R���X�g���N�^
	WireObject();

	//		�f�X�g���N�^
	~WireObject();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�`�揈��
	* 
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render(DrawMesh* drawMesh);

	//		�I������
	void Finalize();

private:

	//		���C���[���f��
	std::unique_ptr<DirectX::Model> m_wireModel;

	//		���C���[�͈̔̓��f��
	std::unique_ptr<DirectX::Model> m_wireRangeModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		�H�I�u�W�F�N�g
	std::unique_ptr<DirectX::Model> m_wingModel;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		�f�o�b�N�p�̃��[���h���W
	DirectX::SimpleMath::Matrix m_debugWorld;

	//		���C���[���g���邩�ǂ���
	bool m_wireAvailableJudgement;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;

	//		�͈�
	float m_range;

	//		��]
	float m_rotation;

	//		�H�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wingPosition;

public:

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return �C���X�^���X
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }

	/*
	*	���C���[�I�u�W�F�N�g���g�p�\���H
	* 
	*	@return �g�p�\�� true : �g�p�\ false : �g�p�s�\
	*/
	bool GetWireAvailableJudgement() { return m_wireAvailableJudgement; }

	/*
	*	���W���󂯎��
	* 
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

};
