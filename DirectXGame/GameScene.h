#pragma once
#include "KamataEngine.h"
#include <stdint.h>
#include <vector>
#include "Player.h"

//ゲームシーン
class GameScene {
private:
	// カメラ
	KamataEngine::Camera camera_;

	// デバッグカメラ
	bool isDebugCametaActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// プレイヤーのモデル・テクスチャ
	uint32_t playerTextureHandle_ = 0;
	KamataEngine::Model* playerModel_ = nullptr;

	// ブロックのモデル・テクスチャ
	uint32_t blockTextureHandle_ = 0;
	KamataEngine::Model* blockModel_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	// 自キャラ
	Player* player_ = nullptr;

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