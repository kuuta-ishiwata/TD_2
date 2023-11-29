#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include <assert.h>
#include <Input.h>
#include "MATHEX.h"
#include <list>
#include "Player.h"



class Jump {


	public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 JumpPositon);

	void Update();

	void Draw(ViewProjection& viewprojection);

	
   
	Vector3 GetWorldPosition();

	void OnCollision2();

	private:
	
		Model* model_ = nullptr;
	    Input* input_ = nullptr;
	    WorldTransform worldtransform_;
	    ViewProjection viewprojection_;

	   uint32_t JumpTextureHandle = 0;

	   	//GameScene* gameScene_ = nullptr;
	    Player* player_ = nullptr;



};
