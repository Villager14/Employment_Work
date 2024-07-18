/*
* @file		FrameWalk.h
* @brief	枠の処理
* @author	Morita
* @date		2024/07/18
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include <unordered_map>

class FrameWalkUI
{
public:

	//		コンストラクタ
	FrameWalkUI();

	//		デストラクタ
	~FrameWalkUI();

	//		初期化処理
	void Initialize();
public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 time;					//		時間
	};

	enum FrameType
	{
		MenuClear,
		EXIT
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		座標
		float move = 0.0f;											//		変化時間
		float time = 0.0f;											//		時間
		bool boxhitJudgement = false;								//		ボックスの中にいるか		
	};

private:

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	float m_time;

	float m_move;

	std::unordered_map<FrameType, UIInformation> m_frameInformation;

public:

	/*
	*	描画処理
	*
	*	@param	(type)	描画するUIの種類
	*/
	void Render(float time, FrameType type);

	//		時間のリセット
	void TimeReset() { m_time = 0.0f; };

	//		フレームのタイプ
	void CreateFrameInformtion(FrameType type, DirectX::SimpleMath::Vector2 position);

	//		リセット
	void Reset();

	std::unordered_map<FrameType, UIInformation>* GetFrameInformation() { return &m_frameInformation; }
};