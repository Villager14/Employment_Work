/*
* @file		BackGroundObject.cpp
* @brief	背景オブジェクト
* @author	Morita
* @date		2024/05/23
*/

#include "BackGroundObjectInformation.h"

#include "Library/Mesh/ObjectMesh.h"

class BackGroundObject
{
public:

	//		コンストラクタ
	BackGroundObject();

	//		デストラクタ
	~BackGroundObject();

	//		初期化処理
	void Initialize(std::vector<ObjectMesh*> mesh,
		const std::vector<DirectX::SimpleMath::Vector3>& m_wirePosition);

	//		更新処理
	void Update();

	//		描画オブジェクト
	void Render(DirectX::SimpleMath::Vector3 cameraVelocity,
				DirectX::SimpleMath::Vector3 cameraPosition);

	//		終了処理
	void Finalize();

	/*
	*	カリングの処理
	* 
	*	@param	(index)	要素数
	*	@return true : 描画する false : 描画しない
	*/
	bool Culling(int index, DirectX::SimpleMath::Vector3 cameraVelocity,
		DirectX::SimpleMath::Vector3 cameraPosition);

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		情報
	std::unique_ptr<BackGroundObjectInformation> m_information;


public:

};
