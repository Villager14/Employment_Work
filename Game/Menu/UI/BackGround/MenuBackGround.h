/*
* @file		MenuTabUI.h
* @brief	���j���[��TabUI
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "Library/Shader/StandardShader.h"

class MenuBackGround
{
public:

	MenuBackGround();

	~MenuBackGround();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	/*
	*	�o�[�̃X�P�[���̕ύX
	* 
	*	@param	(float scale)
	*/
	void BarScale(float scale);

	/*
	*	���j���[�̓�������
	* 
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void MenuMoveProcess(float move);

private:

	enum UIType
	{
		BackGround,
		Bar1,
		Bar2,
	};

private:

	//		���b�Z�[�W�o�[�̃t�@�C���p�X
	const wchar_t* MESSAGE_BAR_FILE_PATH = L"Resources/Texture/UI/GameClear/messegeBer.png";

	//		���b�Z�[�W�w�i�̃t�@�C���p�X
	const wchar_t* MESSAGE_BACK_FILE_PATH = L"Resources/Texture/UI/GameClear/messegeBack.png";

	//		���b�Z�[�W�o�[�P�̃��j���[�����Ă���Ƃ��̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR1_CLOSE_POSITION = { 0.0f, 13.0f };

	//		���b�Z�[�W�o�[�P�̃��j���[���J�Ă���Ƃ��̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR1_OPEN_POSITION = { 0.0f, 300.0f };

	//		���b�Z�[�W�o�[�Q�̃��j���[�����Ă���Ƃ��̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR2_CLOSE_POSITION = { 0.0f, -13.0f };

	//		���b�Z�[�W�o�[�Q�̃��j���[���J�Ă���Ƃ��̍��W
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR2_OPEN_POSITION = { 0.0f, -300.0f };

private:

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;


};