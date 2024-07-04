/*
* @file		AudioSetting.h
* @brief	���̐ݒ�
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class AudioSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	()
	*/
	AudioSetting(MenuManager* menuManager);

	//		�f�X�g���N�^
	~AudioSetting();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		���j���[�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	MenuManager* m_menuManager;

};