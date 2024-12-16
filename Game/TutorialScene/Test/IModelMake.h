
#pragma once

#include "pch.h"

class IModelMake
{
public:

	~IModelMake() = default;

	virtual std::unique_ptr<DirectX::Model> GetModel();

};