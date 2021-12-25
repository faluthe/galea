#include "../core/configuration/config.h"
#include "../sdk/globals/globals.h"
#include "../valve/CUserCmd.h"
#include "features.h"

void features::autopistol(CUserCmd* cmd)
{
	if (!config::autopistol || !g::localplayer->valid_ptr() || !g::localplayer->is_alive())
		return;

	const auto active_weapon = g::localplayer->active_weapon();

	if (!active_weapon->valid_ptr() || !active_weapon->is_pistol())
		return;

	static bool firing{ false };

	if (firing)
		cmd->buttons &= ~CUserCmd::IN_ATTACK;

	firing = cmd->buttons & CUserCmd::IN_ATTACK ? true : false;
}