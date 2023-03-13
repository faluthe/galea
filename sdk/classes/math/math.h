#pragma once

#include "vector.h"

namespace math
{
	Vector vector_angles(const Vector& forward);
	Vector angle_vector(const Vector& angles);

	constexpr float radian_to_degree(const float x)
	{
		return x * (180.f / 3.14159265358979323846f);
	}

	constexpr float degree_to_radian(const float x)
	{
		return x * (3.14159265358979323846f / 180.f);
	}
}