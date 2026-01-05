#include "CameraController.h"
#include "Player.h"

void CameraController::Initialize(KamataEngine::Camera* camera) {
	camera_=camera;
}

void CameraController::Update() {
	// 追従対象のワールドトランスフォームを参照
	const KamataEngine::WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	const KamataEngine::Vector3& targetVelocity = target_->GetVelocity();

	// 追従対象とオフセットと追従対象の速度からカメラの目標座標を計算
	destination_.x = targetWorldTransform.translation_.x + targetOffset_.x + targetVelocity.x * kVelocityBias;
	destination_.y = targetWorldTransform.translation_.y + targetOffset_.y + targetVelocity.y * kVelocityBias;
	destination_.z = targetWorldTransform.translation_.z + targetOffset_.z + targetVelocity.z * kVelocityBias;


	// 目標座標への補間
	camera_->translation_.x = Easing::Lerp(camera_->translation_.x, destination_.x, kInterpolationRate);
	camera_->translation_.y = Easing::Lerp(camera_->translation_.y, destination_.y, kInterpolationRate);
	camera_->translation_.z = Easing::Lerp(camera_->translation_.z, destination_.z, kInterpolationRate);
	
	// 追従対象が画面外に出ないように修正
	camera_->translation_.x = max(camera_->translation_.x, targetWorldTransform.translation_.x + margin_.left);
	camera_->translation_.x = min(camera_->translation_.x, targetWorldTransform.translation_.x + margin_.right);
	camera_->translation_.y = max(camera_->translation_.y, targetWorldTransform.translation_.y + margin_.bottom);
	camera_->translation_.y = min(camera_->translation_.y, targetWorldTransform.translation_.y + margin_.top);

	// 移動範囲制限
	camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);

	// 行列を更新する
	camera_->UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const KamataEngine::WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	camera_->translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	camera_->translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	camera_->translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}