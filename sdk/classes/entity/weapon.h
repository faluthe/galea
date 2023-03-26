#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/game/shared/cstrike15/weapon_csbase.h

#include "../../sdk.h"
#include "../../netvars/netvars.h"
#include "entity.h"

enum class WeaponType
{
	Knife = 0,
	Pistol,
	SubMachinegun,
	Rifle,
	Shotgun,
	SniperRifle,
	Machinegun,
	C4,
	Placeholder,
	Grenade,
};

struct Weapon : Entity
{
	NETVAR(int, world_model, "DT_BaseCombatWeapon", "m_hWeaponWorldModel")
	NETVAR(int, og_owner_low, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow")
	NETVAR(int, og_owner_high, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh")
	NETVAR(int, fallback_seed, "DT_BaseAttributableItem", "m_nFallbackSeed")
	NETVAR(int, item_id, "DT_BaseAttributableItem", "m_iItemIDHigh")
	NETVAR(int, item_def_index, "DT_BaseCombatWeapon", "m_iItemDefinitionIndex")
	NETVAR(int, paint_kit, "DT_BaseAttributableItem", "m_nFallbackPaintKit")
	NETVAR(int, quality, "DT_BaseAttributableItem", "m_iEntityQuality")
	NETVAR(float, wear, "DT_BaseAttributableItem", "m_flFallbackWear")

	VIRTUAL_METHOD(WeaponType, get_weapon_type, 455, (), (this))

	bool is_pistol()
	{
		return get_weapon_type() == WeaponType::Pistol;
	}
	bool is_knife()
	{
		return get_weapon_type() == WeaponType::Knife;
	}
};

struct ViewmodelEnt : Entity
{
	NETVAR(int, hWeapon, "DT_BaseViewModel", "m_hWeapon")
};