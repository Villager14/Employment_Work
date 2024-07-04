

#pragma once

class ConstBufferManager
{
public:

	//		�R���X�g���N�^
	ConstBufferManager();

	//		�f�X�g���N�^
	~ConstBufferManager();

	template<typename T>
	void CreateConstBuffer(const T& obj);

	template<typename T>
	void UpdateBuffer(const T& data);

	void BindBuffer();
private:

	//		�o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
};

template<typename T>
inline void ConstBufferManager::CreateConstBuffer(const T& obj)
{
	UNREFERENCED_PARAMETER(obj);

	T buffer = {};

	//		�V�F�[�_�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(buffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateBuffer(&bd, nullptr, &m_buffer);
}

template<typename T>
inline void ConstBufferManager::UpdateBuffer(const T& data)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	context->UpdateSubresource(m_buffer.Get(), 0, NULL, &data, 0, 0);
}


