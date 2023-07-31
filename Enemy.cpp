#include "Enemy.h"
#include <assert.h>
#include "GameScene.h"

Enemy::~Enemy()
{
	/*for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}*/
}

void Enemy::Initialize(Model* model, uint32_t textureHandle, Vector3& velocity, Vector3& position) { 
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	textureHandle_ = TextureManager::Load("peng.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	
}	

Vector3 Enemy::GetWorldPosition()
{ 
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Enemy::Update() { 
	
	const float kEnemySpeed = 0.2f;

	timer++;


	//worldTransform_.translation_.z -= kEnemySpeed;

	worldTransform_.matWorld_ = MakeAffineMetrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	switch (phase_) {	
	case Phase::Approach:
	default:
		//const float kEnemySpeedA = 0.2f;
		//worldTransform_.translation_.z -= kEnemySpeed;
		/*
		if (worldTransform_.translation_.z < 0.1f)
		{
			phase_ = Phase::Leave;
		}*/

		break;
	case Phase::Leave:
		
		worldTransform_.translation_.x -= kEnemySpeed;
		worldTransform_.translation_.y += kEnemySpeed;
		break;
		
		break;
	}

	if (timer >= 60)
	{
		Fire();
		timer = 0;
	}
		
	


	/*for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}*/

	/*bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});*/
}

void Enemy::Fire()
{
	//const float kBulletSpeed = 1.0f;
	Vector3 velocity;
	//velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	//Enemy::SetPlayer(player_);
	player_->GetWorldPosition();
	GetWorldPosition();
	
	// c = b - a
	velocity.x = player_->GetWorldPosition().x - GetWorldPosition().x;
	velocity.y = player_->GetWorldPosition().y - GetWorldPosition().y;
	velocity.z = player_->GetWorldPosition().z - GetWorldPosition().z;
	
	float leg =
	    sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y) + (velocity.z * velocity.z));

	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
//	Vector3 velocity1;
	Vector3 diie;
	diie.x = velocity.x / leg;
	diie.y = velocity.y / leg;
	diie.z = velocity.z / leg;
	//velocity.x = GetWorldPosition().x - player_->GetWorldPosition().x;
	//velocity.y = GetWorldPosition().y - player_->GetWorldPosition().y;
	//velocity.z *= GetWorldPosition().z - player_->GetWorldPosition().z;

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, /* velocity*/ diie);
	//bullets_.push_back(newBullet);
	gameScene_->AddEnemyBullet(newBullet);
}



void Enemy::OnCollision()
{ isDead_ = true; }

void Enemy::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	/*for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}*/
}