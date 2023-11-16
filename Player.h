#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>
#include "MATHEX.h"
#include "Model.h"


class Player {

public:
   
	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldtransform_; }

	void SetViewProjection(const ViewProjection* viewprojection) {
		viewprojection_ = viewprojection;
	}

	Player();
	~Player();


	 void Initialize(Model* model, uint32_t textureHandle,Vector3 Posiiton);

	 void Update();

	 void Draw(ViewProjection& viewprojection);
	 
	 Vector3 PlayerSpeed() { return kCharacterSpeed; }
	 Vector3 Playermove() { return moves; } 
  
	 void OnCollision();


private:

	WorldTransform worldtransform_;
	const ViewProjection* viewprojection_ = nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	Vector3 acceleration = {0.8f, 20.0f, 0.5f};

	uint32_t TextureHandle = 0;
	Vector3 kCharacterSpeed = {0.1f, 0.1f, 0.1f};
	Vector3 moves = {0.0f, 0.0f, 0.0f};
	bool flag = true;



};
