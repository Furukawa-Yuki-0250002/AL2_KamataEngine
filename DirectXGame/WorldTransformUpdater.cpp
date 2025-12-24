#include "WorldTransformUpdater.h"

using namespace KamataEngine;

void WorldTransformUpdate(KamataEngine::WorldTransform& worldTransform) {
	// 行列を更新して定数バッファに転送
	worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	worldTransform.TransferMatrix();
}