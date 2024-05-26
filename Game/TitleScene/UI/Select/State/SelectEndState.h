/*
* @file		SelectEndState.h
* @brief	�I����I���������
* @author	Morita
* @date		2024/05/26
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class SelectEndState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleSelectManager)	�^�C�g���I���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	SelectEndState(TitleSelectManager* titleSelectManager);

	//		�f�X�g���N�^
	~SelectEndState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;


private:

	TitleSelectManager* m_titleSelectManager;

	float m_time;

	bool m_flag;

	bool m_direction;

	DirectX::SimpleMath::Vector2 m_firstPosition;
};