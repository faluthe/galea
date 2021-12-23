#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/cdll_int.h#L878

#include "ClientClass.h"
#include "../sdk/sdk.h"

struct IBaseClientDLL
{
	VIRTUAL_METHOD(ClientClass*, GetAllClasses, 8, (), (this))
};