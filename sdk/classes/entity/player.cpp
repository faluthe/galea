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