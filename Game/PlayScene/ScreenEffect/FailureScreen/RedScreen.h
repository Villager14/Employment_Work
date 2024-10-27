/*
* @file		RedScreen.h
* @brief	赤い画面化
* @author	Morita
* @date		2024/05/22
*/

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/Menu/MenuInformation.h"

class RedScreen
{
public:
	//		コンストバッファ
	struct  ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
		DirectX::SimpleMath::Matrix		rotationMatrix;
		DirectX::SimpleMath::Vector4	time;
		DirectX::SimpleMath::Vector4	motionVector;
		DirectX::SimpleMath::Vector4	blurStrength;
		DirectX::SimpleMath::Vector4    concentrationLineTime;
		DirectX::SimpleMath::Vector4    grayStrength;
	};
public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//		コンストラクタ
	RedScreen();

	//		デストラクタ
	~RedScreen();

	/*
	*	作成
	*
	*	@param	(position)	座標
	*	@param	(scale)		スケール
	*/
	void Create(
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale);

	/*
	*	更新処理
	*
	*	@param	(timer)	DX::StepTimer
	*/
	void Update(GameManager* gameManager, PlayerCameraInformation* playerCameraInformation);


	//		グレイプロセス
	void Gray(MenuInformation* menuInformation);

	/*
	*	描画処理
	*
	*	@param (shaderResouceView)	テクスチャ情報
	*/
	void Render(ID3D11ShaderResourceView* shaderResouceView);

	/*
	*	スケールを設定する
	*
	*	@param	(scale) スケール
	*/
	void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; };

	/*
	*	スケールを受け取る
	*
	*	@return スケール
	*/
	DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }

	/*
	*	ベースのスケールを受け取る
	*
	*	@return ベーススケール
	*/
	DirectX::SimpleMath::Vector2 GetBaseScale() { return m_baseScale; }

	/*
	*	座標を設定する
	*
	*	@param	(position)
	*/
	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	/*
	*	座標を受け取る
	*
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

	/*
	*	回転行列を受け取る
	*
	*	@param	(rotatonMatrix)	回転行列
	*/
	void SetRotationMatrix(DirectX::SimpleMath::Matrix rotatonMatrix) { m_rotationMatrix = rotatonMatrix; }

	/*
	*	グレイにするかどうか設定する
	*
	*	@param	(judgement)	true : グレイにする false : グレイにしない
	*/
	void SetGrayJudgement(bool judgement) { m_grayJudgement = judgement; }

	/*
	*	テクスチャの読み込み
	*
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path);

private:

	void CreateShader();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;

	//		入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		ジオメトリックシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometoryShaer;

	//		ジオメトリックシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometoryRotationShaer;

	//		スケール
	DirectX::SimpleMath::Vector2 m_scale;

	//		初期スケール
	DirectX::SimpleMath::Vector2 m_baseScale;

	//		座標
	DirectX::SimpleMath::Vector2 m_position;

	//		回転行列
	DirectX::SimpleMath::Matrix m_rotationMatrix;

	//		時間
	float m_time;

	//		グレイにするかどうか
	bool m_grayJudgement;

	//		移動方向
	DirectX::SimpleMath::Vector2 m_cameraMove;

	//		ブラの強さ
	float m_blerString;

	//		集中線の時間
	float concentrationLineTime;

	//		集中線のクールタイム
	float concentrationCoolTime;

	//		集中線の変化率
	float concentrationChange;

	//		メニューの時間
	float m_menuTime;

	//		メニューが開いているかどうか判断する
	bool m_menuOpenJudgement;
};