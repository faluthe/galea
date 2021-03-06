#include <stdexcept>

#include "../sdk/classes/entity/player.h"
#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "../core/configuration/config.h"
#include "../core/features.h"
#include "minhook/MinHook.h"
#include "hooks.h"

bool(__stdcall* oCreateMove)(float, CUserCmd*);
void(__thiscall* oPaintTraverse)(IPanel*, unsigned int, bool, bool);

void Hook::hook_function(unsigned short index, void* hkFunc, void** oFunc)
{
	if (MH_CreateHook((*reinterpret_cast<void***>(pInterface))[index], hkFunc, oFunc) != MH_OK)
		throw std::runtime_error("Hook failed");

	if (oFunc == nullptr)
		throw std::runtime_error("oFunc is nullptr");
}

bool __stdcall hkCreateMove(float sampletime, CUserCmd* cmd)
{
	// Remember, this function is only called in game!
	static bool hooked = []() { sdk::debug::print("CreateMove hooked"); return true; } ();

	if (cmd == nullptr || cmd->command_number == 0)
		return oCreateMove(sampletime, cmd);

	// Should this be called each time createmove is called?
	static bool bLocal = []() { g::get_localplayer(); return true; } ();

	if (GetAsyncKeyState(VK_HOME) & 1)
	{
		// Runtime tests go here
	}

	features::autopistol(cmd);
	features::bunnyhop(cmd);

	// Remove crouch delay
	cmd->buttons |= CUserCmd::IN_BULLRUSH;

	return false;
}

void __stdcall hkPaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
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
	}
}

void hooks::init()
{
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("MinHook not initialized");

	Hook client_mode{ ifaces::client_mode };
	Hook panel{ ifaces::panel };

	client_mode.hook_function(24, &hkCreateMove, reinterpret_cast<void**>(&oCreateMove));
	panel.hook_function(41, &hkPaintTraverse, reinterpret_cast<void**>(&oPaintTraverse));

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("Could not enable hooks");
}

void hooks::restore_all()
{
	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("Could not disable hooks");

	if (MH_Uninitialize() != MH_OK)
		throw std::runtime_error("Could not uninitialize MinHook");
}