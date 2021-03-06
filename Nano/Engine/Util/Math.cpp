#include "Math.h"

#include <random>

float clamp(float val, float lo, float hi) {
	if (val < lo || lo > hi) {
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

int randInt(int lo, int hi) {
	return rand() % (hi - lo) + lo;
}

float randFloat() {
	return randFloat(0.0f, 1.0f);
}

float randFloat(float lo, float hi) {
	return (hi - lo) * rand() / RAND_MAX + lo;
}
