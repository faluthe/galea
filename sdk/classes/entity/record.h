#pragma once

#include "../math/matrix.h"
#include "../math/vector.h"

struct Record
{
	Vector head{};
	float sim_time{};
	Matrix3x4 bone_matrix[128];
};