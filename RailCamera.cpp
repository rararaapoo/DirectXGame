#include "RailCamera.h"


void RailCamera::Initialize(Vector3 move, Vector3 rot) 
{
	worldTransform_.Initialize();
	worldTransform_.translation_ = move;
	worldTransform_.rotation_ = rot;

	viewProjection_.Initialize();
}

void RailCamera::Update() 
{ 
	Vector3 move{0.0f, 0.0f, -0.05f};
	Vector3 rot{0.0f, 0.0f, 0.0f};

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.rotation_.x += rot.x;
	worldTransform_.rotation_.y += rot.y;
	worldTransform_.rotation_.z += rot.z;

	worldTransform_.UpdateMatrix();
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);


	
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("camera.translation", &viewProjection_.translation_.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("camera.rotation_", &viewProjection_.rotation_.x, 0.0f, 1.0f);


	ImGui::End();
}