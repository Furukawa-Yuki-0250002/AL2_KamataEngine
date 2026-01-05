#pragma once
#include "KamataEngine.h"
#include "Easing.h"
#include <algorithm>

class Player;

class CameraController
{
private:
	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// ターゲット
	Player* target_ = nullptr;

	// 追従対象とカメラの座標の差(オフセット)
	KamataEngine::Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};

	// 矩形
	struct CameraRect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	CameraRect movableArea_ = {0.0f, 100.0f, 0.0f, 100.0f};

	// カメラの目標座標
	KamataEngine::Vector3 destination_;

	// 追従対象の各方向へのカメラ移動範囲
	static inline const CameraRect margin_ = {-10.0f, 10.0f, -10.0f, 10.0f};

	// 座標補間割合
	static inline const float kInterpolationRate = 0.5f;

	// 速度掛け率
	static inline const float kVelocityBias = 7.5f;


public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Camera *camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void SetTarget(Player* target) { target_ = target; };

	void Reset();

	void SetMovableArea(CameraRect area) { movableArea_ = area; };
};
