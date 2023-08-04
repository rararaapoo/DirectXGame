#include "Player.h"
#include <assert.h>
#include "ImGuiManager.h"

Player::~Player() { 

	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	delete sprite2DReticle_;
}


void Player::Initialize(
    Model* model, uint32_t textureHandle, Vector3 playerPosition/*, uint32_t textureHandleT*/) { 
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	//textureHandle_T = textureHandleT;
	worldTransform_.Initialize();

	input_ = Input::GetInstance();

	worldTransform_.translation_ = playerPosition;
	
	worldTransform3DReticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("target.png");

	sprite2DReticle_ = Sprite::Create(
		textureReticle, {640, 640}, {1, 1, 1, 1}, {0.5f, 0.5f});

}

Vector3 Player::GetWorldPosition()
{ 
	Vector3 worldPos;

	//worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	//worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	//worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::DrawUI() 
{ sprite2DReticle_->Draw(); }



void Player::OnCollision()
{

}

void Player::Update(ViewProjection& viewProjection_) {
	textureHandle_;

	Vector3 move = {0, 0, 0};

	Vector3 offset = {0, 0, 1.0f};

	Vector2 spritePosition = sprite2DReticle_->GetPosition();

	const float kCharacterSpeed = 0.2f;

	const float kRotSpeed = 0.02f;

	const float kDistancePlayerTo3DReticle = 50.0f;

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;

		sprite2DReticle_->SetPosition(spritePosition);
	}



	offset = TransformNormal(offset, worldTransform_.matWorld_);

	offset = Normalize(offset) * kDistancePlayerTo3DReticle;

	worldTransform3DReticle_.translation_.x = GetWorldPosition().x + offset.x;
	worldTransform3DReticle_.translation_.y = GetWorldPosition().y + offset.y;
	worldTransform3DReticle_.translation_.z = GetWorldPosition().z + offset.z;
	worldTransform3DReticle_.UpdateMatrix();

	//Vector3 positionReticle = {	
	//    worldTransform3DReticle_.translation_.x, worldTransform3DReticle_.translation_.y,
	//    worldTransform3DReticle_.translation_.z};
	//
	//Matrix4x4 matViewport =
	//    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	//
	//Matrix4x4 matViewProjectionViewport =
	//    viewProjection_.matView * viewProjection_.matProjection * matViewport;
	//
	//positionReticle = Transform(positionReticle, matViewProjectionViewport);
	//
	//sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
	mouse(viewProjection_);

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}

	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

		Attack();

			const float kMoveLimitX = 30;
	    const float kMoveLimitY = 15;

	    worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	    worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	    worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	    worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.matWorld_ = MakeAffineMetrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	worldTransform_.UpdateMatrix();
	


	ImGui::Begin("player");
	float sliderValue[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("position", sliderValue, 20.0f, 20.0f);
	worldTransform_.translation_ = {sliderValue[0], sliderValue[1], sliderValue[2]};
	ImGui::End();



	for (PlayerBullet* bullet : bullets_) {

		bullet->Update();
	}

	bullets_.remove_if([](PlayerBullet* bullet)
	{
			if (bullet->IsDead())
			{
			   delete bullet;
			    return true;
			}
		    return false;

	 });

}

void Player::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	for (PlayerBullet* bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}

//	model_->Draw(worldTransform3DReticle_, viewProjection_, textureHandle_T);
}

void Player::Attack() 
{

	XINPUT_STATE joyState;

	if (input_->PushKey(DIK_SPACE))
	{
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity.x = worldTransform3DReticle_.translation_.x - worldTransform_.translation_.x;
		velocity.y = worldTransform3DReticle_.translation_.y - worldTransform_.translation_.y;
		velocity.z = worldTransform3DReticle_.translation_.z - worldTransform_.translation_.z;

		//velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		velocity = Normalize(velocity) * kBulletSpeed;
		

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(
		    model_,/* worldTransform_.translation_*/
		            /*worldTransform3DReticle_.translation_*/ GetWorldPosition(),
		    velocity);
		bullets_.push_back(newBullet);
	}	

	if (!Input::GetInstance()->GetJoystickState(0, joyState))
	{
		return;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity.x = worldTransform3DReticle_.translation_.x - worldTransform_.translation_.x;
		velocity.y = worldTransform3DReticle_.translation_.y - worldTransform_.translation_.y;
		velocity.z = worldTransform3DReticle_.translation_.z - worldTransform_.translation_.z;

		// velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		velocity = Normalize(velocity) * kBulletSpeed;

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(
		    model_, /* worldTransform_.translation_*/
		    /*worldTransform3DReticle_.translation_*/ GetWorldPosition(), velocity);
		bullets_.push_back(newBullet);
	}
}

void Player::mouse(ViewProjection& viewProjection_) {
	POINT mousePosition;
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	GetCursorPos(&mousePosition);

	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	sprite2DReticle_->SetPosition(Vector2(float(mousePosition.x), float(mousePosition.y)));

	Matrix4x4 matVPV = viewProjection_.matView * viewProjection_.matProjection * matViewport;

	Matrix4x4 matInverseVPV = Inverse(matVPV);

	Vector3 posNear = Vector3(float(mousePosition.x), float(mousePosition.y), 0);
	Vector3 posFar = Vector3(float(mousePosition.x), float(mousePosition.y), 1);

	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	Vector3 mouseDirection = {posFar.x - posNear.x, posFar.y - posNear.y, posFar.z - posNear.z};
	mouseDirection = Normalize(mouseDirection);

	const float kDistanceTestObject = 150.0f;

	worldTransform3DReticle_.translation_.x = posNear.x + mouseDirection.x * kDistanceTestObject;
	worldTransform3DReticle_.translation_.y = posNear.y + mouseDirection.y * kDistanceTestObject;
	worldTransform3DReticle_.translation_.z = posNear.z + mouseDirection.z * kDistanceTestObject;
	worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("Player");
	//ImGui::Text("2DReticle:(%f,%f)", spritePosition.x, spritePosition.y);
	ImGui::Text("Near:(%+.2f, %+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f, %+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DReticle:(%+.2f, %+.2f,%+.2f)", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();
}
