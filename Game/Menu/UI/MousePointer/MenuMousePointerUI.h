/*
* @file		MenuMousePointerUI.h
* @brief	���j���[�̃}�E�X�|�C���^����
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "Library/Shader/StandardShader.h"

class MenuMousePointerUI
{
public:

	//		�R���X�g���N�^
	MenuMousePointerUI();

	//		�f�X�g���N�^
	~MenuMousePointerUI();

	//		����������
	void Initialize();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	enum UIType
	{
		MousePointa,
	};

private:

	//		���b�Z�[�W�w�i�̃t�@�C���p�X
	const wchar_t* MOUSE_POINTA_FILE_PATH = L"Resources/Texture/Menu/Title/mousePointa.png";

private:

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	�}�E�X�̍��WX��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetMousePositionX(int position) { 
		(*m_standardShader->GetUIInformation())[UIType::MousePointa].position.x = static_cast<int>(position) - LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f; }

	/*
	*	�}�E�X�̍��WY��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetMousePositionY(int position) { (*m_standardShader->GetUIInformation())[UIType::MousePointa].position.y = static_cast<float>(position) - LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f; }
};