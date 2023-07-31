#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();

	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void AddEnemy(Vector3 pos);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;

	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;

	ViewProjection viewProjection_;

	Player* player_ = nullptr;
	//Enemy* enemy_ = nullptr;
	Skydome* skydome_ = nullptr;

	bool isDebugCameraActive_ = false;
	bool isRailCameraActive_ = true;

	DebugCamera* debugCamera_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	std::list<EnemyBullet*> bullets_;
	std::list<Enemy*> enemy_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
