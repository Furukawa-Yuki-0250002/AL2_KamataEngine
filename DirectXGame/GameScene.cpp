#include "GameScene.h"

using namespace KamataEngine;

void GameScene::GenerateBlocks() {
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(numBlockHorizontal);
	for (uint32_t i = 0; i < numBlockHorizontal; ++i) {
		// 1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(numBlockVirtical);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++) {
		for (uint32_t j = 0; j < numBlockHorizontal; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[j][i] = worldTransform;
				worldTransformBlocks_[j][i]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

}


GameScene::~GameScene() {
	delete debugCamera_;

	delete playerModel_;
	delete player_;
	delete blockModel_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete mapChipField_;
};


void GameScene::Initialize() {
	// カメラの初期化
	camera_.farZ = 800.0f;
	camera_.Initialize();

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//=================
	// プレイヤー
	//=================
	// テクスチャ・モデル
	playerTextureHandle_ = TextureManager::Load("images/mario.png");
	playerModel_ = Model::Create();
	// 生成
	player_ = new Player();
	// 初期化
	player_->Initialize(playerModel_, playerTextureHandle_, &camera_);

	//=================
	// マップチップフィールド
	//=================
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/AL2_05_04_mapData.csv");

	GenerateBlocks();

	//=================
	// ブロック
	//=================
	// テクスチャ・モデル
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");
	blockModel_ = Model::Create();

	//=================
	// 天球
	//=================
	// モデル
	skydomeModel_ = Model::CreateFromOBJ("skydome", true);
	// 生成
	skydome_ = std::make_unique<Skydome>();
	// 初期化
	skydome_->Initialize(skydomeModel_, &camera_);
};

void GameScene::Update() {
	// カメラの処理
	debugCamera_->Update();
	camera_.matView = debugCamera_->GetViewMatrix();
	camera_.matProjection = debugCamera_->GetProjectionMatrix();
	camera_.TransferMatrix();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			
			// ワールドトランスフォームの更新
			WorldTransformUpdate(*worldTransformBlock);
		}
	}

	// 自キャラの更新
	player_->Update();

	// 天球の更新
	skydome_->Update();
};

void GameScene::Draw() {
	Model::PreDraw();

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			blockModel_->Draw(*worldTransformBlock, camera_);
		}
	}

	// 自キャラの描画
	player_->Draw();

	// 天球の描画
	skydome_->Draw();

	Model::PostDraw();
};