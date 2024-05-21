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
	std::vector<std::unique_ptr<Triangle>> 
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

private:

	//		�O�p�`���
	std::vector<std::unique_ptr<Triangle>> m_triangle;
};
