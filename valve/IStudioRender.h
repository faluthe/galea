#pragma once

/* See: https://github.com/faluthe/cstrike15_src/blob/master/public/istudiorender.h
		https://github.com/danielkrupinski/Osiris/blob/master/Osiris/SDK/StudioRender.h */

#include <cstddef>
#include <string_view>

#include "../sdk/sdk.h"
#include "IMaterial.h"

enum class OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SELECTIVE, // Custom materials
	OVERRIDE_SSAO_DEPTH_WRITE,
};

class IStudioRender
{
private:
	std::byte pad0[592];
	IMaterial* material_override;
	std::byte pad1[12];
	OverrideType_t override_type;
public:
	VIRTUAL_METHOD(void, ForcedMaterialOverride, 33, (IMaterial* newMaterial, 
		OverrideType_t nOverrideType = OverrideType_t::OVERRIDE_NORMAL, int nMaterialIndex = -1), 
		(this, newMaterial, nOverrideType, nMaterialIndex))

	bool IsForcedMaterialOverride()
	{
		if (material_override == nullptr)
			return (override_type == OverrideType_t::OVERRIDE_DEPTH_WRITE ||
			override_type == OverrideType_t::OVERRIDE_SSAO_DEPTH_WRITE);
		return std::string_view{ material_override->GetName() }.starts_with("dev/glow");
	}
};