#pragma once

#include "../../valve/CGlobalVarsBase.h"
#include "../../valve/CNetChan.h"
#include "../../valve/IBaseClientDLL.h"
#include "../../valve/IClientEntityList.h"
#include "../../valve/ICvar.h"
#include "../../valve/IMaterialSystem.h"
#include "../../valve/IPanel.h"
#include "../../valve/IStudioRender.h"
#include "../../valve/ISurface.h"
#include "../../valve/IVDebugOverlay.h"
#include "../../valve/IVEngineClient.h"
#include "../../valve/IVModelInfo.h"
#include "../../valve/IVModelRender.h"

namespace ifaces
{
	/* 'inline' tells the compiler to only create one instance of the variable
	   even if the header file is included in multiple source files */
	inline IBaseClientDLL* client{};
	inline void* client_mode{};
	inline ICvar* cvar{};
	inline IVDebugOverlay* debug_overlay{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entity_list{};
	inline CGlobalVarsBase* global_vars{};
	inline IMaterialSystem* mat_sys{};
	inline IVModelInfo* mdl_info{};
	inline IVModelRender* mdl_render{};
	inline CNetChan* netchan{};
	inline IPanel* panel{};
	inline IStudioRender* studio_render{};
	inline ISurface* surface{};

	void init();
}