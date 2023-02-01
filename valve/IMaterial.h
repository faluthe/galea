#pragma once

/* See: https://github.com/faluthe/cstrike15_src/blob/master/public/materialsystem/imaterial.h
		https://github.com/faluthe/cstrike15_src/blob/master/public/materialsystem/imaterial_declarations.h */

#include "../sdk/sdk.h"

enum class MaterialVarFlags_t
{
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
};

struct IMaterial
{
	VIRTUAL_METHOD(const char*, GetName, 0, (), (this))
	VIRTUAL_METHOD(void, AlphaModulate, 27, (float alpha), (this, alpha))
	VIRTUAL_METHOD(void, ColorModulate, 28, (float r, float g, float b), (this, r, g, b))
	VIRTUAL_METHOD(void, SetMaterialVarFlags, 29, (MaterialVarFlags_t flag, bool on), (this, flag, on))
};