/*
* @file		BackGroundObject.cpp
* @brief	�w�i�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/23
*/

class BackGroundObject
{
public:

	//		�R���X�g���N�^
	BackGroundObject();

	//		�f�X�g���N�^
	~BackGroundObject();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`��I�u�W�F�N�g
	void Render();

	//		�I������
	void Finalize();

private:

	//		�����f��
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

public:

};
