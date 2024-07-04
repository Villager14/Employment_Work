/*
* @file		FloorObject.h
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "WireObjectInformation.h"

class WireObject
{
public:

	//		�R���X�g���N�^
	WireObject();

	//		�f�X�g���N�^
	~WireObject();

	//		����������
	void Initialize(DirectX::SimpleMath::Vector3 position, int number);

	/*
	*	�X�V����
	*
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�`�揈��
	* 
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render();

	//		�I������
	void Finalize();

private:

	//		���C���[���f��
	std::unique_ptr<DirectX::Model> m_wireModel;

	//		���C���[�͈̔̓��f��
	std::unique_ptr<DirectX::Model> m_wireRangeModel;

	//		�H�I�u�W�F�N�g
	std::unique_ptr<DirectX::Model> m_wingModel;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		�f�o�b�N�p�̃��[���h���W
	DirectX::SimpleMath::Matrix m_debugWorld;
	
	//		�͈�
	float m_range;

	//		��]
	float m_rotation;

	//		�H�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wingPosition;

	//		���
	WireObjectInformation m_information;

public:

	/*
	*	���C���[�I�u�W�F�N�g���g�p�\���H
	* 
	*	@return �g�p�\�� true : �g�p�\ false : �g�p�s�\
	*/
	bool GetWireAvailableJudgement() { return m_information.m_usedJudgement; }

	/*
	*	���W���󂯎��
	* 
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_information.position; }

	WireObjectInformation* GetWireInformation() { return &m_information; }
};
