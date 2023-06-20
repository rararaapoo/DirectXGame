#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Enemy 
{
public:
	void Initialize();

	void Update();

	void Draw();

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;


	

};
