/*
* @file		GenerationWorld.h
* @brief	世界の生成オブジェクトシェーダー
* @author	Morita
* @date		2024/11/19
*/

#pragma once

#include "Library/Shader/ObjectShaderManager.h"

class GenerationWorld
{
public:

	GenerationWorld();

	~GenerationWorld();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	void Shader(ID3D11DeviceContext1* context);

	void Finalize();

public:

	struct ConstBuffer
	{
		float length = 0.0f;
		DirectX::SimpleMath::Vector3 pad;
		float stop = 0.0f;
		DirectX::SimpleMath::Vector3 pad2;
		float time = 0.0f;
		DirectX::SimpleMath::Vector3 pad3;
	};

private:

	//		コンストバッファ	
	ConstBuffer m_constBuffer;

	//		ワールド生成シェーダー
	std::unique_ptr<ObjectShaderManager> m_generationWorld;

	//		生成中かどうか
	bool m_generationJudgement;

	float m_time;

	float m_deltaTime;

public:

	/*
	*	ワールド生成シェーダー
	* 
	*	@return true :　生成中 false : 生成していない
	*/
	bool GetGenerationJdugement() { return m_generationJudgement; }

	ConstBuffer GetConstBuffer() { return m_constBuffer; }
};