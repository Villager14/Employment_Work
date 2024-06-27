/*
* @file		GoalObject.h
* @brief	ゴールオブジェクトの描画
* @author	Morita
* @date		2024/05/27
*/
#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

class GoalObject
{
public:

	//		コンストラクタ
	GoalObject();

	//		デストラクタ
	~GoalObject();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	/*
	*	描画処理
	* 
	*	@param	(drawMesh)	メッシュ描画のインスタンスのポインタ
	*/
	void Render(DrawMesh* drawMesh);

	//		終了処理
	void Finalize();

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_floorPS;

	// テクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

	//		回転量
	float m_rotation;

public:

	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return インスタンス
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
