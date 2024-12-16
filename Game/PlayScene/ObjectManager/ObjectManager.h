/*
* @file		ObjectManager.h
* @brief	オブジェクトマネージャー
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "WireObject/WireObjectInformation.h"

#include "../GameManager/GameManager.h"

#include "Library/Factory/Factory.h"

#include "Library/Factory/IFactory.h"

#include "LoadingObjectInformation.h"

#include "ObjectInformation.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Effect/Model/GenerationWorld.h"

class BackGroundObject;

class ObjectManager
{
public:

	enum StageType
	{
		Title,
		Play,
	};

public:

	//		コンストラクタ
	ObjectManager();

	//		デストラクタ
	~ObjectManager();

	//		初期化処理
	void Initialize(StageType type);

	/*
	*	更新処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	描画処理
	* 
	*	@param	(cameraVelocity)	視線ベクトル
	*/
	void Render(DirectX::SimpleMath::Vector3 viewDirection,
				DirectX::SimpleMath::Vector3 cameraPosition,
				PostEffectFlag::Flag flag, PostEffectObjectShader* objectShader);

	//		終了処理
	void Finalize();

	/*
	*	オブジェクトの座標
	* 
	*	@param	(position)	オブジェクトの座標
	*	@return true カリングする false : カリングしない
	*/
	bool Culling(DirectX::SimpleMath::Vector3 position, float length);

	/*
	*	ワイヤーの情報オブジェクトを作成する
	* 
	*	@param	(index)			要素
	*	@param	(wireNumber)	ワイヤーの番号
	*/
	void CreateWireInformation(int index, int *wireNumber);

private:

	//		背景オブジェクト
	std::unique_ptr<BackGroundObject> m_backGroundObject;

	//		オブジェクトのメッシュ
	std::vector<ObjectMesh*> m_objectMesh;

	//		メッシュを描画する
	std::unique_ptr<DrawMesh> m_drawMesh;
	 
	//		カメラの座標
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//		ワイヤーオブジェクトの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wireObjectPosition;

	//		ワイヤーの情報
	std::vector<WireObjectInformation> m_wireInformation;

	//		ファクトリー
	std::unique_ptr<Factory> m_factory;

	//		ファクトリーオブジェクト
	std::vector<std::unique_ptr<IFactory>> m_factoryObject;

	//		ゲームマネージャー
	//GameManager* m_gameManager;

	//		オブジェクトの情報の読み込み
	std::unique_ptr<LoadingObjectInformation> m_loadObjectInformation;

	//		オブジェクトの情報
	std::vector<ObjectInformation> m_objectInformation;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		世界の生成シェーダー
	std::unique_ptr<GenerationWorld> m_generationWorld;

	//		カメラの視点
	DirectX::SimpleMath::Vector3 m_viewDirection;

public:


	/*
	*	プレイヤーの座標を受け取る
	* 
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector3 GetPlayerPosition() { return m_playerPosition; }

	/*
	*	オブジェクトメッシュを受け取る
	* 
	*	@return オブジェクトメッシュのインスタンスのポインタ
	*/
	std::vector<ObjectMesh*> GetMesh() { return m_objectMesh; }

	/*
	*	ワイヤーオブジェクトの情報を受け取る
	* 
	*	@return	ワイヤー情報
	*/
	std::vector<WireObjectInformation>* GetUseWireInformation() { return &m_wireInformation; }

	GenerationWorld* GetGenerationWorld() { return m_generationWorld.get(); }
};
