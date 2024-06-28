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
		m_resultManager->ChangeState(m_resultManager->GetResultEnd());
	}
}

void ResultStay::Render()
{
	//		UI背景の描画
	m_resultManager->UIViewProcess(1);

	//		ボタン
	m_resultManager->UIViewProcess(2);

	//		数字の描画
	m_resultManager->NumberRender(4.0f);
}

void ResultStay::Finalize()
{
}
