#include "EnemyBullet.h"
#include <assert.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) 
{
	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("cube.jpg");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void EnemyBullet::Update()
{ 
	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

		if (--deathTimer <= 0) {
		isDead_ = true;
	}

}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}