#pragma once

#include "../sdk/classes/math/vector.h"
#include "../sdk/sdk.h"

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/engine/ivdebugoverlay.h

struct IVDebugOverlay
{
	VIRTUAL_METHOD(int, ScreenPosition, 13, (Vector* point, Vector* screen), (this, point, screen))
};