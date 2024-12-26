/*
* @file		TitlePlayer.cpp
* @brief	�^�C�g���v���C���[�̏���
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "Library/Animation/AnimationManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "../Observer/TitlePlayerAnimationObserver/ITitlePlayerAnimationObserver.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"

class TitlePlayer : public ITitlePlayerAnimationObserver
{
public:

	//		�R���X�g���N�^
	TitlePlayer();

	//		�f�X�g���N�^
	~TitlePlayer();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	/*
	*	�`�揈��
	* 
	*	@param	(flag)	�|�X�g�G�t�F�N�g�t���O
	*/
	void Render(PostEffectFlag::Flag flag, 
				PostEffectObjectShader* postEffectObjectShader);

	//		�I������
	void Finalize();

	//		�v���C���̃A�j���[�V����
	void PlayAnimation() override;

	//	�ݒ莞�̃A�j���[�V����
	void SettingAnimation() override;

	//	�I�����̃A�j���[�V����
	void ExitAnimation() override;
private:

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};