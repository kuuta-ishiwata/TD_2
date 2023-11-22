﻿#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Skydome {


	public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewprojection_);

private:
	// ワールド変換データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;



};
