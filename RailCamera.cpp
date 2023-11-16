#include "RailCamera.h"
#include "ViewProjection.h"
#include "ImGuiManager.h"
#include "MATHEX.h"

// 初期化
void RailCamera::Initialize() {

	// 初期設定
	worldtransform_.translation_.z = -10;
	// ワールドトランスフォームの初期化
	worldtransform_.Initialize();

	// ビュープロジェクションの初期化
	// Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	viewProjection_.Initialize();
	viewProjection_.farZ = 3000.0f;
}

// 更新
void RailCamera::Update() {
	
	// ワールドトランスフォームのワールド行列再計算
	worldtransform_.UpdateMatrix();

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldtransform_.matWorld_);

	viewProjection_.UpdateMatrix();
	
}
