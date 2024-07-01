/*
* @file		MusicLibrary.h
* @brief	���y���C�u�����V���O���g��
* @author	Morita
* @date		2024/06/28
*/

#pragma once

#include <Audio.h>

#include <unordered_map>

class MusicLibrary final
{
private:

	//		�R���X�g���N�^
	MusicLibrary();

public:

	//		�f�X�g���N�^
	~MusicLibrary();

	/*
	*	MusicLibrary�̃C���X�^���X���󂯎��
	*
	*	@return MusicLibrary
	*/
	static MusicLibrary* const GetInstance();

	//		����������
	void Initialize();

private:

	//		MusicLibrary�N���X�̃C���X�^���X�̃|�C���^
	static std::unique_ptr<MusicLibrary> m_library;

public:

	enum BGMType
	{
		TitleScene,
		PlayScene,
		ResultScene,
		Empty
	};

	enum SoundEffectType
	{
		Select,
		Decision,
		Jump,
		Dash,
		Wire,
	};

private:

	//		�I�[�f�B�I�G���W��BGM
	std::unique_ptr<DirectX::AudioEngine> m_audioEngineBGM;

	//		�I�[�f�B�I�G���W�����ʉ�
	std::unique_ptr<DirectX::AudioEngine> m_audioEngineSoundEffect;

	//		���[�v�T�E���h
	std::unique_ptr<DirectX::SoundEffectInstance> m_audioLoop;

	//		BGM�̏��
	std::unordered_map<BGMType, std::unique_ptr<DirectX::SoundEffect>> m_bgmInformation;

	//		���ʉ��̏��
	std::unordered_map<SoundEffectType, std::unique_ptr<DirectX::SoundEffect>> m_soundEffectTypeInformation;


	//		BGM�̃{�����[��
	float m_bgmVolume;

	//		�Đ�����BGM
	BGMType m_nowBGM;

	//		�ő剹��
	float m_maxVolume;

public:

	/*
	*	BGM�̍Đ�
	* 
	*	@param	(type)	BGM�̎��
	*/
	void PlayBGM(BGMType type) 
	{
		if (type == m_nowBGM) return;

		m_nowBGM = type;

		m_audioLoop = m_bgmInformation[m_nowBGM]->CreateInstance();

		m_audioLoop->Play(true);
	}


	/*
	*	���ʉ��̍Đ�
	* 
	*	@param	(tpe)	���ʉ��̎��
	*/
	void PlaySoundEffect(SoundEffectType type)
	{
		m_soundEffectTypeInformation[type]->Play();
	}

	/*
	*	�V�[���̉��ʂ̑J��
	* 
	*	@param	(time)	�J�ڎ���
	*/
	void SceneLerpVolume(float time)
	{
		//		���ʂ̑J��
		m_bgmVolume = Library::Lerp(0.0f, m_maxVolume, time);

		//		�����̃{�����[��
		m_audioEngineBGM->SetMasterVolume(m_bgmVolume);
	}

private:

	/*
	*	BGM�̍쐻
	* 
	*	@param	(type)	BGM�̎��
	*	@param	(path)	�t�H���_�p�X
	*/
	void CreateBGM(BGMType type, const wchar_t* path);

	/*
	*	���ʉ��̍쐬
	* 
	*	@param	(type)	���ʉ��̎��
	*	@param	(path)	�t�@�C���p�X
	*/
	void CreateSoundEffect(SoundEffectType type, const wchar_t* path);
};