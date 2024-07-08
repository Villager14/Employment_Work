/*
* @file		ResultStay.cpp
* @brief	リザルト待機処理
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultStay.h"

ResultStay::ResultStay(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultStay::~ResultStay()
{
}

void ResultStay::Initialize()
{
}

void ResultStay::Update()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		状態を切り替える(数字移動状態)
		m_resultManager->ChangeState(ResultManager::State::End);
	}
}

void ResultStay::Render()
{
	//		評価
	m_resultManager->GetStandardShader()->Render(ResultManager::EvaluationUI);

	//		遷移誘導画像
	m_resultManager->GetStandardShader()->Render(ResultManager::Button);

	//		数字の描画
	m_resultManager->GetRiseNumberShader()->Render(4.0f);
}

void ResultStay::Finalize()
{
}
