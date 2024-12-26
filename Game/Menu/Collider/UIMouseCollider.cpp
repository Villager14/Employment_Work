/*
* @file		UIMouseCollider.cpp
* @brief	メニューのUIの当たり判定
* @author	Morita
* @date		2024/12/20
*/

#include "pch.h"

#include "UIMouseCollider.h"

UIMouseCollider::UIMouseCollider()
	:
	m_mousePositionX(0),
	m_mousePositionY(0)
{
	//		メニュー当たり判定オブザーバーの生成
	m_colliderObserver = std::make_unique<MenuColliderObserver>();
}

UIMouseCollider::~UIMouseCollider()
{
}

void UIMouseCollider::Finalize()
{
	m_mousePositionX = 0;
	m_mousePositionY = 0;
}

void UIMouseCollider::MousePositionX(int x)
{
	m_mousePositionX = x;
}

void UIMouseCollider::MousePositionY(int y)
{
	m_mousePositionY = y;
}

void UIMouseCollider::CollitionProcess(const std::vector<MenuColliderInformation>& information)
{
	for (int i = 0; i < information.size(); ++i)
	{
		if (information[i].type == UIType::Knob)
		{
			BoxColliderProcess(information[i], KNOB_LENGTH);
		}
		if (information[i].type == UIType::Tab)
		{
			BoxColliderProcess(information[i], TAB_LENGTH);
		}
		if (information[i].type == UIType::Button)
		{
			BoxColliderProcess(information[i], BUTTON_LENGTH);
		}
	}
}

void UIMouseCollider::BoxColliderProcess(MenuColliderInformation information,
										 DirectX::SimpleMath::Vector2 boxLength)
{
	//		現在の座標
	DirectX::SimpleMath::Vector2 nowPosition = *information.position;

	//		中心座標
	nowPosition += {  LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
		LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f };

	DirectX::SimpleMath::Vector2 max = nowPosition + boxLength;
	DirectX::SimpleMath::Vector2 min = nowPosition - boxLength;

	//		四角の当たり判定
	if (BoxCollider(min, max))
	{
		//		オブザーバーで知らせる
		m_colliderObserver->HitUIType(information.subType);
	}

}

bool UIMouseCollider::BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
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
