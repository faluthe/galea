#pragma once

#include "../math/matrix.h"
#include "../math/vector.h"

struct Record
{
	Vector origin{};
	float sim_time{};
	Matrix3x4 bone_matrix{};
};