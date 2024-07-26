/*
* @file		BackGroundObjectInformation.h
* @brief	背景オブジェクトの情報
* @author	Morita
* @date		2024/06/05
*/

#include "pch.h"

#include "BackGroundObjectInformation.h"

BackGroundObjectInformation::BackGroundObjectInformation()
{
}

BackGroundObjectInformation::~BackGroundObjectInformation()
{
}

void BackGroundObjectInformation::Create(std::vector<ObjectMesh*> mesh,
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	//		メッシュの情報を整理する
	for (int i = 0, max = static_cast<int>(mesh.size()); i < max; ++i)
	{
		MeshChackProcess(mesh[i]);
	}

	for (int i = 0; i < wirePosition.size(); ++i)
	{
		m_meshCenter.push_back(wirePosition[i]);
		m_meshLength.push_back(100.0f);
	}

	CreateObjectPosition();
}

void BackGroundObjectInformation::MeshChackProcess(ObjectMesh* mesh)
{
	for (int i = 0; i < mesh->GetVertexSize(); ++i)
	{
		//		法線の方向を見る
		if (!ChackNormalize(mesh->GetNormalizePosition(i))) continue;

		DirectX::SimpleMath::Vector3 centerPosition = MeshCenter(mesh, i);

		//		メッシュの中心点を挿入する
		m_meshCenter.push_back(centerPosition);

		//		メッシュの中心からの長さの最長を求める
		m_meshLength.push_back(MeshMaxSide(mesh, i, centerPosition));
	}
}

bool BackGroundObjectInformation::ChackNormalize(DirectX::SimpleMath::Vector3 normalize)
{
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) >= 0.5f)
	{
		return true;
	}

	return false;
}

DirectX::SimpleMath::Vector3 BackGroundObjectInformation::MeshCenter(ObjectMesh* mesh, int index)
{
	//		中心点を求める
	DirectX::SimpleMath::Vector3 centerPosotion = (mesh->GetVertexPosition(index, 0)
													+ mesh->GetVertexPosition(index, 1)
													+ mesh->GetVertexPosition(index, 2)) / 3.0f;

	//		中心点を求める
	return centerPosotion;
}

float BackGroundObjectInformation::MeshMaxSide(ObjectMesh* mesh,
	int index, DirectX::SimpleMath::Vector3 centerPosition)
{
	float side1 = (mesh->GetVertexPosition(index, 0) - centerPosition).Length();
	float side2 = (mesh->GetVertexPosition(index, 1) - centerPosition).Length();
	float side3 = (mesh->GetVertexPosition(index, 2) - centerPosition).Length();

	return std::max(side1, std::max(side2, side3));
}

void BackGroundObjectInformation::CreateObjectPosition()
{
	for (int i = 0, max = static_cast<int>(m_meshCenter.size()); i < max; ++i)
	{
		float maxX = m_meshCenter[i].x + m_meshLength[i] + MAX_LENGTH;
		float maxZ = m_meshCenter[i].z + m_meshLength[i] + MAX_LENGTH;
		float minX = m_meshCenter[i].x - m_meshLength[i] - MAX_LENGTH;
		float minZ = m_meshCenter[i].z - m_meshLength[i] - MAX_LENGTH;

		//		ランダムなオブジェクトの座標を生成する
		RandomObjectPosition(maxX, minX, maxZ, minZ);
	}
}

/*
*	メッシュが密集し背景オブジェクトが絶対に置けない場合を想定し２００回乱数試し
*	座標が決まらなかった場合処理を行わない
*/
void BackGroundObjectInformation::RandomObjectPosition(float maxX, float minX, float maxZ, float minZ)
{
	int dot = 0;

	for (int j = 0; j < 3; ++j)
	{
		DirectX::SimpleMath::Vector3 randomPosition = DirectX::SimpleMath::Vector3(LibrarySingleton::GetInstance()->Random(minX, maxX),
			0.0f, LibrarySingleton::GetInstance()->Random(minZ, maxZ));

		if (ObjectMeshLength(randomPosition))
		{
			randomPosition.y = LibrarySingleton::GetInstance()->Random(-200.0f, -150.0f);

			m_objectPosition.push_back(randomPosition);

			//		オブジェクトの回転を作成する
			ObjectCreateRotation();
		}
		else
		{
			j--;
			dot++;
		}

		//		もし200回以上になったらオブジェクトを置けないとみなす
		if (dot > 200.0f)
		{
			break;
		}
	}
}

bool BackGroundObjectInformation::ObjectMeshLength(DirectX::SimpleMath::Vector3 randomPosition)
{
	for (int i = 0, max = static_cast<int>(m_meshCenter.size()); i < max; ++i)
	{
		if ((DirectX::SimpleMath::Vector3(m_meshCenter[i].x, 0.0f, m_meshCenter[i].z)
			- randomPosition).Length() <= m_meshLength[i] + NOT_EXSIT_LENGTH)
		{
			return false;
		}
	}

	for (int i = 0, max = static_cast<int>
		(m_objectPosition.size()); i < max; ++i)
	{
		//		距離が一定内の場合処理をしない
		if ((DirectX::SimpleMath::Vector3(m_objectPosition[i].x , 0.0f, m_objectPosition[i].z)
			- randomPosition).Length() < 100.0f)
		{
			return false;
		}
	}

	return true;
}

void BackGroundObjectInformation::ObjectCreateRotation()
{
	m_objectRotation.push_back(DirectX::SimpleMath::Vector3(
		LibrarySingleton::GetInstance()->Random(-10.0f, 10.0f),
		LibrarySingleton::GetInstance()->Random(0.0f, 360.0f),
		LibrarySingleton::GetInstance()->Random(-10.0f, 10.0f)
	));

	m_objectQuaternion.push_back(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		{ DirectX::XMConvertToRadians(LibrarySingleton::GetInstance()->Random(-10.0f, 10.0f)),
		  DirectX::XMConvertToRadians(LibrarySingleton::GetInstance()->Random(0.0f, 360.0f)),
		  DirectX::XMConvertToRadians(LibrarySingleton::GetInstance()->Random(-10.0f, 10.0f))}));
}

void BackGroundObjectInformation::Clear()
{
	m_meshCenter.clear();
	m_meshLength.clear();
}

void BackGroundObjectInformation::InstanceExpelement(std::vector<ObjectMesh*> mesh)
{
	//		メッシュの読み込みインスタンスの生成
	//m_loadMesh = std::make_unique<LeadMesh>();

	//std::vector<std::unique_ptr<Triangle>> triangle = m_loadMesh->Lead(L"Resources/ModelMesh/Bill.obj");

	//for (int i = 0; i < triangle.size(); ++i)
	//{
	//	Vertex vertex;
	//	m_vertex.push_back(vertex);

	//	m_vertex[i].position = triangle[i]->m_vertex;
	//}
	//		頂点バッファ
	//D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	//vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//vertexBufferDesc.ByteWidth = sizeof(Vertex) * .size();
	//vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexBufferDesc.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	//vertexData.pSysMem = .data();


}
