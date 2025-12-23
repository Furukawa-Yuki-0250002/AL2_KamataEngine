#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	delete model_;
	delete player_;
};


void GameScene::Initialize() {
	// カメラの初期化
	camera_.Initialize();

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	// テクスチャ・モデル
	textureHandle_ = TextureManager::Load("images/mario.png");
	model_ = Model::Create();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_, &camera_);
};

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
};

void GameScene::Draw() {
	Model::PreDraw();

	// 自キャラの描画
	player_->Draw();

	Model::PostDraw();
};