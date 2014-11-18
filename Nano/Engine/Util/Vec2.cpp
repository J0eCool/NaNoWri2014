#include "Vec2.h"

#include "Math.h"

#include <math.h>
#include <sstream>
#include <assert.h>

Vec2::Vec2() : x(0.0f), y(0.0f) { }
Vec2::Vec2(float _x, float _y) : x(_x), y(_y) { }
Vec2::Vec2(std::initializer_list<float> dims) {
	assert(dims.size() == 2);
	auto it = dims.begin();
	x = *it;
	it++;
	y = *it;
}

Vec2 Vec2::MakeUnit(float radians) {
	return Vec2(cos(radians), sin(radians));
}

Vec2 Vec2::RandUnit() {
	return Vec2::MakeUnit(randFloat(0.0f, 2.0f * PI));
}

Vec2 Vec2::Rand(Vec2 const& lo, Vec2 const& hi) {
	return Vec2(randFloat(lo.x, hi.x), randFloat(lo.y, hi.y));
}

float Vec2::LengthSquared() const {
	return x * x + y * y;
}
float Vec2::Length() const {
	return sqrt(LengthSquared());
}

Vec2 Vec2::Unit() const {
	float l = Length();
	if (l == 0) {
		return Vec2();
	}
	return Vec2(x / l, y / l);
}

Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

Vec2 Vec2::operator+(Vec2 const& other) const {
	return Vec2(x + other.x, y + other.y);
}
Vec2 Vec2::operator-(Vec2 const& other) const {
	return Vec2(x - other.x, y - other.y);
}
Vec2 Vec2::operator*(float s) const {
	return Vec2(x * s, y * s);
}
Vec2 Vec2::operator/(float s) const {
	return Vec2(x / s, y / s);
}

Vec2& Vec2::operator+=(Vec2 const& other) {
	*this = *this + other;
	return *this;
}
Vec2& Vec2::operator-=(Vec2 const& other) {
	*this = *this - other;
	return *this;
}
Vec2& Vec2::operator*=(float s) {
	*this = *this * s;
	return *this;
}
Vec2& Vec2::operator/=(float s) {
	*this = *this / s;
	return *this;
}

float Vec2::Dot(Vec2 const& other) const {
	return x * other.x + y * other.y;
}
float Vec2::Cross(Vec2 const& other) const {
	return x * other.y - y * other.x;
}

String Vec2::ToString() const {
	std::stringstream sstr;
	sstr << "(" << x << ", " << y << ")";
	return sstr.str();
}

Vec2 operator*(float s, Vec2 const& v) {
	return v * s;
}
Vec2 operator/(float s, Vec2 const& v) {
	return v / s;
}
