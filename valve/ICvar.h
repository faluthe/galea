#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/icvar.h

#include "../sdk/sdk.h"
#include "ConVar.h"

struct ICvar {
	VIRTUAL_METHOD(ConVar*, FindVar, 16, (const char* varName), (this, varName))
};