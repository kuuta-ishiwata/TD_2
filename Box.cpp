#include "Box.h"
#include <assert.h>
#include <ImGuiManager.h>
#define _USE_MATH_DEFINES
#include "GameScene.h"



Vector3 Box::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}


void Box::Initialize(Model* model, uint32_t textureHandle,Vector3 BoxPositon)
{

	assert(model);
	model_ = model;
	worldtransform_.Initialize();

	BoxTextureHandle = textureHandle;
	worldtransform_.translation_ = BoxPositon;
	
	

}

void Box::Update() 
{
	

	worldtransform_.UpdateMatrix();


}



void Box::OnCollision() 
{ 

      worldtransform_.translation_ .x+= move.x;

}

void Box::OnCollision2()
{ worldtransform_.translation_.x -= move.x; }


void Box::Draw(ViewProjection& viewprojection) 
{


	
		model_->Draw(worldtransform_, viewprojection, BoxTextureHandle);
	

}
