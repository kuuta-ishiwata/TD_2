#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "Player.h"
#include "Box.h"
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete model_;
	delete modelSkydome_;
	delete debugcamera_;
	delete Stage_;
	delete StageModel_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	TextureHandle = TextureManager::Load("ga.png");
	BoxTextureHandle = TextureManager::Load("sample.png");
	JumpTextureHnadle = TextureManager::Load("ga.png");

	debugcamera_ = new DebugCamera(1280, 720);
	debugcamera_->SetFarZ(1400.0f);

	worldtransform_.Initialize();
	viewprojection_.Initialize();


	model_ = Model::Create();


	player_ = new Player();

	box_ = new Box();

	jump_ = new Jump();

	player_->Initialize(model_, TextureHandle,{20.0f,0.0f,0.0f});
	box_->Initialize(model_, BoxTextureHandle, {0.0f,0.0f,0.0f});
	jump_->Initialize(model_, JumpTextureHnadle, { 5.0f, -20.0f, 10.0f });

	//天球
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);

	viewprojection_.farZ = 1400.0f;


	// カメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());




#pragma region ステージ関係

	// ステージ
	StageTextureHandle_ = TextureManager::Load("black.png");
	StageModel_ = Model::Create();

	// 青ブロックのテクスチャ
	BlueStageTextureHandle_ = TextureManager::Load("blue.png");
	BlueStageModel_ = Model::Create();

#pragma endregion

#pragma region ブロック初期化
	// 黒ブロック
	Stage_ = new MapChip();
	Stage_->Initialize(StageModel_, StageTextureHandle_, BlueStageModel_, BlueStageTextureHandle_);

#pragma endregion


	LoadBoxPopData();

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewprojection_);


}


void GameScene::CheckAllCollisions()
{

	Vector3 PlayerPosition_, BoxPosition_;
	

	PlayerPosition_ = player_->GetWorldPosition();

	for (Box* BOXS : boxs_)
	{
		BoxPosition_ = BOXS->GetWorldPosition();

		float radius = 0.5f;

		float px;
		float py;
		float pz;
		float distance;

		px = (BoxPosition_.x - PlayerPosition_.x) * (BoxPosition_.x - PlayerPosition_.x);
		py = (BoxPosition_.y - PlayerPosition_.y) * (BoxPosition_.y - PlayerPosition_.y);
		pz = (BoxPosition_.z - PlayerPosition_.z) * (BoxPosition_.z - PlayerPosition_.z);

		distance = px + py + pz;

		if (distance <= (radius * radius) + (radius * radius))
		{

			BOXS->OnCollision();
			player_->OnCollision();

		}
	}



	Vector3 JumpPosition_;
	
	JumpPosition_ = jump_->GetWorldPosition();


	float Radius = 0.5f;
	float Jpx;
	float Jpy;
	float Jpz;
	float distansposiiton;


	Jpx = (JumpPosition_.x - PlayerPosition_.x) * (JumpPosition_.x - PlayerPosition_.x);
	Jpy = (JumpPosition_.y - PlayerPosition_.y) * (JumpPosition_.y - PlayerPosition_.y);
	Jpz = (JumpPosition_.z - PlayerPosition_.z) * (JumpPosition_.z - PlayerPosition_.z);

	distansposiiton = Jpx + Jpy + Jpz;

	if (distansposiiton <= (Radius * Radius) + (Radius * Radius))
	{
		player_->JumpOnCollision();

	}

}


void GameScene::Update() {

	

	CheckAllCollisions();
#ifdef _DEBUG

	if (input_->TriggerKey(DIK_M)) {
		isDebugCameraActive_ = true;
	}

#endif 
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewprojection_.matView = debugCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewprojection_.TransferMatrix();


	} else {
		followCamera_->Update();
		viewprojection_.matView = followCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewprojection_.TransferMatrix();
		// ビュープロジェクション行列の更新と転送
		//viewprojection_.UpdateMatrix();
	}
	player_->Update();

	box_->Update();


	jump_->Update();
	// 天球
	skydome_->Update();

	Stage_->Update();



	BoxObjUpdate();
	UpdateBoxPopCommands();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewprojection_);
	
	jump_->Draw(viewprojection_);

	skydome_->Draw(viewprojection_);

	//box_->Draw(viewprojection_);

	// ステージ
	Stage_->Draw(viewprojection_);


	BoxObjDraw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::BoxSpawn() {

	Box* BOX_ = new Box;

	uint32_t tex = TextureManager::Load("sample.png");

	BOX_->Initialize(model_, tex, Boxpositions_);

	box_->SetPlayer(player_);

	box_->SetGameScene(this);

	boxs_.push_back(BOX_);


}



void GameScene::BoxObjUpdate()
{

	for (Box* BOX : boxs_) {

		BOX->Update();
	}

}


void GameScene::BoxObjDraw() {

	for (Box* BOX : boxs_) {

		BOX->Draw(viewprojection_);
	}
}

void GameScene::LoadBoxPopData() {

	std::ifstream file;
	file.open("Resources/BoxPop.csv");
	assert(file.is_open());

	BoxPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateBoxPopCommands() {

	std::string line;

	while (getline(BoxPopCommands, line)) {

		std::istringstream line_stream(line);

		std::string word;

		if (word.find("//") == 0) {
			continue;
		}
		getline(line_stream, word, ',');

		if (word.find("Pop") == 0) {

			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			Boxpositions_ = {x, y, z};

			BoxSpawn();
		}
	}
}
