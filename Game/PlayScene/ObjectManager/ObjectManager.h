/*
* @file		ObjectManager.h
* @brief	オブジェクトマネージャー
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "WireObject/WireObject.h"

#include "BackGroundObject/BackGroundObject.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Game/PlayScene/Shadow/ShadowInformation.h"

#include "WireObject/WireObjectInformation.h"

#include "../GameManager/GameManager.h"

#include "Library/Factory/Factory.h"

#include "Library/Factory/IFactory.h"

class ObjectManager
{
public:

	//		コンストラクタ
	ObjectManager(ShadowInformation* shadowInformation,
		GameManager* gameManager);

	//		デストラクタ
	~ObjectManager();

	//		初期化処理
	void Initialize();

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
	void Render(DirectX::SimpleMath::Vector3 cameraVelocity, DirectX::SimpleMath::Vector3 cameraPosition);

	//		終了処理
	void Finalize();

	/*
	*	オブジェクトの座標
	* 
	*	@param	(position)	オブジェクトの座標
	*	@return true カリングする false : カリングしない
	*/
	bool Culling(DirectX::SimpleMath::Vector3 position);

private:
	//		プレイヤーの行列
	DirectX::SimpleMath::Matrix m_playerMatrix;

	//		ワイヤーオブジェクト
	std::vector<std::unique_ptr<WireObject>> m_wireObject;

	//		背景オブジェクト
	std::unique_ptr<BackGroundObject> m_backGroundObject;

	//		オブジェクトのメッシュ
	std::vector<ObjectMesh*> m_objectMesh;

	//		メッシュを描画する
	std::unique_ptr<DrawMesh> m_drawMesh;

	//		ワイヤーの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

	//		影情報
	ShadowInformation* m_shadowInformation;

	//		カメラ視線ベクトル
	DirectX::SimpleMath::Vector3 m_cameraVelocity;

	//		カメラの座標
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//		ワイヤーオブジェクトの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wireObjectPosition;

	//		ワイヤーの情報
	std::vector<WireObjectInformation*> m_wireInformation;

	//		ファクトリー
	std::unique_ptr<Factory> m_factory;

	std::vector<std::unique_ptr<IFactory>> m_factoryObject;

	GameManager* m_gameManager;

public:

	/*
	*	プレイヤーのワールド行列を受け取る
	* 
	*	@return 行列
	*/
	const DirectX::SimpleMath::Matrix& GetPlayerWorld() { return m_playerMatrix; }

	/*
	*	プレイヤーのワールド行列を設定する
	* 
	*	@param	(position)	プレイヤーの行列
	*/
	void SetPlayerWorld(const DirectX::SimpleMath::Matrix& matrix) { m_playerMatrix = matrix; }

	/*
	*	オブジェクトメッシュを受け取る
	* 
	*	@return オブジェクトメッシュのインスタンスのポインタ
	*/
	std::vector<ObjectMesh*> GetMesh() { return m_objectMesh; }

	/*
	*	ワイヤーの座標を受け取る
	*
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWirePosition() { return m_wirePosition; }

	/*
	*	ワイヤーオブジェクトの情報を受け取る
	* 
	*	@return	ワイヤー情報
	*/
	std::vector<WireObjectInformation*> GetUseWireInformation() { return m_wireInformation; }

	GameManager* GetGameManager() { return m_gameManager; }
};
