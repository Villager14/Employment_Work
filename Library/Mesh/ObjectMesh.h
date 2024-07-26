/*
* @file		LeadMesh.cpp
* @brief	���b�V���̓ǂݍ���
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include <vector>

#include "Triangle.h"

#include "Library/Mesh/LeadMesh.h"

class ObjectMesh
{
public:

	//		�R���X�g���N�^
	ObjectMesh();

	//		�f�X�g���N�^
	~ObjectMesh();

	//		����������
	void Initialize(const wchar_t* filePath);

	/*
	*	�ÓI�ȏ������s��(�ÓI�ȃI�u�W�F�N�g�̏ꍇ�̂݌Ă�)
	* 
	*	@param	(world)	���[���h�s��
	*/
	void StaticProcess(const DirectX::SimpleMath::Matrix& world,
					  const DirectX::SimpleMath::Vector3& move);



public:

	enum class ObjectType
	{
		Floor,
		Wall,
		Goal,
	};

private:

	//		�I�u�W�F�N�g�̎��
	ObjectType m_objectType;

	//		�O�p�`���
	std::vector<Triangle> m_triangle;

	//		���b�V�����̓ǂݍ���
	std::unique_ptr<LeadMesh> m_leadMesh;

	//		�ÓI�I�u�W�F�N�g���ǂ���
	bool m_staticObjectJudgement;

	//		�I�u�W�F�N�g���b�V��
	std::unordered_map<int, std::vector<Triangle>> m_objectMesh;

public:

	/*
	*	���_���󂯎��
	* 
	*	@param	(meshNumber)	���b�V���̔ԍ�
	*	@param	(vertexNumber)	���_�̔ԍ�
	*/
	DirectX::SimpleMath::Vector3 GetVertexPosition
	(const int& meshNumber, const int& vertexNumber)
	{ return m_triangle[meshNumber].m_vertex[vertexNumber]; }

	/*
	*	�@�����󂯎��
	* 
	*	@param	(meshNumber)	���b�V���̔ԍ�
	*/
	DirectX::SimpleMath::Vector3 GetNormalizePosition
	(const int& meshNumber) {
		return m_triangle[meshNumber].m_normalVector;}

	/*
	*	�ÓI�ȃI�u�W�F�N�g���ǂ���
	* 
	*	@return true : �ÓI�ȃI�u�W�F�N�g false : ���I�ȃI�u�W�F�N�g
	*/
	bool GetStaticObjectJudgement() { return m_staticObjectJudgement; }

	/*
	*	���b�V���̐����󂯎��
	* 
	*	@return ���b�V���̐�
	*/
	int GetVertexSize() { return static_cast<int>(m_triangle.size()); }

	/*
	*	�I�u�W�F�N�g�̃^�C�v��ݒ肷��
	* 
	*	@param	(type)	�I�u�W�F�N�g�̃^�C�v
	*/
	void SetObuectType(ObjectType type) { m_objectType = type; }

	/*
	*	�I�u�W�F�N�g�̃^�C�v���󂯎��
	* 
	*	@return �I�u�W�F�N�g�̃^�C�v
	*/
	const ObjectType& GetObjectType() { return m_objectType; }

	//		�I�u�W�F�N�g���b�V��
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_objectMesh; }
};
