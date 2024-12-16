/*
* @file		TitleCameraManager.h
* @brief	タイトルカメラマネージャー
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "ITitleCamera.h"

#include "../Observer/FadeObserver/FadeObserver.h"

class TitleCameraManager
{
public:

	//		コンストラクタ
	TitleCameraManager();

	//		デストラクタ
	~TitleCameraManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		終了処理
	void Finalize();

	/*
	*	ビューの作製
	* 
	*	@param	(position)	座標
	*	@param	(target)	視点のターゲット
	*/
	void CreateView(DirectX::SimpleMath::Vector3 position,
					DirectX::SimpleMath::Vector3 target);

	/*
	*	フェードアウトを行うか
	* 
	*	@param	(time)	時間
	*/
	void FadeOut(float time) { if (time > FADE_START_TIME && !m_fadeOutUseJudgement) 
	{ 
		m_fadeObserver->FadeOut();
		m_fadeOutUseJudgement = true;
	} }

private:

	//		プロジェの作製
	void CreateProj();

public:

	enum CameraType
	{
		Non,
		Front,
		FrontAscending,
		OverHead,
		Back,

	};

public:
	/*
	*	状態の遷移
	* 
	*	@param	(changeState)	状態の遷移
	*/
	void ChangeState(CameraType changeState);

private:

	//		フェード開始時間
	const float FADE_START_TIME = 0.95f;

private:

	//		カメラの情報
	std::unordered_map<CameraType, std::unique_ptr<ITitleCamera>> m_cameraInformation;

	//		カメラのタイプ
	CameraType m_cameraType;

	//		カメラの状態
	ITitleCamera* m_state;

	//		フェードオブザーバー
	std::unique_ptr<FadeObserver> m_fadeObserver;

	//		フェードアウトを行ったかどうか
	bool m_fadeOutUseJudgement;

public:

	/*
	*	フェードオブザーバーを追加する
	*
	*	@param	(observer)	オブザーバーのポインタ
	*/
	void AddFadeObserver(IFadeObserver* observer) { m_fadeObserver->AddObserver(observer); };
};