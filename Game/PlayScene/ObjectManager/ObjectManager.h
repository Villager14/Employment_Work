/*
* @file		ObjectManager.h
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "WireObject/WireObject.h"

#include "BackGroundObject/BackGroundObject.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Game/PlayScene/Shadow/ShadowInformation.h"

#include "WireObject/WireObjectInformation.h"

#include "../GameManager/GameManager.h"

#include "Library/Factory/Factory.h"

#include "Library/Factory/IFactory.h"

class ObjectManager
{
public:

	//		�R���X�g���N�^
	ObjectManager(ShadowInformation* shadowInformation,
		GameManager* gameManager);

	//		�f�X�g���N�^
	~ObjectManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	�`�揈��
	* 
	*	@param	(cameraVelocity)	�����x�N�g��
	*/
	void Render(DirectX::SimpleMath::Vector3 cameraVelocity, DirectX::SimpleMath::Vector3 cameraPosition);

	//		�I������
	void Finalize();

	/*
	*	�I�u�W�F�N�g�̍��W
	* 
	*	@param	(position)	�I�u�W�F�N�g�̍��W
	*	@return true �J�����O���� false : �J�����O���Ȃ�
	*/
	bool Culling(DirectX::SimpleMath::Vector3 position);

private:
	//		�v���C���[�̍s��
	DirectX::SimpleMath::Matrix m_playerMatrix;

	//		���C���[�I�u�W�F�N�g
	std::vector<std::unique_ptr<WireObject>> m_wireObject;

	//		�w�i�I�u�W�F�N�g
	std::unique_ptr<BackGroundObject> m_backGroundObject;

	//		�I�u�W�F�N�g�̃��b�V��
	std::vector<ObjectMesh*> m_objectMesh;

	//		���b�V����`�悷��
	std::unique_ptr<DrawMesh> m_drawMesh;

	//		���C���[�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

	//		�e���
	ShadowInformation* m_shadowInformation;

	//		�J���������x�N�g��
	DirectX::SimpleMath::Vector3 m_cameraVelocity;

	//		�J�����̍��W
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//		���C���[�I�u�W�F�N�g�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wireObjectPosition;

	//		���C���[�̏��
	std::vector<WireObjectInformation*> m_wireInformation;

	//		�t�@�N�g���[
	std::unique_ptr<Factory> m_factory;

	std::vector<std::unique_ptr<IFactory>> m_factoryObject;

	GameManager* m_gameManager;

public:

	/*
	*	�v���C���[�̃��[���h�s����󂯎��
	* 
	*	@return �s��
	*/
	const DirectX::SimpleMath::Matrix& GetPlayerWorld() { return m_playerMatrix; }

	/*
	*	�v���C���[�̃��[���h�s���ݒ肷��
	* 
	*	@param	(position)	�v���C���[�̍s��
	*/
	void SetPlayerWorld(const DirectX::SimpleMath::Matrix& matrix) { m_playerMatrix = matrix; }

	/*
	*	�I�u�W�F�N�g���b�V�����󂯎��
	* 
	*	@return �I�u�W�F�N�g���b�V���̃C���X�^���X�̃|�C���^
	*/
	std::vector<ObjectMesh*> GetMesh() { return m_objectMesh; }

	/*
	*	���C���[�̍��W���󂯎��
	*
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWirePosition() { return m_wirePosition; }

	/*
	*	���C���[�I�u�W�F�N�g�̏����󂯎��
	* 
	*	@return	���C���[���
	*/
	std::vector<WireObjectInformation*> GetUseWireInformation() { return m_wireInformation; }

	GameManager* GetGameManager() { return m_gameManager; }
};
