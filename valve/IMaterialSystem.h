#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/materialsystem/imaterialsystem.h

#include "../sdk/sdk.h"
#include "IMaterial.h"

struct IMaterialSystem
{
	VIRTUAL_METHOD(IMaterial*, FindMaterial, 84,
		(char const* pMaterialName, const char* pTextureGroupName),
			(this, pMaterialName, pTextureGroupName, true, NULL))
};