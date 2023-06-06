#include "Player.h"
#include <assert.h>
#include "ImGuiManager.h"

void Player::Initialize(Model* model, uint32_t textureHandle) 
{ 
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();

}

void Player::Update() 
{ 
	textureHandle_;

	Vector3 move = {0, 0, 0};



	const float kCharacterSpeed = 0.2f;


	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_RIGHT))
	{
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) 
	{
		move.y += kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_DOWN)) 
	{
		move.y -= kCharacterSpeed;
	}
	
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.matWorld_ = MakeAffineMetrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	worldTransform_.TransferMatrix();


	ImGui::Begin("player");
	float sliderValue[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("position", sliderValue, 20.0f, 20.0f);
	worldTransform_.translation_ = {sliderValue[0], sliderValue[1], sliderValue[2]};
	ImGui::End();

	const float kMoveLimitX = 30;
	const float kMoveLimitY = 15;


	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}