/*
* @file		MoveObject.h
* @brief	移動オブジェクトの描画
* @author	Morita
* @date		2024/11/13
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class MoveObject : public IFactory
{
public:

	//		コンストラクタ
	MoveObject(ObjectManager* objectManager);

	//		デストラクタ
	~MoveObject();

	/*
	*	初期化処理
	*
	*	@param	(position)	座標
	*/
	void Initialize(ObjectInformation information) override;

	//		更新処理
	void Update() override;

	/*
	*	描画処理
	* 
	*	@param	(drawMesh)	メッシュ描画のインスタンスのポインタ
	*/
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader) override;

	//		終了処理
	void Finalize() override;

	/*
	*	オブジェクトタイプを受け取る
	*
	*	@return　オブジェクトタイプ
	*/
	Factory::Object GetObjectType() override { return Factory::Move; }


	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return メッシュの情報
	*/
	ObjectMesh* GetObjectMesh(int index) override { 
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get(); }

	/*
	*	ポストエフェクトフラグ
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{ return m_postEffectFlag.get(); }

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// テクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	ObjectManager* m_objectManager;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_firstPosition;
	DirectX::SimpleMath::Vector3 m_secondPosition;

	DirectX::SimpleMath::Vector3 m_rotation;

	//		時間
	float m_time;

	float m_speed;

public:

	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return インスタンス
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
