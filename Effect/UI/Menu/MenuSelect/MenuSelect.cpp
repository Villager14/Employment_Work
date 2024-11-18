/*
* @file		MenuSelect.h
* @brief	メニューの選択処理
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "MenuSelect.h"

MenuSelect::MenuSelect()
	:
	m_time(0.0f)
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(SELECT_TEXTURE,
		SELECT_MENU_VS_TEXTURE,
		SELECT_MENU_GS_TEXTURE,
		SELECT_MENU_PS_TEXTURE,
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);
}

MenuSelect::~MenuSelect()
{
}

void MenuSelect::Initialize()
{
	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void MenuSelect::Render(DirectX::SimpleMath::Vector2 position)
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		コンストバッファの更新
	m_constBuffer.time = { m_time, 0.0f, 0.0f, 0.0f };

	//		座補を設定する
	m_shader->SetPosition(position);

	//		描画
	m_shader->Render(m_constBuffer);
}
