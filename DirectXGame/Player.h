#pragma once
#include "KamataEngine.h"
#include "WorldTransformUpdater.h"
#include "Easing.h"
#include <numbers>
#include <algorithm>

// 左右
enum class LRDirection {
	kRight,
	kLeft,
};

///< summary>
/// 自キャラ
/// </summary>
class Player {
private:
	//ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 移動用変数
	KamataEngine::Vector3 velocity_ = {};
	static inline const float kAcceleration = 0.05f;
	static inline const float kLimitRunSpeed = 0.5f;
	static inline const float kAttenuation = 0.95f;

	// ジャンプ用変数
	bool onGround_ = true; // 接地状態フラグ
	static inline const float kGravityAcceleration = 0.1f; // 重力加速度(下方向)
	static inline const float kLimitFallSpeed = 7.0f; // 最大落下速度(下方向)
	static inline const float kJumpAcceleration = 1.5f; // ジャンプ初速(上方向)

	// 向いている方向(左右)
	LRDirection lrDirection_ = LRDirection::kRight;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

public:
	// デストラクタ
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	/// <param name="camera">カメラ</param>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; };
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; };
};