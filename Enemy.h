#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Matrix4x4.h"
#include <list>
#include "EnemyBullet.h"

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


private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;
	
	std::list<EnemyBullet*> bullets_;

	int timer = 0;
};


