/*
* @file		BackGroundObject.cpp
* @brief	�w�i�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/23
*/

#include "BackGroundObjectInformation.h"

#include "Library/Mesh/ObjectMesh.h"

class BackGroundObject
{
public:

	//		�R���X�g���N�^
	BackGroundObject();

	//		�f�X�g���N�^
	~BackGroundObject();

	//		����������
	void Initialize(std::vector<ObjectMesh*> mesh,
		const std::vector<DirectX::SimpleMath::Vector3>& m_wirePosition);

	//		�X�V����
	void Update();

	//		�`��I�u�W�F�N�g
	void Render(DirectX::SimpleMath::Vector3 cameraVelocity,
				DirectX::SimpleMath::Vector3 cameraPosition);

	//		�I������
	void Finalize();

	/*
	*	�J�����O�̏���
	* 
	*	@param	(index)	�v�f��
	*	@return true : �`�悷�� false : �`�悵�Ȃ�
	*/
	bool Culling(int index, DirectX::SimpleMath::Vector3 cameraVelocity,
		DirectX::SimpleMath::Vector3 cameraPosition);

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 fogColor;        //      �t�H�O�̐F
		DirectX::SimpleMath::Vector4 fogLength;       //      �t�H�O�̕ω�����
		DirectX::SimpleMath::Vector4 cameraPosition;  //      �J�����̍��W
	};

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		���
	std::unique_ptr<BackGroundObjectInformation> m_information;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	ConstBuffer m_constBuffer;

	//		�o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

public:

};
