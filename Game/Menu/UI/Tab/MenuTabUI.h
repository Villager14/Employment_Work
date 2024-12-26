/*
* @file		MenuTabUI.h
* @brief	���j���[��TabUI
* @author	Morita
* @date		2024/12/19
*/

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "Effect/UI/Menu/MenuSelect/MenuSelect.h"

#include "../MenuUITabEnums.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

class MenuTabUI
{
public:

	//		�R���X�g���N�^
	MenuTabUI(AboveUI* abvoceUI,
		MenuSummarizeColliderInformation* summarizeColliderInformation);

	//		�f�X�g���N�^
	~MenuTabUI();

	//		����������
	void Initialize();
	
	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	/*
	*	�^�uUI�̈ړ�
	*
	*	@param	(move)	�ړ���(0~1)
	*/
	void TabMove(float move);

	/*
	*	�X���C�_�[�̓����蔻����̒ǉ�
	*
	*	@param	(position)	���W
	*	@param	(type)		UI�^�C�v
	*/
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2 *position, UISubType type);

private:

	//		�㏸UI
	AboveUI* m_abvoceUI;

	//		���j���[�̍��ڑI��
	std::unique_ptr<MenuSelect> m_menuSelect;

	//		�ړ���
	float m_move;

	//		���j���[�̃^�C�v
	MenuUITaype::UIType m_type;

	//		�G�t�F�N�g�o�ߎ���
	float m_effectElapsedTime;

	//		�������Ă��邩�ǂ���
	bool m_hitJudgement;

	bool m_colliderJudgement;

	//		�����蔻����
	std::vector<MenuColliderInformation> m_colliderInformation;

	//		�����蔻����܂Ƃ߂�1
	MenuSummarizeColliderInformation* m_summarizeColliderInformation;

	//		Tab���g�����ǂ���
	bool m_useJudgement;

public:

	/*
	*	���j���[��ނ�ݒ肷��
	* 
	*	@param	(type)	UI�̎��
	*/
	void SetTabType(MenuUITaype::UIType type) { m_type = type; m_hitJudgement = true; }

	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }

	void TabUserJudgement(bool judgement) { m_useJudgement = judgement; }
};