#pragma once

#include "../math/matrix.h"
#include "../../sdk.h"

struct Entity
{
	void* get_renderable() { return reinterpret_cast<void*>(this + 0x4); }
	void* get_networkable() { return reinterpret_cast<void*>(this + 0x8); }

	VIRTUAL_METHOD(bool, setup_bones, 13, (Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime), (get_renderable(), pBoneToWorldOut, nMaxBones, boneMask, currentTime))

	bool valid_ptr();
};