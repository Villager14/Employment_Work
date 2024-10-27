/*
* @file		RespawnPointRead.cpp
* @brief	リスポーンポイントの読み込み処理
* @author	Morita
* @date		2024/10/03
*/

#include "pch.h"

#include <fstream>

#include "RespawnPointRead.h"

RespawnPointRead::RespawnPointRead()
{
}

RespawnPointRead::~RespawnPointRead()
{
}

void RespawnPointRead::ReadProcess(int stageNumber)
{
	std::string path = "";

	switch (stageNumber)
	{
	case 0:
		path = "Resources/Excel/SpownPoint/SpownPoint.csv";
		break;
	default:
		break;
	}

	//		ファイルを開く
	std::fstream file(path);

	//		ファイルが開いていない場合処理をしない
	if (!file.is_open()) return;

	std::string line;

	for (int i = 0; std::getline(file, line); ++i)
	{
		std::stringstream ss(line);

		std::string value;

		int index = 0;

		//		座標
		DirectX::SimpleMath::Vector3 position;

		//		長さ
		float length = 0.0f;

		while (std::getline(ss, value, ','))
		{
			SetParameter(value, index, &position, &length);

			index++;
		}

		m_position.push_back(position);
		m_length.push_back(length);
	}

	//		ファイルを閉じる
	file.close();

}

void RespawnPointRead::SetParameter(std::string val, int index, DirectX::SimpleMath::Vector3* position, float *length)
{
	if (index == 0)			position->x = std::stof(val);
	else if (index == 1)	position->y = std::stof(val);
	else if (index == 2)	position->z = std::stof(val);
	else if (index == 1)	*length		= std::stof(val);
}
