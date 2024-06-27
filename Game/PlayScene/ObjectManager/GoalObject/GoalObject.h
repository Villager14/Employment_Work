/*
* @file		GoalObject.h
* @brief	�S�[���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/05/27
*/
#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

class GoalObject
{
public:

	//		�R���X�g���N�^
	GoalObject();

	//		�f�X�g���N�^
	~GoalObject();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	/*
	*	�`�揈��
	* 
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render(DrawMesh* drawMesh);

	//		�I������
	void Finalize();

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_floorPS;

	// �e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;

	//		��]��
	float m_rotation;

public:

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return �C���X�^���X
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
