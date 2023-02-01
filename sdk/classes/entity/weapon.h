#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/game/shared/cstrike15/weapon_csbase.h

#include "../../sdk.h"
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
	VIRTUAL_METHOD(WeaponType, GetWeaponType, 455, (), (this))

	bool is_pistol()
	{
		return GetWeaponType() == WeaponType::Pistol;
	}
};