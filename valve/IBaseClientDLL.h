#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/cdll_int.h#L878

#include "../sdk/sdk.h"
#include "ClientClass.h"

struct IBaseClientDLL
{
	VIRTUAL_METHOD(ClientClass*, GetAllClasses, 8, (), (this))
};