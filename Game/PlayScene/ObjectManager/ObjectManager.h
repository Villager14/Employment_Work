/*
* @file		ObjectManager.h
* @brief	オブジェクトマネージャー
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "FloorObject/FloorObject.h"

#include "WireObject/WireObject.h"

#include "WallObject/WallObject.h"

#include "GoalObject/GoalObject.h"

#include "BackGroundObject/BackGroundObject.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Game/PlayScene/Shadow/ShadowInformation.h"

class ObjectManager
{
public:

	//		コンストラクタ
	ObjectManager(ShadowInformation* shadowInformation);

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

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:
	//		プレイヤーの行列
	DirectX::SimpleMath::Matrix m_playerMatrix;

	//		床オブジェクト
	std::unique_ptr<FloorObject> m_floorObject;

	//		ワイヤーオブジェクト
	std::vector<std::unique_ptr<WireObject>> m_wireObject;

	//		ゴールオブジェクト
	std::unique_ptr<GoalObject> m_goalObject;

	//		背景オブジェクト
	std::unique_ptr<BackGroundObject> m_backGroundObject;

	//		オブジェクトのメッシュ
	std::vector<ObjectMesh*> m_objectMesh;

	//		メッシュを描画する
	std::unique_ptr<DrawMesh> m_drawMesh;

	//		壁オブジェクトを生成する
	std::unique_ptr<WallObject> m_wallObject;

	//		ワイヤーの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

	//		影情報
	ShadowInformation* m_shadowInformation;
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
};
