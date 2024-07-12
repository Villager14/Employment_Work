/*
* @file		MusicLibrary.cpp
* @brief	���y���C�u�����V���O���g��
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "MusicLibrary.h"

std::unique_ptr<MusicLibrary> MusicLibrary::m_library = nullptr;

MusicLibrary::MusicLibrary()
	:
	m_bgmVolume(0.5f),
	m_maxVolume(0.5f),
	m_soundEffectVolum(0.5f),
	m_mastarVolume(1.0f),
	m_nowBGM(Empty)
{

}

MusicLibrary::~MusicLibrary()
{
	if (m_audioEngineBGM)
	{
		m_audioEngineBGM->Suspend();
	}

	if (m_audioEngineSoundEffect)
	{
		m_audioEngineSoundEffect->Suspend();
	}

	m_audioLoop.reset();
}

MusicLibrary* const MusicLibrary::GetInstance()
{
	if (m_library == nullptr)
	{
		m_library.reset(new MusicLibrary());
	}

	return m_library.get();
}

void MusicLibrary::Initialize()
{
	//		�I�[�f�B�I�G���W���̐���
	m_audioEngineBGM = std::make_unique<DirectX::AudioEngine>();

	//		�I�[�f�B�I�G���W���̐���
	m_audioEngineSoundEffect = std::make_unique<DirectX::AudioEngine>();

	//		BGM�̍쐻
	CreateBGM(BGMType::TitleScene, L"Resources/Music/BGM/TitleScene/Concave.wav");
	CreateBGM(BGMType::PlayScene, L"Resources/Music/BGM/PlayScene/Cyber_City.wav");
	CreateBGM(BGMType::ResultScene, L"Resources/Music/BGM/ResultScene/�T�C�o�[�|�b�v_2.wav");

	//		���ʉ��̍쐻
	CreateSoundEffect(SoundEffectType::Select, L"Resources/Music/SoundEffect/TitleScene/�J�[�\���ړ�8.wav");
	CreateSoundEffect(SoundEffectType::Decision, L"Resources/Music/SoundEffect/TitleScene/����{�^��������23.wav");
	CreateSoundEffect(SoundEffectType::Jump, L"Resources/Music/SoundEffect/PlayScene/se_jump05.wav");
	CreateSoundEffect(SoundEffectType::Dash, L"Resources/Music/SoundEffect/PlayScene/se_shun1.wav");
	CreateSoundEffect(SoundEffectType::Wire, L"Resources/Music/SoundEffect/PlayScene/�W�����v.wav");

	//		�����̃{�����[��
	m_audioEngineBGM->SetMasterVolume(m_bgmVolume);
	m_audioEngineSoundEffect->SetMasterVolume(m_soundEffectVolum);
}

void MusicLibrary::CreateBGM(BGMType type, const wchar_t* path)
{
	m_bgmInformation.insert({ type, std::make_unique<DirectX::SoundEffect>(m_audioEngineBGM.get(), path)});
}

void MusicLibrary::CreateSoundEffect(SoundEffectType type, const wchar_t* path)
{
	m_soundEffectTypeInformation.insert({ type, std::make_unique<DirectX::SoundEffect>(m_audioEngineSoundEffect.get(), path) });
}
