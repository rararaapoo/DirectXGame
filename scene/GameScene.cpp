#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_;
	delete player_;
	delete debugCamera_;
	for (Enemy* enemy : enemy_) {
		delete enemy;
	}
	
	delete modelSkydome_;
	delete railCamera_;

	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
}



void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("sample.png");

	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	viewProjection_.Initialize();

	player_ = new Player();
	//enemy_ = new Enemy();
	skydome_ = new Skydome();	

	//Vector3 playerPosition(0, 0, 10);
	player_->Initialize(model_, textureHandle_, {0.0f, -5.0f, 15.f});
	//enemy_->Initialize(model_, textureHandle_);
	//enemy_->SetGameScene(this);
	skydome_->Initialize(modelSkydome_, textureHandle_);

	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
	
	railCamera_ = new RailCamera();
	railCamera_->Initialize(viewProjection_.translation_, viewProjection_.rotation_);

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//enemy_->SetPlayer(player_);
	player_->SetParent(&railCamera_->GetWorldTransform());
	AddEnemy({0.5f, 5.0f, 30.0f});
}



void GameScene::Update() {

	player_->Update();
	debugCamera_->Update();
	//enemy_->Update();
	skydome_->Update();
	//railCamera_->Update();

	CheckAllCollisions();

	for (Enemy* enemy : enemy_)
	{
		enemy->Update();
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});


	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0))
	{
		isDebugCameraActive_ = true;
	}


	if (isDebugCameraActive_)
	{	
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

	else
	{
		viewProjection_.UpdateMatrix();
	}

	#endif

		if (isRailCameraActive_) {

		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
}


void GameScene::CheckAllCollisions()
{ 
	Vector3 posA;
	Vector3 posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemyBullets_; /*enemy_->GetBullets();*/

	#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets_) {
		posB = bullet->GetWorldPosition();

		/*
		Vector3 posR;
		posR.x = posB.x - posA.x;
		posR.y = posB.y - posA.y;
		posR.z = posB.z - posA.z;*/
		
		float distance = sqrtf(
		    (posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y) +
		    (posA.z - posB.z) * (posA.z - posB.z));
		/*
		Vector3 distanceV;

		distanceV.x = (posR.x * posR.x);
		distanceV.y =(posR.y * posR.y);
		distanceV.z = (posR.z * posR.z);
		if (distanceV.x + distanceV.y + distanceV.z <= 2.0f)
		{
			player_->OnCollision();
			bullet->OnCollision();
		}*/

		if (distance <= 2.0f) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	
		

	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定
	
	for (Enemy* enemy : enemy_)
	{
		posA = enemy->GetWorldPosition();

		for (PlayerBullet* bullet : playerBullets) {
			posB = bullet->GetWorldPosition();

			/*
			Vector3 posR;
			posR.x = posB.x - posA.x;
			posR.y = posB.y - posA.y;
			posR.z = posB.z - posA.z;*/

			float distance = sqrtf(
			    (posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y) +
			    (posA.z - posB.z) * (posA.z - posB.z));
			/*
			Vector3 distanceV;

			distanceV.x = (posR.x * posR.x);
			distanceV.y =(posR.y * posR.y);
			distanceV.z = (posR.z * posR.z);
			if (distanceV.x + distanceV.y + distanceV.z <= 2.0f)
			{
			    player_->OnCollision();
			    bullet->OnCollision();
			}*/

			if (distance <= 2.0f) {
				enemy->OnCollision();
				bullet->OnCollision();
			}
	}
	
	}
	

	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定


	for (EnemyBullet* bulletE : enemyBullets_) 
	{
		posA = bulletE->GetWorldPosition();

		for (PlayerBullet* bulletP : playerBullets) {
			posB = bulletP->GetWorldPosition();

			/*
			Vector3 posR;
			posR.x = posB.x - posA.x;
			posR.y = posB.y - posA.y;
			posR.z = posB.z - posA.z;*/

			float distance = sqrtf(
			    (posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y) +
			    (posA.z - posB.z) * (posA.z - posB.z));
			/*
			Vector3 distanceV;

			distanceV.x = (posR.x * posR.x);
			distanceV.y =(posR.y * posR.y);
			distanceV.z = (posR.z * posR.z);
			if (distanceV.x + distanceV.y + distanceV.z <= 2.0f)
			{
			    player_->OnCollision();
			    bullet->OnCollision();
			}*/

			if (distance <= 2.0f) {
				bulletE->OnCollision();
				bulletP->OnCollision();
			}
		}
	}

	#pragma endregion
}

void GameScene::AddEnemy(Vector3 pos) {
	Enemy* obj = new Enemy();

	const float kSpeed = 0.0f;

	Vector3 velocity{kSpeed, kSpeed, kSpeed};

	obj->Initialize(model_, textureHandle_, velocity, pos);
	obj->SetGameScene(this);
	obj->SetPlayer(player_);
	enemy_.push_back(obj);
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <s	ummary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	player_->Draw(viewProjection_);
	for (Enemy* enemy : enemy_) {
		enemy->Draw(viewProjection_);
	}
	
	skydome_->Draw(viewProjection_);

	

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


