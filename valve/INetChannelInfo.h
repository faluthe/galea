#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/inetchannelinfo.h

#include "../sdk/sdk.h"

struct INetChannelInfo
{
	VIRTUAL_METHOD(float, GetLatency, 9, (int flow), (this, flow))
};