#include "../core/configuration/config.h"
#include "../sdk/globals/globals.h"
#include "../valve/CUserCmd.h"
#include "features.h"

void features::bunnyhop(CUserCmd* cmd)
{
	if (!config::bunnyhop || !g::localplayer->valid_ptr() || !g::localplayer->is_alive())
		return;

	if (!(g::localplayer->flags() & 1))
		cmd->buttons &= ~CUserCmd::IN_JUMP;
}