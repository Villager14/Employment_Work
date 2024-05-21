/*
* @file		PlayerWire.h
* @brief	�v���C���[�̃��C���[���
* @author	Morita
* @date		2024/05/13
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWire : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerWire(Player* player);

	//		�f�X�g���N�^
	~PlayerWire();

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

	//		�ړ�����
	void MoveProcessing();

	//		��ԑJ�ڔ��f
	void ChangeStateJudgement();

	//		�����񂹂鎞�̏���
	void AttractProcess();

	//		�������̏���
	void FallProcess();

	//		������Ԃɂ��邩�ǂ���
	void FallJudgement();

private:
	
	//		����
	const float DECELERATION_SPEED = 8.0f;

private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�o�ߎ���
	float m_time;

	//		�����̍���
	float m_firstHeight;

	//		����
	float m_length;


	//		�ړ�����
	DirectX::SimpleMath::Vector3 m_direction;

	DirectX::SimpleMath::Vector3 m_acceleation;

	//		���x���󂯎��
	float m_speed;

	float m_firstSpeed;

	//		�������f
	bool m_fallJudgement;

	//		�����ɓ��������ꍇ
	bool m_floorHitJudgement;

	//		�ǂɓ����������H
	bool m_wallHitJudgement;
};
