#include "Math.h"

float clamp(float val, float lo, float hi) {
	if (val < lo) {
		return lo;
	}
	if (val > hi) {
		return hi;
	}
	return val;
}

float clamp01(float val) {
	return clamp(val, 0.0f, 1.0f);
}

bool approxEq(float a, float b) {
	return abs(a - b) < 0.0001f;
}
