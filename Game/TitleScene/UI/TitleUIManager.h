

#pragma once

#include "Library/Shader/UIRenderManager.h"

#include "Select/TitleSelectManager.h"

class TitleUIManager
{
public:

	//		コンストラクタ
	TitleUIManager(TitleSelectManager* titleSceneManager);

	//		デストラクタ
	~TitleUIManager();

	void Initialize();

	//		UIの情報を作成する
	void CreateUIInformation(DirectX::SimpleMath::Vector2 position,
							DirectX::SimpleMath::Vector2 size,
							TitleSelectManager::UIType type);

	void Update();

	void Render();

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;
		DirectX::SimpleMath::Vector2 scale;
	};

private:

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		タイトルシーンマネージャーのインスタンスのポインタ
	TitleSelectManager* m_titleSceneManager;

	//		シェーダーの情報
	std::unordered_map<TitleSelectManager::UIType, UIInformation> m_shaderInformation;

public:

	/*
	*	コンストバッファを受け取る
	* 
	*	@return	コンストバッファのポインタ
	*/
	ConstBuffer* GetConsutBuffer() { return &m_constBuffer; }
};