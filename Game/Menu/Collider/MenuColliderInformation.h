/*
* @file		MenuColliderInformation.h
* @brief	���j���[�̓����蔻��̏��
* @author	Morita
* @date		2024/12/20
*/

#pragma once

#include "pch.h"

enum UIType
{
	None,
	Knob,
	Tab,
	Button,
};

enum UISubType
{
	Non,
	TabAudio,
	TabOption,
	TabGamePlay,
	GameExitButton,
	CloseMenuButton,
	MastarVolumKnob,
	SoundEffectKnob,
	BGMKnob,
	FovKnob,
	MouseSpeedKnob,
};

struct MenuColliderInformation
{
	UIType type = UIType::None;
	UISubType subType = UISubType::Non;
	DirectX::SimpleMath::Vector2 *position;
};