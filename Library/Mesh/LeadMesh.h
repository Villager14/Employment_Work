/*
* @file		LeadMesh.h
* @brief	���b�V���̓ǂݍ���
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include <vector>

#include "Triangle.h"

class LeadMesh
{
public:

	//		�R���X�g���N�^
	LeadMesh();

	//		�f�X�g���N�^
	~LeadMesh();

	/*
	*	�t�@�C���p�X
	*
	*
	*/
	std::vector<Triangle>
		Lead(const wchar_t* filePath);

	/*
	*	���b�V���̎O�p�`�̍쐻
	*
	*	@param	(vertex)		���_
	*	@param	(vertexIndex)	���_�C���f�b�N�X
	*/
	void CreateTrinangle(
		const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const std::vector<int> vertexIndex);

	//		�@���̍쐻
	void CreateNormalize();

	//		�I�u�W�F�N�g���Ƃ̏��ɂ���
	void ObjectInformation();

	bool Sort(int index);

	void AddCodNumber(int index);

	void AddObject();

	//		���_�C���f�b�N�X�̍폜
	void ClearVertexIndex();

	//		�I�u�W�F�N�g���b�V�����󂯎��
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_object; }

	//		���a���쐬����
	void CreateRadius();

	/*
	*	�I�u�W�F�N�g�̍ő�l
	* 
	*	@param	(max)	�ő�l�z��
	*	@return �ő�l
	*/
	DirectX::SimpleMath::Vector3 ObjectMax(std::vector<DirectX::SimpleMath::Vector3> max);

	/*
	*	���b�V���̒������󂯎��
	* 
	*	@return ����
	*/
	std::vector<float> GetMesnLength() { return m_meshLength; }

	/*
	*	���b�V���̒��S���󂯎��
	* 
	*	@return ���S
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return m_meshCenter; }

	/*
	*	�I�u�W�F�N�g�̍ŏ��l
	*
	*	@param	(min)	�ŏ��l�l�z��
	*	@return �ŏ��l
	*/
	DirectX::SimpleMath::Vector3 ObjectMin(std::vector<DirectX::SimpleMath::Vector3> min);

	void Objectlength(DirectX::SimpleMath::Vector3 max, DirectX::SimpleMath::Vector3 min);

private:

	//		�O�p�`���
	std::vector<Triangle> m_triangle;

	//		���b�V�����̃R�s�[
	std::vector<Triangle> m_copytriangle;

	//		�I�u�W�F�N�g
	std::unordered_map<int, std::vector<Triangle>> m_object;

	//		�R�[�h�̔ԍ�
	std::vector<int> codNumber;

	//		���b�V���̒���
	std::vector<float> m_meshLength;

	//		���b�V���̒��S
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;
};