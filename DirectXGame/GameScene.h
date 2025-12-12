#pragma once
#include "KamataEngine.h"
#include <stdint.h>

//ゲームシーン
class GameScene 
{
private:
	//ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	//カメラ
	KamataEngine::Camera camera_;

	//デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// リソース
	uint32_t textureHandle_ = 0;
	//KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;

	//サウンド
	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;

	// ImGui用変数
	float inputFloat3[3] = {0, 0, 0};

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