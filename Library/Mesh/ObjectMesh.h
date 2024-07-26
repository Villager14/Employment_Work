/*
* @file		LeadMesh.cpp
* @brief	メッシュの読み込み
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

	//		コンストラクタ
	ObjectMesh();

	//		デストラクタ
	~ObjectMesh();

	//		初期化処理
	void Initialize(const wchar_t* filePath);

	/*
	*	静的な処理を行う(静的なオブジェクトの場合のみ呼ぶ)
	* 
	*	@param	(world)	ワールド行列
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

	//		オブジェクトの種類
	ObjectType m_objectType;

	//		三角形情報
	std::vector<Triangle> m_triangle;

	//		メッシュ情報の読み込み
	std::unique_ptr<LeadMesh> m_leadMesh;

	//		静的オブジェクトかどうか
	bool m_staticObjectJudgement;

	//		オブジェクトメッシュ
	std::unordered_map<int, std::vector<Triangle>> m_objectMesh;

public:

	/*
	*	頂点を受け取る
	* 
	*	@param	(meshNumber)	メッシュの番号
	*	@param	(vertexNumber)	頂点の番号
	*/
	DirectX::SimpleMath::Vector3 GetVertexPosition
	(const int& meshNumber, const int& vertexNumber)
	{ return m_triangle[meshNumber].m_vertex[vertexNumber]; }

	/*
	*	法線を受け取る
	* 
	*	@param	(meshNumber)	メッシュの番号
	*/
	DirectX::SimpleMath::Vector3 GetNormalizePosition
	(const int& meshNumber) {
		return m_triangle[meshNumber].m_normalVector;}

	/*
	*	静的なオブジェクトかどうか
	* 
	*	@return true : 静的なオブジェクト false : 動的なオブジェクト
	*/
	bool GetStaticObjectJudgement() { return m_staticObjectJudgement; }

	/*
	*	メッシュの数を受け取る
	* 
	*	@return メッシュの数
	*/
	int GetVertexSize() { return static_cast<int>(m_triangle.size()); }

	/*
	*	オブジェクトのタイプを設定する
	* 
	*	@param	(type)	オブジェクトのタイプ
	*/
	void SetObuectType(ObjectType type) { m_objectType = type; }

	/*
	*	オブジェクトのタイプを受け取る
	* 
	*	@return オブジェクトのタイプ
	*/
	const ObjectType& GetObjectType() { return m_objectType; }

	//		オブジェクトメッシュ
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_objectMesh; }
};
