
#pragma once

#include "IObjectMove.h"

class ObjectMoveR : public IObjectMove
{
public:

	ObjectMoveR();

	~ObjectMoveR();

	void Initialize() override;

	void Update() override;

	void Finalize() override;

private:



};