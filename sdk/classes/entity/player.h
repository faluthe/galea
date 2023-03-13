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
	NETVAR(Vector, aim_punch, "DT_BasePlayer", "m_aimPunchAngle")

	VIRTUAL_METHOD(Vector&, get_abs_origin, 10, (), (this))
	VIRTUAL_METHOD(bool, is_dormant, 9, (), (this + sizeof(uintptr_t) * 2))
	VIRTUAL_METHOD(int, ent_list_index, 10, (), (get_networkable()))
	Vector eye_position()
	{
		Vector v;
		sdk::helpers::call_virtual_method<void, 285>(this, std::ref(v));
		return v;
	}
	
	void set_abs_origin(Vector& origin);
	Weapon* active_weapon();
	bool is_alive();
	Vector hitbox_pos(int id);
};