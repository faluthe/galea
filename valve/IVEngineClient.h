#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/cdll_int.h#L298

#include <functional>

#include "../sdk/sdk.h"

struct IVEngineClient
{
	VIRTUAL_METHOD(void, GetScreenSize, 5, (int& width, int& height), (this, std::ref(width), std::ref(height)))
	// Returns index of localplayer in entity list
	VIRTUAL_METHOD(int, GetLocalPlayer, 12, (), (this))
};