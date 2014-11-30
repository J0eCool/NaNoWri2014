#pragma once

#include <math.h>

const float PI = 3.14159265f;

float clamp(float val, float lo, float hi);
float clamp01(float val);

bool approxEq(float a, float b);

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

template <typename T>
inline T min(T a, T b) {
	return a < b ? a : b;
}

template <typename T>
inline T max(T a, T b) {
	return a > b ? a : b;
}

template <typename T>
inline T lerp(float t, T lo, T hi) {
	float t_ = clamp01(t);
	return (T)(lo + t_ * (hi - lo));
}

template <typename T>
inline T absMax(T a, T b) {
	return abs(a) > abs(b) ? a : b;
}

template <typename T>
inline T absMin(T a, T b) {
	return abs(a) < abs(b) ? a : b;
}

template <typename T>
inline int sign(T n) {
	if (n < 0) {
		return -1;
	}
	if (n > 0) {
		return 1;
	}
	return 0;
}

template <typename T>
inline int sign1(T n) {
	if (n < 0) {
		return -1;
	}
	return 1;
}

int randInt(int lo, int hi);
float randFloat();
float randFloat(float lo, float hi);
