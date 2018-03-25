#pragma once

#include "Vector.h"
#include <cmath>

template <typename T>
struct Quadic {
	typedef Vector3<T> Vector;

	Vector u;
	float w;

	Quadic
		( const Vector &axis,
		, float angle
		)
		: u(std::sin(angle / 2) * axis)
		, w(std::cos(angle / 2))
	{}
};
