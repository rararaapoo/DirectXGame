#include "Enemy.h"
#include <assert.h>

void Enemy::Initialize(Model* model, uint32_t textureHandle) 
{ 
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	textureHandle_ = TextureManager::Load("peng.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 2.0f, 20.0f};
	
}	

void Enemy::Update() { 
	
	const float kEnemySpeed = 0.2f;

	//worldTransform_.translation_.z -= kEnemySpeed;

	worldTransform_.matWorld_ = MakeAffineMetrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	switch (phase_) {	
	case Phase::Approach:
	default:
		//const float kEnemySpeedA = 0.2f;
		worldTransform_.translation_.z -= kEnemySpeed;

		if (worldTransform_.translation_.z < 0.1f)
		{
			phase_ = Phase::Leave;
		}

		break;
	case Phase::Leave:
		worldTransform_.translation_.x -= kEnemySpeed;
		worldTransform_.translation_.y += kEnemySpeed;
		break;
		
		break;
	}

}

void Enemy::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}