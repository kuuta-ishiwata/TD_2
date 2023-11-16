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


class GameScene;


class Box {

public:

	void Initialize(Model* model, uint32_t textureHandle, Vector3 BoxPositon);

	void Update();

	void Draw(ViewProjection& viewprojection);

	
	void OnCollision();

	
	bool IsDead() const { return isDead_; }
	

	Vector3 GetWorldPosition();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void SetPlayer(Player* player) { player_ = player; }
	

private:


	Model* model_ = nullptr;
	Input* input_ = nullptr;
	WorldTransform worldtransform_;
	ViewProjection viewprojection_;

	GameScene* gameScene_ = nullptr;
	Player* player_ = nullptr;
	Box* box__ = nullptr;
	

	// デスフラグ
	bool isDead_ = false;
	

	uint32_t BoxTextureHandle = 0;

   // std::list<Box*> boies_;


};
