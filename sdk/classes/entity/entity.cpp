#include "entity.h"
#include "../../sdk.h"

bool Entity::valid_ptr()
{
	return this != nullptr;
}

void Entity::invalidate_bone_cache()
{
	static uintptr_t invalidate_bone_cache = reinterpret_cast<uintptr_t>(sdk::helpers::pattern_scan("client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81"));
	auto bone_counter = **reinterpret_cast<uintptr_t**>(invalidate_bone_cache + 0xA);
	*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + 0x2924) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
	*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + 0x2690) = bone_counter - 1; // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
}