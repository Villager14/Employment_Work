/*
* @file		LeadMesh.h
* @brief	���b�V���̓ǂݍ���
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include <vector>

class Triangle;

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

	//		�I�u�W�F�N�g���b�V�����󂯎��
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_object; }

private:

	//		�O�p�`���
	std::vector<Triangle> m_triangle;

	std::vector<Triangle> m_copytriangle;

	std::unordered_map<int, std::vector<Triangle>> m_object;

	std::vector<int> codNumber;

};