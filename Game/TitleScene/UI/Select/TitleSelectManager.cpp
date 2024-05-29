/*
* @file		BackGroundMove.cpp
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

TitleSelectManager::TitleSelectManager()
	:
	m_inputKey(false),
	m_direction(false),
	m_scrollWheeel(0),
	m_changeSceneJudgement(false)
{
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		マウスのフォールチをリセットする
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		Playの描画
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		CENTER_POINT, { MAX_SCALE, MAX_SCALE });

	//		Playの描画
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		UP_POINT, { MIN_SCALE, MIN_SCALE });

	//		Playの描画
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		UNDER_POINT, { MIN_SCALE, MIN_SCALE });

	//		TitleRogoの描画
	AddRenderUI(L"Resources/Texture/TitleScene/TitleRogo.png",
		{ 0.0f,-170.0f }, { MAX_SCALE, MAX_SCALE });

	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		背景の初期化
	m_backGroundMove->Initialize();

	//		TVOffのエフェクトの生成
	m_tvOffEffect = std::make_unique<TVOFEffec>();

	//		エフェクトの作詞絵
	m_tvOffEffect->Create(L"Resources/Texture/TitleScene/Black.png",{0.0f, 0.0f}, {1.0f, 1.0f});

	//		選択プレイ状態を生成する
	m_selectPlayState = std::make_unique<SelectPlayState>(this);

	//		選択終了状態を生成する
	m_selectEndState = std::make_unique<SelectEndState>(this);

	//		設定状態を生成する
	m_selectSettingState = std::make_unique<SelectSettingState>(this);

	//		シーン切り替え状態を生成する
	m_changeSceneState = std::make_unique<ChangeSceneState>(this);
	
	//		初期状態をセットする
	m_state = m_selectPlayState.get();

	//		初期化する
	m_state->Initialize();

	//		描画順を設定する
	for (int i = 0; i < 3; ++i)
	{
		m_drawOder.push_back(i);
	}
}

void TitleSelectManager::Update()
{
	//		背景の更新処理
	m_backGroundMove->Update();

	//		更新処理
	m_state->Update();
}

void TitleSelectManager::Render()
{
	//		背景の描画
	m_backGroundMove->Render();
	
	//		描画処理
	m_state->Render();

	for (int i = 0; i < m_uiRender.size(); ++i)
	{
		//		UIの座標を設定する
		m_uiRender[i]->SetPosition(m_uiPosition[i]);

		//		UIのサイズを設定する
		m_uiRender[i]->SetSize(m_uiSize[i]);
	}

	//		UIの描画(選択肢)
	for (int i = 0; i < 3; ++i)
	{
		m_uiRender[m_drawOder[i]]->Render();
	}

	//		タイトルロゴの描画
	m_uiRender[UIType::TitleRogo]->Render();

	//m_tvOffEffect->Render(0.5f);

}

void TitleSelectManager::Finalize()
{
}

void TitleSelectManager::InputKey()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		WボタンORマウスホイール上で上に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W)|| 
		m_scrollWheeel < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_inputKey)
		{
			m_inputKey = true;
			m_direction = true;
		}

		m_scrollWheeel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}

	//		SボタンORマウスホイールしたで下に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S) ||
		m_scrollWheeel > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_inputKey)
		{
			m_inputKey = true;
			m_direction = false;
		}

		m_scrollWheeel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}
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

	//		描画順を最後にする
	m_drawOder[2] = type;

	if (direction)
	{
		firstPosition = { 0.0f,120.0f };
		endPosition = { 0.0f, 40.0f };

		move = sqrt(1 - pow(time - 1, 2));
		size = 1 - sqrt(1 - pow(time, 2));
		firstSize = MAX_SCALE;
		endSize = MIN_SCALE;
	}
	else
	{
		firstPosition = { 0.0f,40.0f };
		endPosition = { 0.0f, 120.0f };

		move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
		size = sqrt(1.0f - pow(time - 1.0f, 2.0f));
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

	//		描画順を最後にする
	m_drawOder[1] = type;

	if (direction)
	{
		firstPosition = UNDER_POINT;
		endPosition = CENTER_POINT;

		move = 1 - sqrt(1 - pow(time, 2));
		size = sqrt(1 - pow(time - 1, 2));
		firstSize = MIN_SCALE;
		endSize = MAX_SCALE;
	}
	else
	{
		firstPosition = CENTER_POINT;
		endPosition = UNDER_POINT;

		move = sqrt(1 - pow(time - 1, 2));
		size = 1 - sqrt(1 - pow(time, 2));
		firstSize = MAX_SCALE;
		endSize = MIN_SCALE;
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

	float firstSize = MIN_SCALE - 0.5f;
	float endSize = MIN_SCALE;

	//		描画順を最初にする
	m_drawOder[0] = type;

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
