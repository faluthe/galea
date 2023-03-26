#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/icliententitylist.h

#include "../sdk/sdk.h"

struct IClientEntityList
{
	template<typename E>
	VIRTUAL_METHOD(E*, GetClientEntity, 3, (int entnum), (this, entnum))
	template<typename E>
	VIRTUAL_METHOD(E*, GetEntityFromHandle, 4, (int handle), (this, handle))
};