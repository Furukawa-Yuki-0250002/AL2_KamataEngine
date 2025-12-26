#pragma once
#include <math.h>

class Easing {
public:
	static float Lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}

	static float EaseIn(float t) {
		return t * t;
	}

	static float EaseOut(float t) {
		return 1.0f - (1.0f - t) * (1.0f - t);
	}

	static float EaseInOut(float t) {
		if (t < 0.5f) {
			return 2.0f * t * t;
		} else {
			return 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
		}
	}

	static float EaseInBack(float t) {
		const float c = 1.70158f; // オーバーシュート量
		return (c + 1.0f) * t * t * t - c * t * t;
	}

	static float EaseOutBack(float t) {
		const float c = 1.70158f;
		t -= 1.0f;
		return 1.0f + (c + 1.0f) * t * t * t + c * t * t;
	}

	static float LerpEase(float a, float b, float t, float (*easeType)(float)) {
		return Lerp(a, b, easeType(t));
	}
};