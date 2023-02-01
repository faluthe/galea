#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/engine/ivmodelrender.h

#include <cstddef>

#include "../sdk/sdk.h"

struct model_t
{
	void* fn_handle;
	char name[260];
};

struct ModelRenderInfo_t
{
	std::byte pad0[32];
	const model_t* pModel;
	std::byte pad1[16];
	int entity_index;
};

struct IVModelRender
{
	std::byte pad0;
};