#pragma once

#include "../../valve/IBaseClientDLL.h"
#include "../../valve/IClientEntityList.h"
#include "../../valve/IMaterialSystem.h"
#include "../../valve/IPanel.h"
#include "../../valve/IStudioRender.h"
#include "../../valve/ISurface.h"
#include "../../valve/IVEngineClient.h"
#include "../../valve/IVModelRender.h"

namespace ifaces
{
	inline IBaseClientDLL* client{};
	inline void* client_mode{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entity_list{};
	inline IMaterialSystem* mat_sys{};
	inline IVModelRender* mdl_render{};
	inline IPanel* panel{};
	inline IStudioRender* studio_render{};
	inline ISurface* surface{};

	void init();
}