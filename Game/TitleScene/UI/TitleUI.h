/*
* @file		TitleUI.h
* @brief	�^�C�g����UI
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Library/Shader/StandardShader.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "Effect/UI/TitleScene/SelectionBar/SelectionBar.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "../Observer/TitleUIObserver/ITitleUIObserver.h"

#include "Effect/UI/TitleScene/KeyGuidance/TitleKeyGuidance.h"

#include "Effect/UI/TitleScene/Fade/FadeUI.h"

#include "../Observer/FadeObserver/IFadeObserver.h"

class TitleUI : public ITitleUIObserver, public IFadeObserver
{
public:

	//		�R���X�g���N�^
	TitleUI();

	//		�f�X�g���N�^
	~TitleUI();

	//		����������
	void Initalize();

	//		�X�V����
	void Update();

	/*
	*	�`�揈��
	* 
	*	@param	(postEffectType)	�|�X�g�G�t�F�N�g�̃^�C�v
	*/
	void Render(int postEffectType);

	//		�I������
	void Finalize();

	/*
	*	���ւ̈ړ�����
	* 
	*	@param	(processingTime)	��������
	*/
	void DownSelect(float processingTime) override;

	/*
	*	��ւ̈ړ�����
	*
	*	@param	(processingTime)	��������
	*/
	void UpSelect(float processingTime) override;

	//		�V�[���I���t�F�[�h�A�E�g
	void SceneEndFadeOut() override;

	//		�t�F�[�h�A�E�g
	void FadeOut() override;

private:

	//		����
	void Generation();

private:

	//		UI�̎��
	enum TitleUIType
	{
		TitleRogo,	//		�^�C�g�����S
	};

private:

	//		�^�C�g�����S�̍��W
	const DirectX::SimpleMath::Vector2 TITLE_POINT = { 0.0f, -170.0f };

	//		�ő�X�P�[��
	const float MAX_SCALE = 1.0f;

	//		�ŏ��X�P�[��
	const float MIN_SCALE = 0.5f;

private:

	//		�^�C�g��UI�}�l�[�W���[
	std::unique_ptr<StandardShader<TitleUIType>> m_standardShader;

	//		�w�i����
	std::unique_ptr<BackGroundMove> m_backGround;

	//		�I���o�[
	std::unique_ptr<SelectionBar> m_selectionBar;

	//		�L�[�K�C�_���X
	std::unique_ptr<TitleKeyGuidance> m_keyGuidance;

	//		UI�ȊO�������t�F�[�h����
	std::unique_ptr<FadeUI> m_fadeUI;
};