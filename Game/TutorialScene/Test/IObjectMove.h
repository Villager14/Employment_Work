
#pragma once

#include "OInformation.h"

class IObjectMove
{
public:

	~IObjectMove() = default;

	//		����������
	virtual void Initialize() = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�I�u�W�F�N�g�̏��
	virtual OInformation* GetInformation() = 0;
};