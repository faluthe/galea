#include "../core/configuration/config.h"
#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "../valve/CUserCmd.h"
#include "features.h"

#include <Windows.h>

void features::triggerbot(CUserCmd* cmd)
{
	if (!config::triggerbot || !g::localplayer->valid_ptr() || !g::localplayer->is_alive())
		return;

	auto id = g::localplayer->crosshair_id();
	if (id != 0 && id < 32)
	{
		const auto ent = ifaces::entity_list->GetClientEntity<Player>(id);
		// 'C' key for now
		if (ent->team() != g::localplayer->team() && GetAsyncKeyState(0x43) >> 15)
			cmd->buttons |= CUserCmd::IN_ATTACK;
	}
}