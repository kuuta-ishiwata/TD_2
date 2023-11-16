#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "AxisIndicator.h"
#include "Player.h"
#include "MATHEX.h"
#include "Box.h"
#include "Skydome.h"
#include "FollowCamera.h"
#include <sstream>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void LoadBoxPopData();

	void UpdateBoxPopCommands();

	void BoxObjUpdate();

	void BoxObjDraw();

    void CheckAllCollisions();

  

private:

	// メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	DebugCamera* debugcamera_ = nullptr;

	ViewProjection viewprojection_;
	WorldTransform worldtransform_;


	uint32_t TextureHandle = 0;
	uint32_t BoxTextureHandle = 0;

	Model* model_ = nullptr;

	
	Player* player_ = nullptr;
	Box* box_ = nullptr;


	Vector3 Positon = {0.0f,0.0f,0.0f};
	Vector3 Boxposiiton = {0.0f, 0.0f, 0.0f};
	
	
	float inputFloat3[3] = {0, 0, 0};

	bool isDebugCameraActive_ = false;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	

	//skydome
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	//followcamera
	//  カメラ

	std::unique_ptr<FollowCamera> followCamera_;

	std::stringstream BoxPopCommands;

	std::list<Box*> boxs_;

	
	void BoxSpawn();
	Vector3 Boxpositions_{5.0f, 0.0f, 5.0f};

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
