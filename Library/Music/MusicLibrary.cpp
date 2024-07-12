/*
* @file		MusicLibrary.cpp
* @brief	音楽ライブラリシングルトン
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
	//		オーディオエンジンの生成
	m_audioEngineBGM = std::make_unique<DirectX::AudioEngine>();

	//		オーディオエンジンの生成
	m_audioEngineSoundEffect = std::make_unique<DirectX::AudioEngine>();

	//		BGMの作製
	CreateBGM(BGMType::TitleScene, L"Resources/Music/BGM/TitleScene/Concave.wav");
	CreateBGM(BGMType::PlayScene, L"Resources/Music/BGM/PlayScene/Cyber_City.wav");
	CreateBGM(BGMType::ResultScene, L"Resources/Music/BGM/ResultScene/サイバーポップ_2.wav");

	//		効果音の作製
	CreateSoundEffect(SoundEffectType::Select, L"Resources/Music/SoundEffect/TitleScene/カーソル移動8.wav");
	CreateSoundEffect(SoundEffectType::Decision, L"Resources/Music/SoundEffect/TitleScene/決定ボタンを押す23.wav");
	CreateSoundEffect(SoundEffectType::Jump, L"Resources/Music/SoundEffect/PlayScene/se_jump05.wav");
	CreateSoundEffect(SoundEffectType::Dash, L"Resources/Music/SoundEffect/PlayScene/se_shun1.wav");
	CreateSoundEffect(SoundEffectType::Wire, L"Resources/Music/SoundEffect/PlayScene/ジャンプ.wav");

	//		初期のボリューム
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
