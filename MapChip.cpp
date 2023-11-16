#include "MapChip.h"

#include <cassert>

    void
    MapChip::Initialize(
        Model* model, uint32_t textureHandle, Model* Bluemodel, uint32_t BluetextureHandle) {
	assert(model);

	StageModel_ = model;
	StageHandle_ = textureHandle;

	BlueStageModel_ = Bluemodel;
	BlueStageHandle_ = BluetextureHandle;

	// 仮、vectorに追加するやり方これ真似て配置するやつだけ計算したワールドトランスフォームを追加していく
	// これができれば3次元配列のワールドトランフォームは消える
	// WorldTransform test;
	// test.Initialize();
	// worldTransforms_.push_back(test/*ここにワールドトランスフォームの実体を各);

	// push_back呼ぶたびに配列の要素数が増えてるイメージ
	// マップ初期化
	for (int y = 0; y < MAP_ROW_MAX; y++) {
		for (int z = 0; z < MAP_DEPTH_MAX; z++) {
			for (int x = 0; x < MAP_COLUMN_MAX; x++) {
				// 無駄に計算しているのでifでmap状に配置する奴だけチェックする
				// 用は値が1のやつが配置(描画)するやつ

				// ワールドトランスフォーム
				// 描画するやつ確認
				if (map[y][z][x] == 1 || map[y][z][x] == 2) {
					WorldTransform mapWorld;
					// 描画するやつだけ初期化
					mapWorld.Initialize();

					mapWorld.translation_.x = (float)x * 2;
					mapWorld.translation_.y = (float)y * 2;
					mapWorld.translation_.z = (float)z * 2;

					// push_backで追加
					worldTransforms_.push_back(mapWorld);

					blockTypes_.push_back(map[y][z][x]);
				}
			}
		}
	}
}

void MapChip::Update() {

	for (WorldTransform worldTransform : worldTransforms_) 
	{
		worldTransform.UpdateMatrix();
	}
}

void MapChip::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < worldTransforms_.size(); i++) {
		// worldTransforms_[i]

		if (blockTypes_[i] == 1) {
			StageModel_->Draw(worldTransforms_[i], viewProjection, StageHandle_);
		}

		if (blockTypes_[i] == 2) {
			BlueStageModel_->Draw(worldTransforms_[i], viewProjection, BlueStageHandle_);
		}
	}
}