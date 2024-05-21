/*
* @file		LeadMesh.h
* @brief	メッシュの読み込み
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

	//		コンストラクタ
	LeadMesh();

	//		デストラクタ
	~LeadMesh();

	/*
	*	ファイルパス
	* 
	* 
	*/
	std::vector<std::unique_ptr<Triangle>> 
		Lead(const wchar_t* filePath);

	/*
	*	メッシュの三角形の作製
	* 
	*	@param	(vertex)		頂点
	*	@param	(vertexIndex)	頂点インデックス
	*/
	void CreateTrinangle(
		const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const std::vector<int> vertexIndex);

	//		法線の作製
	void CreateNormalize();

private:

	//		三角形情報
	std::vector<std::unique_ptr<Triangle>> m_triangle;
};
