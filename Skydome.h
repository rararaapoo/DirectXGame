#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Skydome 
{
public:

	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection_);

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	
	uint32_t textureHandle_ = 0;

	//ViewProjection viewProjection_;
};
