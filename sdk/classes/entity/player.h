#pragma once

#include "../../netvars/netvars.h"
#include "entity.h"
#include "weapon.h"

struct Player : Entity
{
	NETVAR(int, flags, "DT_CSPlayer", "m_fFlags")
	NETVAR(int, health, "DT_BasePlayer", "m_iHealth")
	
	Weapon* active_weapon();
	bool is_alive();
};