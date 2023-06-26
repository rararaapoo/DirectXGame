#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include <iostream>
#include "PlayerBullet.h"
#include <list>
#include "Matrix4x4.h"
#include "Material.h"

class Player {

	public:

		~Player();

		void Initialize(Model* model, uint32_t textureHandle);

		void Update();

		void Draw(ViewProjection& viewProjection_);

		void Attack();

		

	private:
	    WorldTransform worldTransform_;

		Model* model_ = nullptr;

		uint32_t textureHandle_ = 0u;

		Input* input_ = nullptr;

	    std::list<PlayerBullet*> bullets_;

};
