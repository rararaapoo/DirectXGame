#include "Skydome.h"
#include <assert.h>

void Skydome::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHandle_ = textureHandle;

	textureHandle_ = TextureManager::Load("uvChecker.png"); 
	
}

void Skydome::Update()
{
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);
}