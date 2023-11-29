#include "Jump.h"
#include <assert.h>
#include <ImGuiManager.h>
#define _USE_MATH_DEFINES
#include "GameScene.h"


Vector3 Jump::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}


void Jump::Initialize(Model* model, uint32_t textureHandle, Vector3 JumpPositon)
{
	assert(model);
	model_ = model;
	worldtransform_.Initialize();

	JumpTextureHandle = textureHandle;
	worldtransform_.translation_ = JumpPositon;

}


void Jump::Update()
{


	worldtransform_.UpdateMatrix();

}

void ::Jump::OnCollision2()
{
	worldtransform_.translation_.y -= 10;

}

void Jump::Draw(ViewProjection& viewprojection) 
{
	model_->Draw(worldtransform_, viewprojection, JumpTextureHandle);


}