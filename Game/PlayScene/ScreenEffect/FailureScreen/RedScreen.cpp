/*
* @file		RedScreen.h
* @brief	�Ԃ���ʉ�
* @author	Morita
* @date		2024/05/22
*/
#include "pch.h"

#include "RedScreen.h"
#include "Game/PlayScene/UIManager/BinaryFile.h"
#include "Library/Library.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> RedScreen::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),	D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,	sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0},
};

RedScreen::RedScreen()
	:
	m_rotationMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_time(0.0f),
	concentrationLineTime(0.0f),
	concentrationCoolTime(0.0f),
	m_blerString(0.0f),
	m_baseScale(0.0f),
	m_grayJudgement(false),
	m_menuTime(0.0f),
	m_menuOpenJudgement(false)
{
}

RedScreen::~RedScreen()
{
}

//		�V�F�[�_�[��ǂݍ���
void RedScreen::Create(
	DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale)
{
	m_position = position;
	m_baseScale = m_scale = scale;

	LoadTexture(L"Resources/Texture/UI/Speed/UISpeed.png");

	//		�V�F�[�_�[�̍쐻
	CreateShader();
}

void RedScreen::Update(GameManager* gameManager, PlayerCameraInformation* playerCameraInformation)
{
	if (gameManager->FlagJudgement(GameManager::DeathJudgement))
	{
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);
	}
	else
	{
		m_time = 0.0f;
	}

	m_cameraMove = playerCameraInformation->GetCameraMove();

	m_blerString = m_cameraMove.Length();

	m_blerString *= 0.01f;

	m_cameraMove.Normalize();

	if (concentrationCoolTime < 0.5f)
	{
		concentrationCoolTime += LibrarySingleton::GetInstance()->GetElpsedTime();
	}

	concentrationCoolTime = 0.0f;

	//		�W�����̕ω�����
	concentrationLineTime = LibrarySingleton::GetInstance()->Random(0.0f, 1080.0f);

	concentrationChange = LibrarySingleton::GetInstance()->Random(0.2f, 0.3);
}

void RedScreen::Gray(MenuInformation* menuInformation)
{
	//		���j���[���J������
	if (menuInformation->GetMenuTransrationJudgement() && !m_menuOpenJudgement)
	{
		m_menuTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_menuTime = Library::Clamp(m_menuTime, 0.0f, 1.0f);

		if (m_menuTime >= 1.0f)
		{
			//		���j���[���J���Ă����Ԃɂ���
			m_menuOpenJudgement = true;
		}
	}

	//		���j���[���J���Ă��鎞
	if (m_menuOpenJudgement && !menuInformation->GetMenuTransrationJudgement())
	{
		m_menuTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_menuTime = Library::Clamp(m_menuTime, 0.0f, 1.0f);

		if (m_menuTime <= 0.0f)
		{
			//		���j���[���J���Ă����Ԃɂ���
			m_menuOpenJudgement = false;
		}
	}
}

void RedScreen::Render(ID3D11ShaderResourceView* shaderResouceView)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(2)),
		DirectX::SimpleMath::Vector4(m_position.x, m_position.y,
		LibrarySingleton::GetInstance()->GetScreenSize().x,
		LibrarySingleton::GetInstance()->GetScreenSize().y),
		DirectX::SimpleMath::Vector2(1.0f,1.0f))
	};

	//		�V�F�[�_�ɓn���ǉ��̃o�b�t�@���쐬����
	ConstBuffer cbuff;
	cbuff.rotationMatrix = m_rotationMatrix.Transpose();
	cbuff.windowSize = DirectX::SimpleMath::Vector4(LibrarySingleton::GetInstance()->GetScreenSize().x,
		LibrarySingleton::GetInstance()->GetScreenSize().y, 1, 1);
	cbuff.time = { static_cast<float>(m_time),0,0,0 };
	cbuff.motionVector = { m_cameraMove.x, m_cameraMove.y, 0.0f, 0.0f};
	cbuff.blurStrength = { m_blerString, 0.0f ,0.0f, 0.0f };
	cbuff.concentrationLineTime = { concentrationLineTime , concentrationChange, 0.0f ,0.0f};
	cbuff.grayStrength = { m_menuTime , 0.0f, 0.0f, 0.0f };

	//		�󂯓n���p�o�b�t�@
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//		�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//		�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { LibrarySingleton::GetInstance()->GetCommonState()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//		�������`��w��
	ID3D11BlendState* blendestate = LibrarySingleton::GetInstance()->GetCommonState()->NonPremultiplied();

	//		�������菈��
	context->OMSetBlendState(blendestate, nullptr, 0xFFFFFFFF);

	//		�[�x�o�b�t�@�ɏ������ݎQ��
	context->OMSetDepthStencilState(LibrarySingleton::GetInstance()->GetCommonState()->DepthDefault(), 0);

	//		�J�����O�͍����
	context->RSSetState(LibrarySingleton::GetInstance()->GetCommonState()->CullNone());

	//		�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometoryShaer.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//		�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����
	context->PSSetShaderResources(0, 1, &shaderResouceView);
	context->PSSetShaderResources(1, 1, &m_texture);

	//		�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//		�|���S����`��
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Begin();
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->End();

	//		�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

void RedScreen::LoadTexture(const wchar_t* path)
{
	//		�摜�t�@�C���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, m_resource.ReleaseAndGetAddressOf(),
		m_texture.ReleaseAndGetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

	//		�e�N�X�`����
	DX::ThrowIfFailed(m_resource.As(&texture));

	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);
}

//		�V�F�[�_�[�̓ǂݍ���
void RedScreen::CreateShader()
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		�R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shader/RedScreen/RedScreenPS.cso");
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shader/RedScreen/RedScreenVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shader/RedScreen/RedScreenGS.cso");

	//		�C���v�b�g���C�A�E�g�̍쐻
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//		���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//		�G���[
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		return;
	}

	//		�W�I���g���b�N�V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometoryShaer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader failed", NULL, MB_OK);

		return;
	}

	//		�s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Failde", NULL, MB_OK);
		return;
	}

	//		�V�F�[�_�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}
