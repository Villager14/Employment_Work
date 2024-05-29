/*
* @file		ChangeSceneState.cpp
* @brief	ƒV[ƒ“Ø‚è‘Ö‚¦‚ð‚µ‚½ó‘Ô
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "ChangeSceneState.h"

ChangeSceneState::ChangeSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
}

void ChangeSceneState::Update()
{
}

void ChangeSceneState::Render()
{
}

void ChangeSceneState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}
