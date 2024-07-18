/*
* @file		MenuManager.cpp
* @brief	メニューのマネージャー
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

MenuManager::MenuManager()
	:
	m_state(),
	m_selectUI{},
	m_type{},
	m_rangeUI{ AboveUI::UIType::Empty },
	m_slideUIType{AboveUI::UIType::Empty},
	m_firstAudioMenuJudgement(true)
{
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{
	//		状態の生成
	m_menuStateInformation.insert({ Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ Audio, std::make_unique<AudioSetting>(this) });
	m_menuStateInformation.insert({ Option, std::make_unique<OptionSetting>(this) });
	m_menuStateInformation.insert({ GamePlay, std::make_unique<EndSetting>(this) });
	m_menuStateInformation.insert({ Close, std::make_unique<MenuClose>(this) });

	m_type = Start;

	//		初期の状態
	m_state = m_menuStateInformation[m_type].get();

	//		初期化処理
	m_state->Initialize();

	//		UIを作成する
	CreateUI();
}

void MenuManager::Update()
{
	//		メニューを使用することができるかどうか
	if (!m_information->GetMenuUseJudgement()) return;

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::Escape))
	{
		m_information->SetMenuJudgement(true);
	}

	//		メニューを使用するかどうか
	if (!m_information->GetMenuJudgement()) return;


	//		マウスのモードを変更するかどうか
	if (m_information->GetMouseModeJudgement())
	{
		//		マウスを相対位置にする
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);

		//		マウスのモードを変更できないようにする
		m_information->SetMouseModeJudgement(false);
	}

	//		更新処理
	m_state->Update();

	//		メニューモードを終了したとき
	if (!m_information->GetMenuJudgement())
	{
		//		マウスのモードを変更できるようにする
		m_information->SetMouseModeJudgement(true);
	}
}

void MenuManager::Render()
{
	//		メニューを使用しているかどうか
	if (!m_information->GetMenuJudgement()) return;

	//		描画処理
	m_state->Render();

	//		デバックフォント
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionX",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x), 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionY",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y), 0, 30);
	LibrarySingleton::GetInstance()->DebugFont(L"HitJudgement",
		BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX), 0, 60);
}

void MenuManager::Finalize()
{
}

void MenuManager::MenuBackRneder()
{
	//		背景の描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::BackGround);

	//		バー１の描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar1);

	//		バー２の描画
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar2);
}

bool MenuManager::BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
{
	DirectX::SimpleMath::Vector2 mousePosition;

	mousePosition.x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	mousePosition.y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	//		範囲内にマウスがあるかどうか
	if (min.x <= mousePosition.x && max.x >= mousePosition.x &&
		min.y <= mousePosition.y && max.y >= mousePosition.y)
	{
		//		範囲内
		return true;
	}

	//		範囲外
	return false;
}

void MenuManager::CreateUI()
{
	//		スタンダードシェーダーの生成
	m_standardShader = std::make_unique<StandardShader<MenuInformation::UIType>>();

	//		スタンダードシェーダーの初期化処理
	m_standardShader->Initialize();

	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, 13.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::Bar1);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, -13.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::Bar2);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png",
		{ 0.0f, 0.0f }, { 0.0f, 1.0f }, MenuInformation::UIType::BackGround);

	//		上昇UIの生成
	m_aboveUI = std::make_unique<AboveUI>();

	//		上昇UIの初期化
	m_aboveUI->Initialize();

	//		スライダーUIの生成
	m_slider = std::make_unique<Slider>();

	//		スライダーUIの初期化
	m_slider->Initialize();

	//		メニュー選択UIの生成
	m_menuSelect = std::make_unique<MenuSelect>();

	//		メニュー選択UIの初期化
	m_menuSelect->Initialize();

	//		フレームワークを生成する
	m_frameWalkUI = std::make_unique<FrameWalkUI>();

	//		フレームワークを生成する
	m_frameWalkUI->Initialize();

	//		メニューの情報を生成する
	m_information = std::make_unique<MenuInformation>();

	//		メニューの情報を初期化する
	m_information->Initialzie(m_standardShader.get(),
		m_aboveUI.get(), m_slider.get(), m_menuSelect.get(), m_frameWalkUI.get());

}

void MenuManager::RoughMenuViwe(float transitionTime)
{
	//		Opetionの描画
	m_information->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, transitionTime);

	//		GamePlayの描画
	m_information->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, transitionTime);

	//		Audioのタイトル描画
	m_information->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, transitionTime);
}

void MenuManager::MenuSelectView()
{
	//		選択していない場合描画処理をしない
	if (m_rangeUI != AboveUI::UIType::Empty)
		m_information->GetMenuSelect()->Render((*m_information->GetAboveUI()->GetInformation())[m_rangeUI].position);
}

void MenuManager::ChangState(MenuType type)
{
	//		同じタイプの場合処理をしない
	if (m_type == type) return;

	//		終了処理
	m_state->Finalize();

	//		タイプの更新
	m_type = type;

	//		状態の更新
	m_state = m_menuStateInformation[type].get();

	//		初期化処理
	m_state->Initialize();
}

bool MenuManager::MenuEscCloseProcess()
{
	//		ESCキーを押した場合
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()
		->IsKeyPressed(DirectX::Keyboard::Escape))
	{
		return true;
	}

	return false;
}

bool MenuManager::ButtonCollider(MenuType type)
{
	MenuType hitType = MenuType::Empty;

	//		範囲内にいるかどうかのフラグ
	bool hitJudgement = false;

	//		Audioの大まかボタン内にいるか？
	if (BoxCollider(m_information->AUDIO_TITLE_POSITION_MIN, m_information->AUDIO_TITLE_POSITION_MAX))
	{
		//		範囲内にいるUIをAudioにする
		m_rangeUI = AboveUI::AudioSelect;

		//		範囲内にいる
		hitJudgement = true;

		//		範囲にいるものが現在の状態でなければ処理をする
		if (MenuType::Audio != type)
			hitType = MenuType::Audio;
	}
	
	//		Optionの大まかなボタン内にいるか？
	if (BoxCollider(m_information->OPTION_TITLE_POSITION_MIN, m_information->OPTION_TITLE_POSITION_MAX))
	{
		//		範囲内にいるUIをOptionにする
		m_rangeUI = AboveUI::OptionSelect;

		//		範囲内にいる
		hitJudgement = true;

		//		範囲にいるものが現在の状態でなければ処理をする
		if (MenuType::Option != type)
			hitType = MenuType::Option;
	}
	
	//		Backの大まかなボタンの中にいるか？
	if (BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX))
	{
		//		範囲内にいるUIをGamePlayにする
		m_rangeUI = AboveUI::GamePlaySelect;

		//		範囲内にいる
		hitJudgement = true;

		//		範囲にいるものが現在の状態でなければ処理をする
		if (MenuType::GamePlay != type)
			hitType = MenuType::GamePlay;
	}

	//		範囲内にいない場合
	if (!hitJudgement)
	{
		//		選択していない状態にする
		m_rangeUI = AboveUI::Empty;
		
		//		時間のリセット
		m_information->GetMenuSelect()->TimeReset();
	}

	//		当たっていない場合これ以上処理をしない
	if (hitType == Empty) return false;

	//		範囲内でクリックした場合
	if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
		== DirectX::Mouse::ButtonStateTracker().PRESSED)
	{
		//		クリックした状態を代入する
		m_selectUI = hitType;

		return true;
	}

	return false;
}

bool MenuManager::Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
							bool* startJudgement, bool endJudgement, bool moveJudgement)
{
	//		開始状態の場合
	if (*startJudgement)
	{
		//		時間1の更新
		*transitionTime1 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		時間1が一定時間以上になったら他の時間も更新する
		if (*transitionTime1 > 0.3f)
		{
			//		時間2の更新
			*transitionTime2 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		時間2が一定時間以上3遷移フラグがオンの場合時間3の更新をする
			if (*transitionTime2 > 0.3f && moveJudgement)
			{
				//		時間3の更新
				*transitionTime3 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		1以上にならないようにする
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		//		3の更新をする場合
		if (moveJudgement)
		{
			//		3の更新が終わったら
			if (*transitionTime3 >= 1.0f)
			{
				//		開始状態を終了する
				*startJudgement = false;
			}
		}
		else
		{
			//		2の更新が終わったら
			if (*transitionTime2 >= 1.0f)
			{
				//		開始状態を終了する
				*startJudgement = false;
			}
		}

		return true;
	}

	//		終了状態の場合
	if (endJudgement)
	{
		//		時間1の更新
		*transitionTime1 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		時間1が一定時間以下になったら他の時間も更新する
		if (*transitionTime1 < 0.7f)
		{
			//		時間2の更新
			*transitionTime2 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		時間2が一定時間以下3遷移フラグがオンの場合時間3の更新をする
			if (*transitionTime2 < 0.7f && moveJudgement)
			{
				//		時間3の更新
				*transitionTime3 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		0以下にならないようにする
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		if (moveJudgement)
		{
			if (*transitionTime3 <= 0.0f)
			{
				//		シーンを切り替える
				ChangState(MenuType::Close);
			}
		}
		else
		{
			if (*transitionTime2 <= 0.0f)
			{
				//		シーンを切り替える
				ChangState(m_selectUI);
			}
		}

		return true;
	}

	return false;
}

void MenuManager::SlideProcess(AboveUI::UIType type)
{
	//		現在の座標
	DirectX::SimpleMath::Vector2 nowPosition = (*m_information->GetAboveUI()->GetInformation())[type].position;

	//		中心座標
	nowPosition += {  LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
					  LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f };

	DirectX::SimpleMath::Vector2 max = nowPosition + m_information->KNOB_LENGTH;
	DirectX::SimpleMath::Vector2 min = nowPosition - m_information->KNOB_LENGTH;

	if (BoxCollider(min, max))
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_slideUIType = type;
		}
	}
	
	if (m_slideUIType == type)
	{
		(*m_information->GetAboveUI()->GetInformation())[type].position.x = static_cast<float>
			(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x) - 640.0f;

		(*m_information->GetAboveUI()->GetInformation())[type].position.x = Library::Clamp
		((*m_information->GetAboveUI()->GetInformation())[type].position.x,
			559 - 640.0f, 1120 - 640.0f);


		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().RELEASED)
		{
			//		効果音の場合のみ離したとき効果音を鳴らす
			if (m_slideUIType == AboveUI::UIType::SoundEffectKnob)
				MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

			m_slideUIType = AboveUI::UIType::Empty;
		}
	}
}
