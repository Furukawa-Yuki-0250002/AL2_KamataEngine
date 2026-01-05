#pragma once
#include "KamataEngine.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Skydome.h"
#include "WorldTransformUpdater.h"
#include "MapChipField.h"
#include "CameraController.h"

//ゲームシーン
class GameScene {
private:
	//float WIN_WIDTH_HALF = 640.0f;
	//float WIN_HEIGHT_HALF = 320.0f;

	// カメラ
	KamataEngine::Camera camera_;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// 追従カメラ
	CameraController* cameraController_ = nullptr;

	//=================
	// プレイヤー
	//=================
	Player* player_ = nullptr;
	// モデル・テクスチャ
	KamataEngine::Model* playerModel_ = nullptr;

	//=================
	// ブロック
	//=================
	// モデル・テクスチャ
	KamataEngine::Model* blockModel_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	//=================
	// 天球
	//=================
	std::unique_ptr<Skydome> skydome_;
	// モデル・テクスチャ
	KamataEngine::Model* skydomeModel_ = nullptr;

	//=================
	// マップチップフィールド
	//=================
	MapChipField* mapChipField_;

	void GenerateBlocks();

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