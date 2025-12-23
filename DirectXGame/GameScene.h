#pragma once
#include "KamataEngine.h"
#include <stdint.h>
#include "Player.h"

//ゲームシーン
class GameScene 
{
private:
	//カメラ
	KamataEngine::Camera camera_;

	// リソース
	uint32_t textureHandle_ = 0;
	KamataEngine::Model* model_ = nullptr;

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