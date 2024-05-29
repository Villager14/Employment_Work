/*
* @file		BackGroundMove.cpp
* @brief	�^�C�g���̑I���}�l�[�W���[
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
	//		�}�E�X�̃t�H�[���`�����Z�b�g����
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		Play�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		CENTER_POINT, { MAX_SCALE, MAX_SCALE });

	//		Play�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		UP_POINT, { MIN_SCALE, MIN_SCALE });

	//		Play�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		UNDER_POINT, { MIN_SCALE, MIN_SCALE });

	//		TitleRogo�̕`��
	AddRenderUI(L"Resources/Texture/TitleScene/TitleRogo.png",
		{ 0.0f,-170.0f }, { MAX_SCALE, MAX_SCALE });

	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//		TVOff�̃G�t�F�N�g�̐���
	m_tvOffEffect = std::make_unique<TVOFEffec>();

	//		�G�t�F�N�g�̍쎌�G
	m_tvOffEffect->Create(L"Resources/Texture/TitleScene/Black.png",{0.0f, 0.0f}, {1.0f, 1.0f});

	//		�I���v���C��Ԃ𐶐�����
	m_selectPlayState = std::make_unique<SelectPlayState>(this);

	//		�I���I����Ԃ𐶐�����
	m_selectEndState = std::make_unique<SelectEndState>(this);

	//		�ݒ��Ԃ𐶐�����
	m_selectSettingState = std::make_unique<SelectSettingState>(this);

	//		�V�[���؂�ւ���Ԃ𐶐�����
	m_changeSceneState = std::make_unique<ChangeSceneState>(this);
	
	//		������Ԃ��Z�b�g����
	m_state = m_selectPlayState.get();

	//		����������
	m_state->Initialize();

	//		�`�揇��ݒ肷��
	for (int i = 0; i < 3; ++i)
	{
		m_drawOder.push_back(i);
	}
}

void TitleSelectManager::Update()
{
	//		�w�i�̍X�V����
	m_backGroundMove->Update();

	//		�X�V����
	m_state->Update();
}

void TitleSelectManager::Render()
{
	//		�w�i�̕`��
	m_backGroundMove->Render();
	
	//		�`�揈��
	m_state->Render();

	for (int i = 0; i < m_uiRender.size(); ++i)
	{
		//		UI�̍��W��ݒ肷��
		m_uiRender[i]->SetPosition(m_uiPosition[i]);

		//		UI�̃T�C�Y��ݒ肷��
		m_uiRender[i]->SetSize(m_uiSize[i]);
	}

	//		UI�̕`��(�I����)
	for (int i = 0; i < 3; ++i)
	{
		m_uiRender[m_drawOder[i]]->Render();
	}

	//		�^�C�g�����S�̕`��
	m_uiRender[UIType::TitleRogo]->Render();

	//m_tvOffEffect->Render(0.5f);

}

void TitleSelectManager::Finalize()
{
}

void TitleSelectManager::InputKey()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		W�{�^��OR�}�E�X�z�C�[����ŏ�Ɉړ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W)|| 
		m_scrollWheeel < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		�����ړ����������Ă���ꍇ�͏��������Ȃ�
		if (!m_inputKey)
		{
			m_inputKey = true;
			m_direction = true;
		}

		m_scrollWheeel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}

	//		S�{�^��OR�}�E�X�z�C�[�������ŉ��Ɉړ�
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S) ||
		m_scrollWheeel > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		�����ړ����������Ă���ꍇ�͏��������Ȃ�
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

	//		�`�揇���Ō�ɂ���
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

	//		�`�揇���Ō�ɂ���
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

	//		�`�揇���ŏ��ɂ���
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
	//		UI�����_�[�̐���
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UI�̍쐻
	uiRender->Create(path, position, size);

	m_uiPosition.push_back(position);

	m_uiSize.push_back(size);

	//		UI�̒ǉ�
	m_uiRender.push_back(std::move(uiRender));
}
