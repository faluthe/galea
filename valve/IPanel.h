#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/vgui/IPanel.h

#include "../sdk/sdk.h"

struct IPanel
{
	VIRTUAL_METHOD(const char*, GetName, 36, (unsigned int vguiPanel), (this, vguiPanel))
};