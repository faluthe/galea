#pragma once

#include "../../sdk.h"
#include "../../netvars/netvars.h"
#include "../math/vector.h"
#include "entity.h"
#include "weapon.h"

enum class Team
{
	T = 2,
	CT = 3
};

struct Player : Entity
{
	NETVAR(int, flags, "DT_CSPlayer", "m_fFlags")
	NETVAR(int, health, "DT_BasePlayer", "m_iHealth")
	NETVAR(Team, team, "DT_BasePlayer", "m_iTeamNum")
	NETVAR(float, sim_time, "DT_CSPlayer", "m_flSimulationTime")
	NETVAR(Vector, origin, "DT_BasePlayer", "m_vecOrigin")

	VIRTUAL_METHOD(bool, is_dormant, 9, (), (this + sizeof(uintptr_t) * 2))
	
	Weapon* active_weapon();
	bool is_alive();
};