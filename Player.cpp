#include "Player.h"
#include <assert.h>
#include <ImGuiManager.h>
#include "Input.h"
#include <Xinput.h>
#include "MATHEX.h"

Player::Player() {}
Player::~Player() {}



Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}


void Player::Initialize(Model* model, uint32_t textureHandle,Vector3 Posiotn)
{ 
	assert(model);
	model_ = model;

	TextureHandle = textureHandle;
	
	

	worldtransform_.Initialize();
	input_ = Input::GetInstance();
	worldtransform_.translation_ = Posiotn;

	
}


void Player::Update() 
{
	Vector3 move = {0, 0, 0};

	
	//const float Grabity = 0.5f; 
	// 押した方向で移動ベクトルを変更
	
		
    if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed.x;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed.x;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed.x;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed.x;
	}


	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 速さ
		Vector3 speed = {0.2f,0.2f,0.2f};

		//(float)joyState.Gamepad.bRightTrigger

		// 移動量
		move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed.x, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed.x};

		Normalize(move);
		Multiply2(move, speed);
		
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{

			worldtransform_.translation_.y += acceleration.x;

		}
		

		worldtransform_.translation_ = Add(worldtransform_.translation_, move);

	}
	
	worldtransform_.translation_ = Add(worldtransform_.translation_, move);


	worldtransform_.UpdateMatrix();



}

void Player::OnCollision()
{
	
	

		worldtransform_.translation_.y -= acceleration.y;
	

	if (worldtransform_.translation_.y <= -20) 
	{
		flag = false;
	}

}

void Player::Draw(ViewProjection& viewprojection) 
{

	model_->Draw(worldtransform_, viewprojection, TextureHandle);

}
