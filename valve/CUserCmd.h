#pragma once

/* See: https://github.com/faluthe/cstrike15_src/blob/master/game/shared/usercmd.h
		https://github.com/faluthe/cstrike15_src/blob/master/game/shared/in_buttons.h */

#include "../sdk/classes/math/vector.h"

struct CUserCmd
{
	enum
	{
		IN_ATTACK = 1 << 0,
		IN_JUMP = 1 << 1,
		IN_DUCK = 1 << 2,
		IN_FORWARD = 1 << 3,
		IN_BACK = 1 << 4,
		IN_USE = 1 << 5,
		IN_MOVELEFT = 1 << 9,
		IN_MOVERIGHT = 1 << 10,
		IN_ATTACK2 = 1 << 11,
		IN_BULLRUSH = 1 << 22,
	};
	void* vmt;
	int command_number;
	int tick_count;
	Vector viewangles;
	Vector aimdirection;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
};