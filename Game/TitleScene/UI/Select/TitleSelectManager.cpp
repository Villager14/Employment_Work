/*
* @file		BackGroundMove.cpp
* @brief	�^�C�g���̑I���}�l�[�W���[
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
	//		Play�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		CENTER_POINT, { 1.0f, 1.0f });

	//		Play�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		UP_POINT, { 0.7f, 0.7f });

	//		Play�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		UNDER_POINT, { 0.7f, 0.7f });

	//		�I���v���C��Ԃ𐶐�����
	m_selectPlayState = std::make_unique<SelectPlayState>(this);

	//		�I���I����Ԃ𐶐�����
	m_selectEndState = std::make_unique<SelectEndState>(this);

	//		������Ԃ��Z�b�g����
	m_state = m_selectPlayState.get();

	//		����������
	m_state->Initialize();
}

void TitleSelectManager::Update()
{
	//		�X�V����
	m_state->Update();
}

void TitleSelectManager::Render()
{
	//		�`�揈��
	m_state->Render();

	for (int i = 0; i < m_uiRender.size(); ++i)
	{
		//		UI�̍��W��ݒ肷��
		m_uiRender[i]->SetPosition(m_uiPosition[i]);

		//		UI�̃T�C�Y��ݒ肷��
		m_uiRender[i]->SetSize(m_uiSize[i]);
	}

		//		UI�̕`��
	m_uiRender[1]->Render();
	m_uiRender[2]->Render();
	m_uiRender[0]->Render();

}

void TitleSelectManager::Finalize()
{
}

void TitleSelectManager::ChangeState(ITitleSelect* state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_state->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		�V������Ԃ̏���������������
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
	//		UI�����_�[�̐���
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UI�̍쐻
	uiRender->Create(path, position, size);

	m_uiPosition.push_back(position);

	m_uiSize.push_back(size);

	//		UI�̒ǉ�
	m_uiRender.push_back(std::move(uiRender));
}
