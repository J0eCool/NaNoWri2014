#pragma once

#include "Containers.h"

#include <initializer_list>

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float _x, float _y);
	Vec2(std::initializer_list<float> dims);

	static Vec2 MakeUnit(float radians);
	static Vec2 RandUnit();
	static Vec2 Rand(Vec2 const& lo, Vec2 const& hi);

	float Length() const;
	float LengthSquared() const;
	Vec2 Unit() const;

	Vec2 operator-() const;
	Vec2 operator+(Vec2 const& other) const;
	Vec2 operator-(Vec2 const& other) const;
	Vec2 operator*(float s) const;
	Vec2 operator/(float s) const;

	Vec2& operator+=(Vec2 const& other);
	Vec2& operator-=(Vec2 const& other);
	Vec2& operator*=(float s);
	Vec2& operator/=(float s);

	float Dot(Vec2 const& other) const;
	float Cross(Vec2 const& other) const;

	Vec2 Mult(Vec2 const& other) const;
	Vec2 Min(Vec2 const& other) const;
	Vec2 Max(Vec2 const& other) const;

	String ToString() const;
};

Vec2 operator*(float s, Vec2 const& v);
Vec2 operator/(float s, Vec2 const& v);
