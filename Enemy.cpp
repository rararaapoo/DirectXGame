#include "Enemy.h"
#include <assert.h>

void Enemy::Initialize(Model* model, uint32_t textureHandle) 
{ 
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	textureHandle_ = TextureManager::Load("cube.jpg");
	worldTransform_.Initialize();
	
}

void Enemy::Update() { 
	
	worldTransform_.matWorld_ = MakeAffineMetrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); 
}

void Enemy::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}