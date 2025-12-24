#include "Player.h"

using namespace KamataEngine;

Player::~Player() {};

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {
	// NULLポインタチェック
	assert(model);
	
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	// カメラのセット
	camera_ = camera;
}

void Player::Update() {
	// ワールドトランスフォームの更新
	WorldTransformUpdate(worldTransform_);
}

void Player::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}