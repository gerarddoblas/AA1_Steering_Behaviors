#pragma once
#include"Vector2.hpp"

struct Steering
{
	Vector2 _linear;

	Steering() = default;
	Steering(Vector2 linear) : _linear(linear) {}
	//Struct de apoyo para facilitar los calculos, los operadores sirven para multiplicar y sumar Steering, que realmente afecta a su fuerza(Vector2 _linear).
	Steering operator*(float s) const { return Steering(_linear * s); }
	Steering& operator+=(const Steering& o) { (_linear += o._linear); return *this; }
	float magnitude() const { return _linear.length(); }
	Steering truncated(float length) const { return Steering(_linear.truncated(length)); }
};