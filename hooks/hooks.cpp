#include <stdexcept>
#include <string>
#include <Windows.h>

#include "../sdk/classes/math/matrix.h"
#include "../sdk/classes/entity/player.h"
#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "../core/configuration/config.h"
#include "../core/features.h"
#include "../valve/checksum_md5.h"
#include "minhook/MinHook.h"
#include "hooks.h"

static bool(__stdcall* oCreateMove)(float, CUserCmd*);
static void(__thiscall* oFrameStageNotify)(void*, FrameStage);
static void(__thiscall* oPaintTraverse)(IPanel*, unsigned int, bool, bool);
static int(__thiscall* oSendDatagram)(CNetChan*, void*);

void Hook::hook_function(unsigned short index, void* hkFunc, void** oFunc)
{
	if (MH_CreateHook((*reinterpret_cast<void***>(pInterface))[index], hkFunc, oFunc) != MH_OK)
		throw std::runtime_error("Hook failed");

	if (oFunc == nullptr)
		throw std::runtime_error("oFunc is nullptr");
}

// Thanks sharklaser! See: https://www.unknowncheats.me/forum/counterstrike-global-offensive/227226-synced-fake-ping.html
int __fastcall hkSendDatagram(CNetChan* netchan, void*, void* datagram)
{
	if (!ifaces::engine->IsInGame())
	{
		features::backtrack::last_sequence = 0;
		return oSendDatagram(netchan, datagram);
	}

	if (datagram)
		return oSendDatagram(netchan, datagram);

	auto state = netchan->m_nInReliableState;
	auto sequence_nr = netchan->m_nInSequenceNr;

	if (config::fakeping > 0.f)
	{
		features::backtrack::add_latency(netchan, config::fakeping);

		int og = oSendDatagram(netchan, datagram);

		netchan->m_nInReliableState = state;
		netchan->m_nInSequenceNr = sequence_nr;

		return og;
	}
	else
		return oSendDatagram(netchan, datagram);
}

// Called once per tick in game
static bool __stdcall hkCreateMove(float sampletime, CUserCmd* cmd)
{
	auto set_angles = oCreateMove(sampletime, cmd);
	if (cmd == nullptr || cmd->command_number == 0)
		return set_angles;

	if (set_angles)
		ifaces::engine->SetViewAngles(&cmd->viewangles);

	cmd->random_seed = MD5_PseudoRandom(cmd->command_number) & 0x7fffffff;

	// Remember, this function is only called in game!
	static bool hooked = []() { sdk::debug::print("CreateMove hooked"); return true; } ();
	static bool send_datagram_hook = []() {
		// MAKE THIS MORE CONCISE
		auto client_state = **reinterpret_cast<void***>(sdk::helpers::pattern_scan("engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
		ifaces::netchan = *reinterpret_cast<CNetChan**>(reinterpret_cast<uintptr_t>(client_state) + 0x9C);

		auto addr = sdk::helpers::pattern_scan("engine.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9 89 7C 24 14");
		if (MH_CreateHook(reinterpret_cast<void*>(addr), &hkSendDatagram, reinterpret_cast<void**>(&oSendDatagram)) != MH_OK)
			throw std::runtime_error("SendDatagram Hook failed");
		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			throw std::runtime_error("Could not enable hook");
		return true;
	} ();

	g::get_localplayer();
	config::convars::set();

	features::autopistol(cmd);
	features::bunnyhop(cmd);
	features::triggerbot(cmd);
	features::esp::anti_flash();
	features::backtrack::update_sequences();
	features::backtrack::run(cmd);

	// Remove crouch delay
	cmd->buttons |= CUserCmd::IN_BULLRUSH;

	return false;
}

static void __fastcall hkDrawModelExecute(void* _this, void* _edx, void* pRenderContext, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, Matrix3x4* pCustomBoneToWorld)
{
	static bool hooked = []() { sdk::debug::print("DrawModelExecute hooked"); return true; } ();

	if (ifaces::studio_render->IsForcedMaterialOverride())
		return hooks::oDrawModelExecute(_this, _edx, pRenderContext, state, pInfo, pCustomBoneToWorld);

	features::chams(_this, _edx, pRenderContext, state, pInfo, pCustomBoneToWorld);

	hooks::oDrawModelExecute(_this, _edx, pRenderContext, state, pInfo, pCustomBoneToWorld);
	
	ifaces::studio_render->ForcedMaterialOverride(nullptr);
}

void __stdcall hkFrameStageNotify(FrameStage frame_stage)
{
	// PostDataUpdate has been called and we're about to interpolate, or not ;)
	if (frame_stage == FrameStage::FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		features::backtrack::disable_interpolation();
	else if (frame_stage == FrameStage::FRAME_NET_UPDATE_END)
		features::backtrack::update_records();
	else if (frame_stage == FrameStage::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		features::skinchanger();

	oFrameStageNotify(ifaces::client, frame_stage);
}

static void __stdcall hkPaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	static bool hooked = []() { sdk::debug::print("PaintTraverse hooked"); return true; } ();

	oPaintTraverse(ifaces::panel, vguiPanel, forceRepaint, allowForce);

	auto panel_name = ifaces::panel->GetName(vguiPanel);

	// strcmp returns 0 if strings are equal
	if (strcmp(panel_name, "MatSystemTopPanel") == 0)
	{
		/* This function doesn't need to be called every time PaintTraverse is,
		   only when the screen size is relevant. Fonts are also configured here,
		   as the two are directly correlated */
		g::get_screen_size();
		
		config::render();
		config::render_watermark();
		features::esp::crosshair();
	}
}

void hooks::init()
{
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("MinHook not initialized");

	Hook client{ ifaces::client };
	Hook client_mode{ ifaces::client_mode };
	Hook mdl_render{ ifaces::mdl_render };
	Hook panel{ ifaces::panel };

	client.hook_function(37, &hkFrameStageNotify, reinterpret_cast<void**>(&oFrameStageNotify));
	client_mode.hook_function(24, &hkCreateMove, reinterpret_cast<void**>(&oCreateMove));
	mdl_render.hook_function(21, &hkDrawModelExecute, reinterpret_cast<void**>(&oDrawModelExecute));
	panel.hook_function(41, &hkPaintTraverse, reinterpret_cast<void**>(&oPaintTraverse));

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("Could not enable hooks");

	// Return address checks hotfix
	const char* game_modules[]{ "client.dll",  "engine.dll",  "server.dll",  "studiorender.dll", "materialsystem.dll",  "shaderapidx9.dll",  "vstdlib.dll", "vguimatsurface.dll" };
	long long patch = 0x69690004C201B0;
	for (auto current_module : game_modules)
		WriteProcessMemory(GetCurrentProcess(), (LPVOID)sdk::helpers::pattern_scan(current_module, "55 8B EC 56 8B F1 33 C0 57 8B 7D 08"), &patch, 5, 0);
}

void hooks::restore_all()
{
	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("Could not disable hooks");

	if (MH_Uninitialize() != MH_OK)
		throw std::runtime_error("Could not uninitialize MinHook");
}