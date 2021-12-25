#pragma once

#include "../../valve/IBaseClientDLL.h"
#include "../../valve/IClientEntityList.h"
#include "../../valve/IPanel.h"
#include "../../valve/ISurface.h"
#include "../../valve/IVEngineClient.h"

namespace ifaces
{
	inline IBaseClientDLL* client{};
	inline void* client_mode{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entity_list{};
	inline IPanel* panel{};
	inline ISurface* surface{};

	void init();
}