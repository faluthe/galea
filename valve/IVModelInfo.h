#pragma once

#include "../sdk/sdk.h"

struct IVModelInfo
{
	VIRTUAL_METHOD(int, GetModelIndex, 2, (const char* filename), (this, filename))
};