#include "../../interfaces/interfaces.h"
#include "player.h"

bool Player::is_alive() 
{ 
	return health() > 0; 
}

Weapon* Player::active_weapon()
{
	static uintptr_t offset{};

	if (!offset)
	{ 
		offset = netvars::get_netvar("DT_CSPlayer", "m_hActiveWeapon");
		sdk::debug::print_address("m_hActiveWeapon", offset, true);
	}

	auto weapon = *reinterpret_cast<uintptr_t*>(this + offset) & 0xFFF;
	return ifaces::entity_list->GetClientEntity<Weapon>(weapon);
}

Vector Player::hitbox_pos(int id)
{
	Matrix3x4 bone_matrixes[128];
	 
	if (setup_bones(bone_matrixes, 128, 0x100, 0.f))
	{
		Matrix3x4 m = bone_matrixes[id];
		return Vector{ m[0][3], m[1][3], m[2][3] };
	}

	return Vector{ 0, 0, 0 };
}

void Player::set_abs_origin(Vector& origin)
{
	*reinterpret_cast<Vector*>(uintptr_t(this) + 0xA0) = origin;
}