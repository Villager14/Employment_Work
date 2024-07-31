/*
* @file		LeadMesh.h
* @brief	メッシュの読み込み
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

	//		コンストラクタ
	LeadMesh();

	//		デストラクタ
	~LeadMesh();

	/*
	*	ファイルパス
	*
	*
	*/
	std::vector<Triangle>
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

	//		オブジェクトごとの情報にする
	void ObjectInformation();

	bool Sort(int index);

	void AddCodNumber(int index);

	void AddObject();

	//		頂点インデックスの削除
	void ClearVertexIndex();

	//		オブジェクトメッシュを受け取る
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_object; }

	//		半径を作成する
	void CreateRadius();

	/*
	*	オブジェクトの最大値
	* 
	*	@param	(max)	最大値配列
	*	@return 最大値
	*/
	DirectX::SimpleMath::Vector3 ObjectMax(std::vector<DirectX::SimpleMath::Vector3> max);

	/*
	*	メッシュの長さを受け取る
	* 
	*	@return 長さ
	*/
	std::vector<float> GetMesnLength() { return m_meshLength; }

	/*
	*	メッシュの中心を受け取る
	* 
	*	@return 中心
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return m_meshCenter; }

	/*
	*	オブジェクトの最小値
	*
	*	@param	(min)	最小値値配列
	*	@return 最小値
	*/
	DirectX::SimpleMath::Vector3 ObjectMin(std::vector<DirectX::SimpleMath::Vector3> min);

	void Objectlength(DirectX::SimpleMath::Vector3 max, DirectX::SimpleMath::Vector3 min);

private:

	//		三角形情報
	std::vector<Triangle> m_triangle;

	//		メッシュ情報のコピー
	std::vector<Triangle> m_copytriangle;

	//		オブジェクト
	std::unordered_map<int, std::vector<Triangle>> m_object;

	//		コードの番号
	std::vector<int> codNumber;

	//		メッシュの長さ
	std::vector<float> m_meshLength;

	//		メッシュの中心
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;
};