#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Matrix4x4.h"
#include <list>
#include "EnemyBullet.h"
#include "Player.h"

class Player;
class GameScene;

enum class Phase
{
	Approach,
	Leave,
};

class Enemy 
{
public:
	~Enemy();
	void Initialize(Model* model, uint32_t textureHandle, Vector3& velocity, Vector3& position);

	void Update();

	void Draw(ViewProjection& viewProjection_);

	void Fire();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	void OnCollision();

	//const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Phase phase_ = Phase::Approach;

	bool isDead_ = false;
	
	//std::list<EnemyBullet*> bullets_;

	int timer = 0;
	Vector3 velocity_;

	GameScene* gameScene_ = nullptr;
	
	Player* player_ = nullptr;
};


