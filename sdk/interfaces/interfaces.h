#pragma once

#include "../../valve/IBaseClientDLL.h"

namespace ifaces
{
	inline IBaseClientDLL* client{};
	inline void* client_mode{};

	void init();
}