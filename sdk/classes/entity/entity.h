#pragma once

#include "../math/matrix.h"
#include "../../netvars/netvars.h"
#include "../../sdk.h"

struct Entity
{
	void* get_renderable() { return reinterpret_cast<void*>(this + 0x4); }
	void* get_networkable() { return reinterpret_cast<void*>(this + 0x8); }

	NETVAR(int, model_index, "DT_BaseViewModel", "m_nModelIndex")
	VIRTUAL_METHOD(bool, setup_bones, 13, (Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime), (get_renderable(), pBoneToWorldOut, nMaxBones, boneMask, currentTime))

	bool valid_ptr();
	void invalidate_bone_cache();
};