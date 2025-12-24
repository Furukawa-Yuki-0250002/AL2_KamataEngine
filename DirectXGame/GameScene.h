#pragma once
#include "KamataEngine.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Skydome.h"
#include "WorldTransformUpdater.h"

//ゲームシーン
class GameScene {
private:
	// カメラ
	KamataEngine::Camera camera_;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	//=================
	// プレイヤー
	//=================
	Player* player_ = nullptr;
	// モデル・テクスチャ
	uint32_t playerTextureHandle_ = 0;
	KamataEngine::Model* playerModel_ = nullptr;

	// ブロックのモデル・テクスチャ
	uint32_t blockTextureHandle_ = 0;
	KamataEngine::Model* blockModel_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	//=================
	// 天球
	//=================
	std::unique_ptr<Skydome> skydome_;
	// モデル・テクスチャ
	KamataEngine::Model* skydomeModel_ = nullptr;

public:
	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();
};