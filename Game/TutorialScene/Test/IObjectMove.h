
#pragma once

#include "OInformation.h"

class IObjectMove
{
public:

	~IObjectMove() = default;

	//		初期化処理
	virtual void Initialize() = 0;

	//		更新処理
	virtual void Update() = 0;

	//		終了処理
	virtual void Finalize() = 0;

	//		オブジェクトの情報
	virtual OInformation* GetInformation() = 0;
};