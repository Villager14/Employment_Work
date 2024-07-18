/*
* @file		AboveUI.h
* @brief	UIの上昇処理
* @author	Morita
* @date		2024/07/09
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class AboveUI
{
public:

	//		コンストラクタ
	AboveUI();

	//		デストラクタ
	~AboveUI();

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

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		座標
		DirectX::SimpleMath::Vector2 scale;							//		サイズ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;	//		テクスチャ
		DirectX::SimpleMath::Vector2 textureSize;					//		テクスチャサイズ
		float time = 0.0f;											//		時間
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER;
	};

	enum UIType
	{
		AudioSelect,
		OptionSelect,
		GamePlaySelect,
		Slide,
		AudioTitle,
		OptionTitle,
		GamePlayTitle,
		SliderBack,
		MastarVolume,
		BGMVolume,
		SoundEffectVolume,
		MasterKnob,
		BGMKnob,
		SoundEffectKnob,
		MenuClose,
		Exit,
		FOV,
		FOVKnob,
		Mouse,
		MouseKnob,

		Empty,
	};

private:

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		シェーダーの情報
	std::unordered_map<UIType, UIInformation> m_shaderInformation;


public:

	/*
	*	UIの情報を作成する
	*
	*	@param	(path)		テクスチャのパス
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*	@param	(type)		UIの種類
	*/
	void CreateUIInformation(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		UIType type,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	/*
	*	描画処理
	*
	*	@param	(type)	描画するUIの種類
	*/
	void Render(UIType type, float time);

	std::unordered_map<UIType, UIInformation>* GetInformation() { return &m_shaderInformation; }
};