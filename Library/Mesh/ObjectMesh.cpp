
#include "pch.h"

#include "ObjectMesh.h"

#include <fstream>

#include <Effects.h>

ObjectMesh::ObjectMesh()
	:
	m_staticObjectJudgement(false)
{
}

ObjectMesh::~ObjectMesh()
{
}

void ObjectMesh::Initialize(const wchar_t* filePath)
{
	//		メッシュの読み込みを生成する
	m_leadMesh = std::make_unique<LeadMesh>();

	//		読み込む
	m_triangle = m_leadMesh->Lead(filePath);

	//		オブジェクトメッシュを受け取る
	m_objectMesh = m_leadMesh->GetObjectMesh();

	//		リソースの開放(今後使わないので)
	m_leadMesh.reset();
}

void ObjectMesh::StaticProcess(const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Vector3& move)
{
	//		静的なオブジェクト
	m_staticObjectJudgement = true;

	//		先にワールド行列の計算をしておく
	for (int i = 0, max = static_cast<int>(m_triangle.size());
		i < max; ++i)
	{
		m_triangle[i].m_vertex[0] = DirectX::SimpleMath::Vector3::Transform(m_triangle[i].m_vertex[0], world);
		m_triangle[i].m_vertex[1] = DirectX::SimpleMath::Vector3::Transform(m_triangle[i].m_vertex[1], world);
		m_triangle[i].m_vertex[2] = DirectX::SimpleMath::Vector3::Transform(m_triangle[i].m_vertex[2], world);

		m_triangle[i].m_vertex[0] += move;
		m_triangle[i].m_vertex[1] += move;
		m_triangle[i].m_vertex[2] += move;

		m_triangle[i].m_normalVector = DirectX::SimpleMath::Vector3::Transform(m_triangle[i].m_normalVector, world);
	}
}

