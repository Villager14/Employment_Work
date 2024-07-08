/*
* @file		BackGroundMove.cpp
* @brief	�^�C�g���̑I���}�l�[�W���[
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleSelectManager::TitleSelectManager()
	:
	m_inputKey(false),
	m_direction(false),
	m_scrollWheeel(0),
	m_changeSceneJudgement(false),
	m_iState(),
	m_menuJudgement(false),
	m_state{}
{
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		�}�E�X�̃t�H�[���`�����Z�b�g����
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//		��Ԃ̏���ݒ肷��
	m_stateInformation.insert({ State::PlayState, std::make_unique<SelectPlayState>(this) });
	m_stateInformation.insert({ State::EndState, std::make_unique<SelectEndState>(this) });
	m_stateInformation.insert({ State::SettingState, std::make_unique<SelectSettingState>(this) });
	m_stateInformation.insert({ State::StartState, std::make_unique<StartSceneState>(this) });
	m_stateInformation.insert({ State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		�����̏��
	m_state = State::StartState;

	//		�����̏��
	m_iState = m_stateInformation[m_state].get();

	//		����������
	m_iState->Initialize();

	//		�t�F�[�h�̐���
	m_fade = std::make_unique<FadeRender>();

	//		UI�`��̍쐻
	m_fade->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�`�揇��ݒ肷��
	m_drawOder.push_back(TitleUIType::Play);
	m_drawOder.push_back(TitleUIType::Setting);
	m_drawOder.push_back(TitleUIType::End);

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	CreateStandardShader();
}

void TitleSelectManager::Update()
{
	//		�w�i�̍X�V����
	m_backGroundMove->Update();

	//		���j���[���J���Ă���ꍇ�͏��������Ȃ�
	if (m_menuJudgement) return;

	//		�X�V����
	m_iState->Update();
}

void TitleSelectManager::Render()
{
	//		�w�i�̕`��
	m_backGroundMove->Render();

	//		���j���[���J���Ă���ꍇ�͏��������Ȃ�
	if (m_menuJudgement) return;

	//		�I���̕`��
	for (int i = 0, max = static_cast<int>(m_drawOder.size()); i < max; ++i)
	{
		//		�I��UI�̕`��
		m_standardShader->Render(m_drawOder[i]);
	}

	//		�^�C�g�����S�̕`��
	m_standardShader->Render(TitleUIType::TitleRogo);

	//		�`�揈��
	m_iState->Render();

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

			//		�I�����ʉ�
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
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

			//		�I�����ʉ�
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		//		�z�C�[���̒l���X�V����
		m_scrollWheeel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}
}

void TitleSelectManager::CreateStandardShader()
{
	//		�^�C�g��UI�}�l�[�W���[�̐���
	m_standardShader = std::make_unique<StandardShader<TitleUIType>>();

	//		�^�C�g��UI�}�l�[�W���̏�����
	m_standardShader->Initialize();

	//		�^�C�g�����S�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		{ 0.0f, -170.0f }, { MAX_SCALE,
		MAX_SCALE },
		TitleSelectManager::TitleUIType::TitleRogo);

	//		Play�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		CENTER_POINT, { MAX_SCALE,
		MAX_SCALE },
		TitleSelectManager::TitleUIType::Play);

	//		End�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		UP_POINT, { MIN_SCALE,
		MIN_SCALE },
		TitleSelectManager::TitleUIType::End);

	//		Setting�̐���
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		UNDER_POINT, { MIN_SCALE,
		MIN_SCALE },
		TitleSelectManager::TitleUIType::Setting);


}

void TitleSelectManager::ChangeState(State state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_iState->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		��Ԃ�؂�ւ���
	m_iState = m_stateInformation[m_state].get();

	//		�V������Ԃ̏���������������
	m_iState->Initialize();
}

void TitleSelectManager::CentreUP(bool direction, float time, TitleUIType type)
{
	//		�J�ڗ�
	float move = 0.0f;
	//		�J�ڗ�
	float size = 0.0f;

	//		�������W
	DirectX::SimpleMath::Vector2 firstPosition;
	//		�ŏI���W
	DirectX::SimpleMath::Vector2 endPosition;

	//		�����T�C�Y
	float firstSize = 0.0f;
	//		�ŏI�T�C�Y
	float endSize = 0.0f;

	//		�`�揇���Ō�ɂ���
	m_drawOder[2] = type;

	//		�ړ����������ď�����ς���
	if (direction)
	{
		firstPosition = CENTER_POINT;
		endPosition = UP_POINT;

		//		�ړ��̑J�ڗ�
		move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
		//		�T�C�Y�̑J�ڗ�
		size = 1.0f - sqrt(1 - pow(time, 2.0f));

		//		�����T�C�Y��ݒ�
		firstSize = MAX_SCALE;
		//		�ŏI�T�C�Y��ݒ�
		endSize = MIN_SCALE;
	}
	else
	{
		firstPosition = UP_POINT;
		endPosition = CENTER_POINT;

		//		�ړ��̑J�ڗ�
		move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
		//		�T�C�Y�̑J�ڗ�
		size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

		//		�����T�C�Y��ݒ�
		firstSize = MIN_SCALE;
		//		�ŏI�T�C�Y��ݒ�
		endSize = MAX_SCALE;
	}

	//		���W��ݒ肷��
	(*m_standardShader->GetUIInformation())[type].position = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	//		�T�C�Y��ݒ肷��
	(*m_standardShader->GetUIInformation())[type].scale = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::CenterUnder(bool direction, float time, TitleUIType type)
{
	//		�J�ڗ�
	float move = 0.0f;
	//		�J�ڗ�
	float size = 0.0f;

	//		�������W
	DirectX::SimpleMath::Vector2 firstPosition;
	//		�ŏI���W
	DirectX::SimpleMath::Vector2 endPosition;

	//		�����T�C�Y
	float firstSize = 0.0f;
	//		�ŏI�T�C�Y
	float endSize = 0.0f;

	//		�`�揇�𒆊Ԃɂ���
	m_drawOder[1] = type;

	//		�ړ����������ď�����ς���
	if (direction)
	{
		firstPosition = UNDER_POINT;
		endPosition = CENTER_POINT;

		//		�ړ��̑J�ڗ�
		move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
		//		�T�C�Y�̑J�ڗ�
		size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

		//		�����T�C�Y��ݒ�
		firstSize = MIN_SCALE;
		//		�ŏI�T�C�Y��ݒ�
		endSize = MAX_SCALE;
	}
	else
	{
		firstPosition = CENTER_POINT;
		endPosition = UNDER_POINT;

		//		�ړ��̑J�ڗ�
		move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
		//		�T�C�Y�̑J�ڗ�
		size = 1.0f - sqrt(1.0f - pow(time, 2.0f));

		//		�����T�C�Y��ݒ�
		firstSize = MAX_SCALE;
		//		�ŏI�T�C�Y��ݒ�
		endSize = MIN_SCALE;
	}

	//		���W��ݒ肷��
	(*m_standardShader->GetUIInformation())[type].position = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	//		�T�C�Y��ݒ肷��
	(*m_standardShader->GetUIInformation())[type].scale = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::UPUnder(bool direction, float time, TitleUIType type)
{
	//		�J�ڗ�
	float move = 0.0f;
	//		�J�ڗ�
	float size = 0.0f;

	//		�������W
	DirectX::SimpleMath::Vector2 firstPosition;
	//		�ŏI���W
	DirectX::SimpleMath::Vector2 endPosition;

	//		�����T�C�Y
	float firstSize = MIN_SCALE - 0.5f;
	//		�ŏI�T�C�Y
	float endSize = MIN_SCALE;

	//		�`�揇���ŏ��ɂ���
	m_drawOder[0] = type;

	//		�ړ����������ď�����ς���
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

	//		���W��ݒ肷��
	(*m_standardShader->GetUIInformation())[type].position = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	//		�T�C�Y��ݒ肷��
	(*m_standardShader->GetUIInformation())[type].scale = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}