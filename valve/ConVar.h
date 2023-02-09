#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/8ee527f36d6fcc991a8dadf37eb7628189580340/public/tier1/convar.h#L412

#include <cstddef>

#include "../sdk/sdk.h"

struct ConVar
{
	std::byte pad0[12];
	const char* name;
};