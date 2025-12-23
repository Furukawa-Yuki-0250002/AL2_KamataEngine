#include "GameScene.h"

using namespace KamataEngine;

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
};


void GameScene::Initialize() {
	// カメラの初期化
	camera_.Initialize();

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// プレイヤーのテクスチャ・モデル
	playerTextureHandle_ = TextureManager::Load("images/mario.png");
	playerModel_ = Model::Create();

	// ブロックのテクスチャ・モデル
	blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");
	blockModel_ = Model::Create();

	//=================
	// ブロックの生成
	//=================
	// 要素数
	const uint32_t kNumBlockVertical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if ((i + j) % 2 == 1) {
				continue;
			}

			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		}
	}


	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(playerModel_, playerTextureHandle_, &camera_);
};

void GameScene::Update() {
	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isDebugCametaActive_ = !isDebugCametaActive_;
	}
	#endif

	// カメラの処理
	if (isDebugCametaActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetViewMatrix();
		camera_.matProjection = debugCamera_->GetProjectionMatrix();
		camera_.TransferMatrix();

	} else {
		camera_.UpdateMatrix();
	}

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			
			// アフィン変換行列の作成
			Matrix4x4 affineMatrix = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			// ワールド行列に代入
			worldTransformBlock->matWorld_ = affineMatrix;

			// 定数バッファへ転送
			worldTransformBlock->TransferMatrix();
		}
	}

	// 自キャラの更新
	player_->Update();
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
	//player_->Draw();

	Model::PostDraw();
};