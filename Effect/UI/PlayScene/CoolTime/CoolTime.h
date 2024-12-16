/*
* @file		CoolTime.h
* @brief	クールタイム
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Library/Shader/UIRenderManager.h"

#include "../UIManager.h"

class CoolTime
{
public:

	//		コンストラクタ
	CoolTime(UIManager* uiManager);

	//		デストラクタ
	~CoolTime();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	*	
	*	プレイヤーの情報を受けとる
	*/
	void Update(float coolTime);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		数字の描画
	void NumberView();

private:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		アスペクト比
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 number;			//		数字
	};

	//		コンストバッファ回転
	struct ConstBufferCircle
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 rotation;
	};


private:

	//		数字の中心の座標
	const float NUMBER_CENTER_POSITION = 1179.0f;

	//		数字の間隔
	const float NUMBER_INTERVAL = 30.0f;

	//		クールタイムの座標
	const DirectX::SimpleMath::Vector2 COOL_TIME_POSITION = { 270.0f, 0.0f };

	//		最大角度
	const float MAX_ANGLE = 360.0f;
	
	//		レート
	const float RATO = 100.0f;

	//		ダッシュの速度
	const float DASH_SPEED = 2.0f;

	//		クールタイムの速度
	const float COOL_TIME_SPEED = 0.67f;

	//		クールタイムテクスチャパス
	const wchar_t* COOL_TIME_TEXTURE_PATH = L"Resources/Texture/UI/CoolTime/CoolTime.png";

	//		クールタイムVSパス
	const wchar_t* COOL_TIME_VS_PATH = L"Resources/Shader/UI/CoolTime/CoolTimeVS.cso";

	//		クールタイムGSパス
	const wchar_t* COOL_TIME_GS_PATH = L"Resources/Shader/UI/CoolTime/CoolTimeGS.cso";

	//		クールタイムPSパス
	const wchar_t* COOL_TIME_PS_PATH = L"Resources/Shader/UI/CoolTime/CoolTimePS.cso";

	//		クールタイムテクスチャパス
	const wchar_t* COOL_TIME_NUMBER_TEXTURE_PATH = L"Resources/Texture/UI/CoolTime/cooltimeNumber.png";

	//		番号VSパス
	const wchar_t* NUMBER_VS_PATH = L"Resources/Shader/UI/Number/NumberVS.cso";

	//		番号GSパス
	const wchar_t* NUMBER_GS_PATH = L"Resources/Shader/UI/Number/NumberGS.cso";

	//		番号PSパス
	const wchar_t* NUMBER_PS_PATH = L"Resources/Shader/UI/Number/NumberPS.cso";

private:

	//		UIマネージャのインスタンスのポインタ
	UIManager* m_uiManager;

	//		角度
	float m_angle;

	//		時間
	float m_time;

	//		パーセント
	float m_ratio;

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_coolTimeNumberShader;

	//		回転シェーダー
	std::unique_ptr<UIRenderManager> m_coolTImeShader;

	//		コンストバッファ
	ConstBuffer buffer;

	//		回転コンストバッファ
	ConstBufferCircle circleBuffer;
};
