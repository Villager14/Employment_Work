/*
* @file		MoveObject.h
* @brief	�ړ��I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/11/13
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class MoveObject : public IFactory
{
public:

	//		�R���X�g���N�^
	MoveObject(ObjectManager* objectManager);

	//		�f�X�g���N�^
	~MoveObject();

	/*
	*	����������
	*
	*	@param	(position)	���W
	*/
	void Initialize(ObjectInformation information) override;

	//		�X�V����
	void Update() override;

	/*
	*	�`�揈��
	* 
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader) override;

	//		�I������
	void Finalize() override;

	/*
	*	�I�u�W�F�N�g�^�C�v���󂯎��
	*
	*	@return�@�I�u�W�F�N�g�^�C�v
	*/
	Factory::Object GetObjectType() override { return Factory::Move; }


	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return ���b�V���̏��
	*/
	ObjectMesh* GetObjectMesh(int index) override { 
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get(); }

	/*
	*	�|�X�g�G�t�F�N�g�t���O
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{ return m_postEffectFlag.get(); }

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// �e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	ObjectManager* m_objectManager;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_firstPosition;
	DirectX::SimpleMath::Vector3 m_secondPosition;

	DirectX::SimpleMath::Vector3 m_rotation;

	//		����
	float m_time;

	float m_speed;

public:

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return �C���X�^���X
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};