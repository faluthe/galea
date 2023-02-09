#pragma once

struct Matrix3x4
{
	float matrix[3][4];

	float* operator[](int i)
	{
		return matrix[i];
	}
};