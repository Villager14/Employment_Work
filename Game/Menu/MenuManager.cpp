/*
* @file		MenuManager.cpp
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

MenuManager::MenuManager()
	:
	m_state(),
	m_selectUI{},
	m_type{},
	m_rangeUI{ AboveUI::UIType::Empty },
	m_slideUIType{AboveUI::UIType::Empty},
	m_menuJudgement{NULL},
	m_firstAudioMenuJudgement(true)
{
}

MenuManager::~MenuManager()
{
	m_menuJudgement = nullptr;
}

void MenuManager::Initialize()
{
	//		��Ԃ̐���
	m_menuStateInformation.insert({ Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ Audio, std::make_unique<AudioSetting>(this) });
	m_menuStateInformation.insert({ Option, std::make_unique<OptionSetting>(this) });
	m_menuStateInformation.insert({ GamePlay, std::make_unique<EndSetting>(this) });
	m_menuStateInformation.insert({ Close, std::make_unique<MenuClose>(this) });

	m_type = Start;

	//		�����̏��
	m_state = m_menuStateInformation[m_type].get();

	//		����������
	m_state->Initialize();

	//		���j���[�̏��𐶐�����
	m_information = std::make_unique<MenuInformation>();

	//		���j���[�̏�������������
	m_information->Initialzie();
}

void MenuManager::Update()
{
	//		�}�E�X�𑊑Έʒu�ɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);

	//		�X�V����
	m_state->Update();
}

void MenuManager::Render()
{
	//		�`�揈��
	m_state->Render();

	//		�f�o�b�N�t�H���g
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionX",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x), 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionY",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y), 0, 30);
	LibrarySingleton::GetInstance()->DebugFont(L"HitJudgement",
		BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX), 0, 60);
}

void MenuManager::Finalize()
{
}

void MenuManager::MenuBackRneder()
{
	//		�w�i�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::BackGround);

	//		�o�[�P�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar1);

	//		�o�[�Q�̕`��
	m_information->GetStandardShader()->Render(MenuInformation::UIType::Bar2);
}

bool MenuManager::BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max)
{
	DirectX::SimpleMath::Vector2 mousePosition;

	mousePosition.x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	mousePosition.y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	//		�͈͓��Ƀ}�E�X�����邩�ǂ���
	if (min.x <= mousePosition.x && max.x >= mousePosition.x &&
		min.y <= mousePosition.y && max.y >= mousePosition.y)
	{
		//		�͈͓�
		return true;
	}

	//		�͈͊O
	return false;
}

void MenuManager::RoughMenuViwe(float transitionTime)
{
	//		Opetion�̕`��
	m_information->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, transitionTime);

	//		GamePlay�̕`��
	m_information->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, transitionTime);

	//		Audio�̃^�C�g���`��
	m_information->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, transitionTime);
}

void MenuManager::MenuSelectView()
{
	//		�I�����Ă��Ȃ��ꍇ�`�揈�������Ȃ�
	if (m_rangeUI != AboveUI::UIType::Empty)
		m_information->GetMenuSelect()->Render((*m_information->GetAboveUI()->GetInformation())[m_rangeUI].position);
}

void MenuManager::ChangState(MenuType type)
{
	//		�����^�C�v�̏ꍇ���������Ȃ�
	if (m_type == type) return;

	//		�I������
	m_state->Finalize();

	//		�^�C�v�̍X�V
	m_type = type;

	//		��Ԃ̍X�V
	m_state = m_menuStateInformation[type].get();

	//		����������
	m_state->Initialize();
}

bool MenuManager::MenuEscCloseProcess()
{
	//		ESC�L�[���������ꍇ
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()
		->IsKeyPressed(DirectX::Keyboard::Escape))
	{
		return true;
	}

	return false;
}

bool MenuManager::ButtonCollider(MenuType type)
{
	MenuType hitType = MenuType::Empty;

	//		�͈͓��ɂ��邩�ǂ����̃t���O
	bool hitJudgement = false;

	//		Audio�̑�܂��{�^�����ɂ��邩�H
	if (BoxCollider(m_information->AUDIO_TITLE_POSITION_MIN, m_information->AUDIO_TITLE_POSITION_MAX))
	{
		//		�͈͓��ɂ���UI��Audio�ɂ���
		m_rangeUI = AboveUI::AudioSelect;

		//		�͈͓��ɂ���
		hitJudgement = true;

		//		�͈͂ɂ�����̂����݂̏�ԂłȂ���Ώ���������
		if (MenuType::Audio != type)
			hitType = MenuType::Audio;
	}
	
	//		Option�̑�܂��ȃ{�^�����ɂ��邩�H
	if (BoxCollider(m_information->OPTION_TITLE_POSITION_MIN, m_information->OPTION_TITLE_POSITION_MAX))
	{
		//		�͈͓��ɂ���UI��Option�ɂ���
		m_rangeUI = AboveUI::OptionSelect;

		//		�͈͓��ɂ���
		hitJudgement = true;

		//		�͈͂ɂ�����̂����݂̏�ԂłȂ���Ώ���������
		if (MenuType::Option != type)
			hitType = MenuType::Option;
	}
	
	//		Back�̑�܂��ȃ{�^���̒��ɂ��邩�H
	if (BoxCollider(m_information->GAMEPLAY_TITLE_POSITION_MIN, m_information->GAMEPLAY_TITLE_POSITION_MAX))
	{
		//		�͈͓��ɂ���UI��GamePlay�ɂ���
		m_rangeUI = AboveUI::GamePlaySelect;

		//		�͈͓��ɂ���
		hitJudgement = true;

		//		�͈͂ɂ�����̂����݂̏�ԂłȂ���Ώ���������
		if (MenuType::GamePlay != type)
			hitType = MenuType::GamePlay;
	}

	//		�͈͓��ɂ��Ȃ��ꍇ
	if (!hitJudgement)
	{
		//		�I�����Ă��Ȃ���Ԃɂ���
		m_rangeUI = AboveUI::Empty;
		
		//		���Ԃ̃��Z�b�g
		m_information->GetMenuSelect()->TimeReset();
	}

	//		�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
	if (hitType == Empty) return false;

	//		�͈͓��ŃN���b�N�����ꍇ
	if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
		== DirectX::Mouse::ButtonStateTracker().PRESSED)
	{
		//		�N���b�N������Ԃ�������
		m_selectUI = hitType;

		return true;
	}

	return false;
}

bool MenuManager::Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
							bool* startJudgement, bool endJudgement, bool moveJudgement)
{
	//		�J�n��Ԃ̏ꍇ
	if (*startJudgement)
	{
		//		����1�̍X�V
		*transitionTime1 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		����1����莞�Ԉȏ�ɂȂ����瑼�̎��Ԃ��X�V����
		if (*transitionTime1 > 0.3f)
		{
			//		����2�̍X�V
			*transitionTime2 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		����2����莞�Ԉȏ�3�J�ڃt���O���I���̏ꍇ����3�̍X�V������
			if (*transitionTime2 > 0.3f && moveJudgement)
			{
				//		����3�̍X�V
				*transitionTime3 += LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		1�ȏ�ɂȂ�Ȃ��悤�ɂ���
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		//		3�̍X�V������ꍇ
		if (moveJudgement)
		{
			//		3�̍X�V���I�������
			if (*transitionTime3 >= 1.0f)
			{
				//		�J�n��Ԃ��I������
				*startJudgement = false;
			}
		}
		else
		{
			//		2�̍X�V���I�������
			if (*transitionTime2 >= 1.0f)
			{
				//		�J�n��Ԃ��I������
				*startJudgement = false;
			}
		}

		return true;
	}

	//		�I����Ԃ̏ꍇ
	if (endJudgement)
	{
		//		����1�̍X�V
		*transitionTime1 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

		//		����1����莞�Ԉȉ��ɂȂ����瑼�̎��Ԃ��X�V����
		if (*transitionTime1 < 0.7f)
		{
			//		����2�̍X�V
			*transitionTime2 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;

			//		����2����莞�Ԉȉ�3�J�ڃt���O���I���̏ꍇ����3�̍X�V������
			if (*transitionTime2 < 0.7f && moveJudgement)
			{
				//		����3�̍X�V
				*transitionTime3 -= LibrarySingleton::GetInstance()->GetElpsedTime() * m_information->TRANSITION_SPEED;
			}
		}

		//		0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		if (moveJudgement)
		{
			if (*transitionTime3 <= 0.0f)
			{
				//		�V�[����؂�ւ���
				ChangState(MenuType::Close);
			}
		}
		else
		{
			if (*transitionTime2 <= 0.0f)
			{
				//		�V�[����؂�ւ���
				ChangState(m_selectUI);
			}
		}

		return true;
	}

	return false;
}

void MenuManager::SlideProcess(AboveUI::UIType type)
{
	//		���݂̍��W
	DirectX::SimpleMath::Vector2 nowPosition = (*m_information->GetAboveUI()->GetInformation())[type].position;

	//		���S���W
	nowPosition += {  LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
					  LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f };

	DirectX::SimpleMath::Vector2 max = nowPosition + m_information->KNOB_LENGTH;
	DirectX::SimpleMath::Vector2 min = nowPosition - m_information->KNOB_LENGTH;

	if (BoxCollider(min, max))
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_slideUIType = type;
		}
	}
	
	if (m_slideUIType == type)
	{
		(*m_information->GetAboveUI()->GetInformation())[type].position.x = static_cast<float>
			(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x) - 640.0f;

		(*m_information->GetAboveUI()->GetInformation())[type].position.x = Library::Clamp
		((*m_information->GetAboveUI()->GetInformation())[type].position.x,
			559 - 640.0f, 1120 - 640.0f);


		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().RELEASED)
		{
			//		���ʉ��̏ꍇ�̂ݗ������Ƃ����ʉ���炷
			if (m_slideUIType == AboveUI::UIType::SoundEffectKnob)
				MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

			m_slideUIType = AboveUI::UIType::Empty;
		}
	}
}
