/*
* @file		UIMouseCollider.h
* @brief	���j���[��UI�̓����蔻��
* @author	Morita
* @date		2024/12/20
*/

#include "pch.h"

#include "../Observer/Mouse/IMenuMouseObserver.h"

#include "../Collider/MenuColliderInformation.h"

#include "../Observer/Collider/MenuColliderObserver.h"

class UIMouseCollider : public IMenuMouseObserver
{
public:

	//		�R���X�g���N�^
	UIMouseCollider();

	//		�f�X�g���N�^
	~UIMouseCollider();

	//		�I������
	void Finalize();

	/*
	*	�}�E�X��X���W�̍X�V
	*
	*	@param	(x) x���W
	*/
	void MousePositionX(int x) override;

	/*
	*	�}�E�X��Y���W�̍X�V
	*
	*	@param	(y) y���W
	*/
	void MousePositionY(int y) override;

	void CollitionProcess(const std::vector<MenuColliderInformation>& information);

	/*
	*	�l�p�̓����蔻��̏���
	* 
	*	@param	(information)	���b�V���̏��
	*	@param	(boxLength)		�l�p�̔����̒���
	*/
	void BoxColliderProcess(MenuColliderInformation information,
							DirectX::SimpleMath::Vector2 boxLength);

	/*
	*	�l�p�̓����蔻��
	*
	*	@param	(min)	�ŏ��l
	*	@param	(max)	�ő�l
	*	@return true : �������Ă��� false : �������Ă��Ȃ�
	*/
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

private:

	//		�܂݂̑傫��
	const DirectX::SimpleMath::Vector2 KNOB_LENGTH = { 15.0f, 33.0f };

	//		�^�u�̑傫��
	const DirectX::SimpleMath::Vector2 TAB_LENGTH = { 140.0f, 52.0f };

	//		�{�^���̑傫��
	const DirectX::SimpleMath::Vector2 BUTTON_LENGTH = { 199.0f, 58.0f };

private:

	//		�}�E�X�̍��WX
	int m_mousePositionX;

	//		�}�E�X�̍��WY
	int m_mousePositionY;

	//		�����蔻��I�u�U�[�o�[
	std::unique_ptr<MenuColliderObserver> m_colliderObserver;

public:

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	* 
	*	@param	�I�u�U�[�o�̃C���X�^���X�̃|�C���^
	*/
	void AddColliderObserver(IMenuColliderObserver* observer) { m_colliderObserver->AddObserver(observer); }
};