/*
* @file		BackGroundObjectInformation.h
* @brief	背景オブジェクトの情報
* @author	Morita
* @date		2024/06/05
*/

#include "Library/Mesh/ObjectMesh.h"

class BackGroundObjectInformation
{
public:

	//		コンストラクタ
	BackGroundObjectInformation();

	//		デストラクタ
	~BackGroundObjectInformation();

	/*
	*	オブジェクトの座標の生成
	* 
	*	@param	(mesh)	オブジェクトのメッシュの情報のポインタ
	*/	
	void Create(std::vector<ObjectMesh*> mesh, 
		const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	/*
	*	メッシュの情報を使えるものかどうかチェックする
	*
	*	@param	(mesh)	オブジェクトのメッシュの情報のポインタ
	*/
	void MeshChackProcess(ObjectMesh* mesh);

	/*
	*	メッシュの法線の情報から判断する
	* 
	*	@param	(normalize)	メッシュの法線
	*	@return 個の法線を使うかどうか
	*/
	bool ChackNormalize(DirectX::SimpleMath::Vector3 normalize);
	
	/*
	*	メッシュの中心点を計算する
	* 
	*	@param	(mesh)	オブジェクトのメッシュの情報のポインタ
	*	@param	(index)	要素
	*	@return メッシュの中心座標
	*/
	DirectX::SimpleMath::Vector3 MeshCenter(ObjectMesh* mesh, int index);

	/*
	*	メッシュの中心から頂点の最大距離を求める
	* 
	*	@param	(mesh)				オブジェクトのメッシュの情報のポインタ
	*	@param	(index)				要素数
	*	@param	(centerPosition)	中心座標
	*/
	float MeshMaxSide(ObjectMesh* mesh, int index, DirectX::SimpleMath::Vector3 centerPosition);

	//		オブジェクトの座標を作成
	void CreateObjectPosition();

	/*
	*	ランダムなオブジェクトの座標の処理
	* 
	*	@param	(maxX)	Xの最大距離
	*	@praam	(minX)	Xの最小距離
	*	@param	(maxZ)	Zの最大距離
	*	@param	(minZ)	Zの最小距離
	*/
	void RandomObjectPosition(float maxX, float minX, float maxZ, float minZ);

	/*
	*	オブジェクトとメッシュの距離を計算する
	* 
	*	@param	(randomPosition)	オブジェクトの座標
	*/
	bool ObjectMeshLength(DirectX::SimpleMath::Vector3 randomPosition);

	//		オブジェクトの回転を設定する
	void ObjectCreateRotation();

	//		いらない情報を開放する
	void Clear();

private:
	
	//		建物が存在しない距離
	const float NOT_EXSIT_LENGTH = 50.0f;

	//		建物が存在する最大距離
	const float MAX_LENGTH = 300.0f;

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		メッシュの中心点
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;

	//		メッシュの距離
	std::vector<float> m_meshLength;

	//		オブジェクトの座標
	std::vector<DirectX::SimpleMath::Vector3> m_objectPosition;

	//		オブジェクトの回転
	std::vector<DirectX::SimpleMath::Vector3> m_objectRotation;

	//		オブジェクトのクオータニオン
	std::vector<DirectX::SimpleMath::Quaternion> m_objectQuaternion;

public:

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectPosition() { return m_objectPosition; }

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectRotation() { return m_objectRotation; }

	const std::vector<DirectX::SimpleMath::Quaternion>& GetObjectQuaternion() { return m_objectQuaternion; }
};
