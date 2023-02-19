#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "features.h"

void features::test_esp()
{
	for (int i = 1; i < ifaces::engine->GetMaxClients(); i++)
	{
		auto ent = ifaces::entity_list->GetClientEntity<Player>(i);

		if (!ent || !ent->is_alive() || ent->is_dormant() || ent->team() == g::localplayer->team())
			continue;

		auto head_pos = ent->hitbox_pos(8);
		Vector pos_2d;
		if (ifaces::debug_overlay->ScreenPosition(&head_pos, &pos_2d) != 0)
			continue;

		g::fonts::config.print(L"H", pos_2d.x, pos_2d.y);

	}
}