/*
* @file		PlayerGoal.h
* @brief	�v���C���[�S�[�����
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerGoal : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerGoal(Player* player);

	//		�f�X�g���N�^
	~PlayerGoal();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�ړ�����
	void Move() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;
	
private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;
};