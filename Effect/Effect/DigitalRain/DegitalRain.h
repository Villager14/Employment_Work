/*
* @file		DegitalRain.h
* @brief	デジタル雨マネージャー
* @author	Morita
* @date		2024/10/14
*/

#pragma once

#include "Library/Shader/EffectShaderManager.h"

#include "DegitalRainParameter.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class DegitalRain
{
public:

	DegitalRain();

	~DegitalRain();

	//		初期化処理
	void Initialzie();

	//		更新処理
	void Update();

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	int BinaryDigits(int number);

	//		ソート処理
	void Sort();

	//		数字の生成
	void CreateNumber(int index);

	//		クールタイム
	void CoolTime();

	/*
	*	生成座標１
	* 
	*/
	void GenerationPosition(int index);

	//		ビルボードの作製
	void Billbord(DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up, int index);

	//		終了処理
	void Finalize();

private:

	struct  ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
		int number = 0;
		DirectX::SimpleMath::Vector3 pad;
		float length = 0;
		DirectX::SimpleMath::Vector3 pad2;
	};

public:

	const float MAX_LENGTH = 50.0f;

	const float MIN_LENGTH = 40.0f;

	//		テクスチャパス
	const wchar_t* TEST_TEXTURE_PATH = L"Resources/Texture/TEST.png";

	//		テクスチャパス２
	const wchar_t* TEST2_TEXTURE_PATH = L"Resources/Texture/TEST2.png";

	//		デジタル雨VSパス
	const wchar_t* DEGITAL_RAIN_VS_PATH = L"Resources/Shader/Effect/DegitalRain/DegitalRainVS.cso";

	//		デジタル雨GSパス
	const wchar_t* DEGITAL_RAIN_GS_PATH = L"Resources/Shader/Effect/DegitalRain/DegitalRainGS.cso";

	//		デジタル雨PSパス
	const wchar_t* DEGITAL_RAIN_PS_PATH = L"Resources/Shader/Effect/DegitalRain/DegitalRainPS.cso";

private:

	ConstBuffer m_constBuffer;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

	//		カメラの視点ベクトル
	DirectX::SimpleMath::Vector3 m_cameraViewVelocity;

	//		カメラのEye
	DirectX::SimpleMath::Vector3 m_cameraEye;

	//		カメラのアップ
	DirectX::SimpleMath::Vector3 m_cameraUp;

	//		エフェクトマネージャー
	//EffectManager* m_effectManager;

	//		エフェクトシェーダーマネージャー
	std::unique_ptr<EffectShaderManager<ConstBuffer>> m_effectShaderManager;

	//		パラメーター
	std::vector<DegitalRainParameter> m_parameta;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	float m_time;

public:

	/*
	*	カメラのビューベクトルを設定する
	* 
	*	@param	(velocity)	ベクトル
	*/
	void SetCameraViewVelocity(DirectX::SimpleMath::Vector3 velocity) { m_cameraViewVelocity = velocity; }

	/*
	*	カメラのEyeを設定する
	* 
	*	@param	(eye)	Eye
	*/
	void SetCameraEye(DirectX::SimpleMath::Vector3 eye) { m_cameraEye = eye; }

	/*
	*	カメラのUpを設定する
	* 
	*	@param	(up)	Up
	*/
	void SetCameraUp(DirectX::SimpleMath::Vector3 up) { m_cameraUp = up; }
};