#pragma once
#include "KamataEngine.h"

/// <summary>
/// 天球
/// </summary>
class Skydome {
private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// スカイドームモデル
	uint32_t TextureHandle_ = 0;
	KamataEngine::Model* model_ = nullptr;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// /// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};