/*
* @file		FloorObject.h
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

class FloorObject : public IFactory
{
public:

	//		�R���X�g���N�^
	FloorObject(ObjectManager* objectManager);

	//		�f�X�g���N�^
	~FloorObject();

	/*
	*	����������
	*
	*	@param	(position)	���W
	*/
	void Initialize(DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 rotation) override;

	//		�X�V����
	void Update() override;

	/*
	*	�`�揈��
	* 
	*	@param	(drawMesh)	���b�V���`��̃C���X�^���X�̃|�C���^
	*/
	void Render() override;

	//		�I������
	void Finalize() override;

	/*
	*	�I�u�W�F�N�g�^�C�v���󂯎��
	*
	*	@return�@�I�u�W�F�N�g�^�C�v
	*/
	Factory::Object GetObjectType() override { return Factory::Wall; }


	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return ���b�V���̏��
	*/
	ObjectMesh* GetObjectMesh(int index) override { 
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get(); }

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		�I�u�W�F�N�g�̃��b�V��
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		�e���
	ShadowInformation* m_shadowInformation;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_floorPS;

	// �e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	ObjectManager* m_objectManager;
public:

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	*
	*	@return �C���X�^���X
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
