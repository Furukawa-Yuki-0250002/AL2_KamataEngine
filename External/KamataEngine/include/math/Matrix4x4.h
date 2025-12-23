#pragma once
#include "Vector3.h"
#include <cmath>

namespace KamataEngine {

/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];
};

// 行列作成
inline Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] =
				m1.m[y][0] * m2.m[0][x] + 
				m1.m[y][1] * m2.m[1][x] +
				m1.m[y][2] * m2.m[2][x] +
				m1.m[y][3] * m2.m[3][x];
		}
	}
	return result;
}

// --- Scale ---
inline Matrix4x4 MakeScaleMatrix(const Vector3& s) {
	Matrix4x4 m {};
	m.m[0][0] = s.x;
	m.m[1][1] = s.y;
	m.m[2][2] = s.z;
	m.m[3][3] = 1.0f;

	return m;
}

// --- Rotate X ---
inline Matrix4x4 MakeRotateXMatrix(float rad) {
	Matrix4x4 m{};
	float cos = cosf(rad);
	float sin = sinf(rad);
	m.m[0][0] = 1.0f;
	m.m[1][1] = cos;
	m.m[1][2] = -sin;
	m.m[2][1] = sin;
	m.m[2][2] = cos;
	m.m[3][3] = 1.0f;
	return m;
}

// --- Rotate Y ---
inline Matrix4x4 MakeRotateYMatrix(float rad) {
	Matrix4x4 m{};
	float cos = cosf(rad);
	float sin = sinf(rad);
	m.m[0][0] = cos;
	m.m[0][2] = -sin;
	m.m[1][1] = 1.0f;
	m.m[2][0] = sin;
	m.m[2][2] = cos;
	m.m[3][3] = 1.0f;
	return m;
}

// --- Rotate Z ---
inline Matrix4x4 MakeRotateZMatrix(float rad) {
	Matrix4x4 m{};
	float cos = cosf(rad);
	float sin = sinf(rad);
	m.m[0][0] = cos;
	m.m[0][1] = -sin;
	m.m[1][0] = sin;
	m.m[1][1] = cos;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	return m;
}

// --- Translate ---
inline Matrix4x4 MakeTranslateMatrix(const Vector3& t) {
	Matrix4x4 m{};
	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	m.m[3][0] = t.x;
	m.m[3][1] = t.y;
	m.m[3][2] = t.z;
	return m;
}

// --- Affine ---
inline Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translation) {
	Matrix4x4 Scale = MakeScaleMatrix(scale);
	Matrix4x4 RotX = MakeRotateXMatrix(rotation.x);
	Matrix4x4 RotY = MakeRotateYMatrix(rotation.y);
	Matrix4x4 RotZ = MakeRotateZMatrix(rotation.z);
	Matrix4x4 Translate = MakeTranslateMatrix(translation);
	// 回転行列の合成（Z→X→Yの順）
	Matrix4x4 Rot = Multiply(RotZ, Multiply(RotX, RotY));
	// スケーリングと回転の合成
	Matrix4x4 world = Multiply(Scale, Rot);
	// 最終的なアフィン変換行列
	world = Multiply(world, Translate);
	return world;
}

} // namespace KamataEngine