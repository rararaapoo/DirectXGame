#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Matrix4x4.h"
#include <list>
#include "EnemyBullet.h"
#include "Player.h"

class Player;

enum class Phase
{
	Approach,
	Leave,
};

class Enemy 
{
public:
	~Enemy();
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection_);

	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	void OnCollision();

	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }



private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;
	
	std::list<EnemyBullet*> bullets_;

	int timer = 0;

	
	Player* player_ = nullptr;
};


