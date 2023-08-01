#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include <iostream>
#include "PlayerBullet.h"
#include <list>
#include "Matrix4x4.h"
#include "Material.h"
#include "Sprite.h"
#include "ViewProjection.h"

class Player {

	public:

		~Player();

		void Initialize(
	        Model* model, uint32_t textureHandle, Vector3 playerPosition/*, uint32_t textureHandleT*/);

		void Update(ViewProjection& viewProjection_);

		void Draw(ViewProjection& viewProjection_);

		void Attack();

		Vector3 GetWorldPosition();

		void OnCollision();

		const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

		void SetParent(const WorldTransform* parent);

		void DrawUI();
			
	private:
	    WorldTransform worldTransform_;

		Model* model_ = nullptr;

		uint32_t textureHandle_ = 0u;
	    uint32_t textureHandle_T = 0u;
		Input* input_ = nullptr;

	    std::list<PlayerBullet*> bullets_;
	  
		Sprite* sprite2DReticle_ = nullptr;
	    //ViewProjection viewProjection_T;
		WorldTransform worldTransform3DReticle_;

};
