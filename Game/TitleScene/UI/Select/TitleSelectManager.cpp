/*
* @file		BackGroundMove.cpp
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

TitleSelectManager::TitleSelectManager()
{
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		Playの描画
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		CENTER_POINT, { 1.0f, 1.0f });

	//		Playの描画
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		UP_POINT, { 0.7f, 0.7f });

	//		Playの描画
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		UNDER_POINT, { 0.7f, 0.7f });

	//		選択プレイ状態を生成する
	m_selectPlayState = std::make_unique<SelectPlayState>(this);

	//		選択終了状態を生成する
	m_selectEndState = std::make_unique<SelectEndState>(this);

	//		初期状態をセットする
	m_state = m_selectPlayState.get();

	//		初期化する
	m_state->Initialize();
}

void TitleSelectManager::Update()
{
	//		更新処理
	m_state->Update();
}

void TitleSelectManager::Render()
{
	//		描画処理
	m_state->Render();

	for (int i = 0; i < m_uiRender.size(); ++i)
	{
		//		UIの座標を設定する
		m_uiRender[i]->SetPosition(m_uiPosition[i]);

		//		UIのサイズを設定する
		m_uiRender[i]->SetSize(m_uiSize[i]);
	}

		//		UIの描画
	m_uiRender[1]->Render();
	m_uiRender[2]->Render();
	m_uiRender[0]->Render();

}

void TitleSelectManager::Finalize()
{
}

void TitleSelectManager::ChangeState(ITitleSelect* state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_state->Finalize();

	//		状態を切り替える
	m_state = state;

	//		新しい状態の初期化処理をする
	m_state->Initialize();
}

void TitleSelectManager::CentreUP(bool direction, float time, UIType type)
{
	float move = 0.0f;
	float size = 0.0f;

	DirectX::SimpleMath::Vector2 firstPosition;
	DirectX::SimpleMath::Vector2 endPosition;

	float firstSize = 0.0f;
	float endSize = 0.0f;

	if (direction)
	{
		firstPosition = { 0.0f,120.0f };
		endPosition = { 0.0f, 40.0f };

		move = sqrt(1 - pow(time - 1, 2));
		size = 1 - sqrt(1 - pow(time, 2));
		firstSize = 1.0f;
		endSize = 0.7f;
	}
	else
	{
		firstPosition = { 0.0f,40.0f };
		endPosition = { 0.0f, 120.0f };

		move = 1 - sqrt(1 - pow(time, 2));
		size = sqrt(1 - pow(time - 1, 2));
		firstSize = 0.7f;
		endSize = 1.0f;
	}

	m_uiPosition[type] = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	m_uiSize[type] = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::CenterUnder(bool direction, float time, UIType type)
{
	float move = 0.0f;
	float size = 0.0f;

	DirectX::SimpleMath::Vector2 firstPosition;
	DirectX::SimpleMath::Vector2 endPosition;

	float firstSize = 0.0f;
	float endSize = 0.0f;

	if (direction)
	{
		firstPosition = UNDER_POINT;
		endPosition = CENTER_POINT;

		move = 1 - sqrt(1 - pow(time, 2));
		size = sqrt(1 - pow(time - 1, 2));
		firstSize = 0.7f;
		endSize = 1.0f;
	}
	else
	{
		firstPosition = CENTER_POINT;
		endPosition = UNDER_POINT;

		move = sqrt(1 - pow(time - 1, 2));
		size = 1 - sqrt(1 - pow(time, 2));
		firstSize = 1.0f;
		endSize = 0.7f;
	}

	m_uiPosition[type] = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	m_uiSize[type] = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::UPUnder(bool direction, float time, UIType type)
{
	float move = 0.0f;
	float size = 0.0f;

	DirectX::SimpleMath::Vector2 firstPosition;
	DirectX::SimpleMath::Vector2 endPosition;

	float firstSize = 0.65;
	float endSize = 0.7f;

	if (direction)
	{
		firstPosition = UP_POINT;
		endPosition = UNDER_POINT;
	}
	else
	{
		firstPosition = UNDER_POINT;
		endPosition = UP_POINT;
	}

	move = time * time * time;

	float radian = Library::Lerp(0.0f, 360.0f, move);

	
	size = (cosf(DirectX::XMConvertToRadians(radian)) / 2.0f + 0.5f);

	size = Library::Clamp(size, 0.0f, 1.0f);

	m_uiPosition[type] = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	m_uiSize[type] = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::AddRenderUI(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 size)
{
	//		UIレンダーの生成
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UIの作製
	uiRender->Create(path, position, size);

	m_uiPosition.push_back(position);

	m_uiSize.push_back(size);

	//		UIの追加
	m_uiRender.push_back(std::move(uiRender));
}
