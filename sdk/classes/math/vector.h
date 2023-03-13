#pragma once

struct Vector
{
	float x, y, z;

	// These modify in place
	void normalize();
	void clamp();

	float dot(const Vector& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	float length_sqr()
	{
		return x * x + y * y + z * z;
	}

	Vector operator+(const Vector& v)
	{
		return Vector{ x + v.x, y + v.y, z + v.z };
	}
	Vector operator-(const Vector& v)
	{
		return Vector{ x - v.x, y - v.y, z - v.z };
	}
	Vector operator*(float f)
	{
		return Vector{ x * f, y * f, z * f };
	}
};