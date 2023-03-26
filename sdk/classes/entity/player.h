#pragma once

#include "../../sdk.h"
#include "../../netvars/netvars.h"
#include "../math/vector.h"
#include "entity.h"
#include "weapon.h"

#include <array>

enum class Team
{
	T = 2,
	CT = 3
};

using WeaponList = std::array<int, 48>;

struct Player : Entity
{
	NETVAR(int, flags, "DT_CSPlayer", "m_fFlags")
	NETVAR(int, health, "DT_BasePlayer", "m_iHealth")
	NETVAR(Team, team, "DT_BasePlayer", "m_iTeamNum")
	NETVAR(float, sim_time, "DT_CSPlayer", "m_flSimulationTime")
	NETVAR(Vector, origin, "DT_BasePlayer", "m_vecOrigin")
	NETVAR(Vector, aim_punch, "DT_BasePlayer", "m_aimPunchAngle")
	NETVAR(WeaponList, my_weapons, "DT_BaseCombatCharacter", "m_hMyWeapons")
	NETVAR(int, view_model, "DT_BasePlayer", "m_hViewModel[0]")
	int& crosshair_id()
	{
		static uintptr_t offset{};
		if (!offset) {
			offset = netvars::get_netvar("DT_CSPlayer", "m_bHasDefuser"); 
			sdk::debug::print_address("m_bHasDefuser", offset, true);
		}

		static uintptr_t id_offset{};
		if (!id_offset)
		{
			id_offset = offset + 92;
			sdk::debug::print_address("crosshair_id", id_offset, true);
		}

		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + id_offset);
	}

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