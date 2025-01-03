/*
* @file		FrameWalk.cpp
* @brief	枠の処理
* @author	Morita
* @date		2024/07/18
*/

#include "pch.h"

#include "FrameWalkUI.h"

FrameWalkUI::FrameWalkUI()
	:
	m_time(0.0f),
	m_move(0.0f)
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(MENU_FRAMEWAORK_TEXTURE_PATH,
		MENU_FRAMEWAORK_VS_PATH,MENU_FRAMEWAORK_GS_PATH,
		MENU_FRAMEWAORK_PS_PATH, m_constBuffer,
		MENU_FRAME_WORK_POSITION, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);
}

FrameWalkUI::~FrameWalkUI()
{
}

void FrameWalkUI::Initialize()
{
	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	CreateFrameInformtion(FrameType::MenuClear, MENU_FRAME_WORK_POSITION);
	CreateFrameInformtion(FrameType::EXIT, EXIT_POSITION);
}

void FrameWalkUI::Update(FrameType type)
{
	//		ボックスに当たっているか
	if (m_frameInformation[type].boxhitJudgement)
	{
		//		当たっている場合枠を広げる
		m_frameInformation[type].move += LibrarySingleton::GetInstance()->GetElpsedTime() * FRAME_SPEED;
	}
	else
	{
		//		当たっていない場合枠を狭める
		m_frameInformation[type].move -= LibrarySingleton::GetInstance()->GetElpsedTime() * FRAME_SPEED;
	}

	//		時間が1以上０以下にならないようにする
	m_frameInformation[type].move = Library::Clamp(m_frameInformation[type].move, 0.0f, 1.0f);

	//		イージング関数
	m_frameInformation[type].time = 1.0f - pow(1.0f - m_frameInformation[type].move, 4.0f);
}

void FrameWalkUI::Render(float moveTime, FrameType type)
{
	//		シェーダーの座標を設定する
	m_shader->SetPosition(m_frameInformation[type].position);

	//		コンストバッファに時間の値を渡す
	m_constBuffer.time = { moveTime, m_frameInformation[type].time, 0.0f, 0.0f };

	//		描画
	m_shader->Render(m_constBuffer);
}

void FrameWalkUI::CreateFrameInformtion(FrameType type, DirectX::SimpleMath::Vector2 position)
{
	UIInformation infor;
	infor.position = position;

	m_frameInformation.insert({ type, infor });
}

void FrameWalkUI::Reset()
{
	for (auto e : m_frameInformation)
	{
		e.second.boxhitJudgement = false;
		e.second.time = 0.0f;
		e.second.move = 0.0f;
	}
}
