/*
* @file		BackGroundObject.cpp
* @brief	背景オブジェクト
* @author	Morita
* @date		2024/05/23
*/

class BackGroundObject
{
public:

	//		コンストラクタ
	BackGroundObject();

	//		デストラクタ
	~BackGroundObject();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画オブジェクト
	void Render();

	//		終了処理
	void Finalize();

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

public:

};
