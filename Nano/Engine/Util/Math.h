#pragma once

#include <math.h>

float clamp(float val, float lo, float hi);
float clamp01(float val);

bool approxEq(float a, float b);

template <typename T>
T lerp(float t, T lo, T hi) {
	float t_ = clamp01(t);
	return (T)(lo + t_ * hi);
}

template <typename T>
T absMax(T a, T b) {
	if (abs(a) > abs(b)) {
		return a;
	}
	return b;
}

template <typename T>
T absMin(T a, T b) {
	if (abs(a) < abs(b)) {
		return a;
	}
	return b;
}

template <typename T>
int sign(T n) {
	if (n < 0) {
		return -1;
	}
	if (n > 0) {
		return 1;
	}
	return 0;
}

template <typename T>
int sign1(T n) {
	if (n < 0) {
		return -1;
	}
	return 1;
}

