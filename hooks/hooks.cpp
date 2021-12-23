#include <stdexcept>

#include "hooks.h"
#include "../sdk/interfaces/interfaces.h"
#include "minhook/MinHook.h"

bool(__stdcall* oCreateMove)(float, void*);

void Hook::hook_function(unsigned short index, void* hkFunc, void* oFunc)
{
	if (MH_CreateHook((*reinterpret_cast<void***>(pInterface))[index], hkFunc, &oFunc) != MH_OK)
		throw std::runtime_error("Hook failed");
}

bool __stdcall hkCreateMove(float sampletime, void* cmd)
{
	// Remember, this function is only called in game!
	static bool hooked = []() { sdk::debug::print("CreateMove hooked"); return true; } ();

	return false;
}

void hooks::init()
{
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("MinHook not initialized");

	Hook client_mode{ ifaces::client_mode };

	client_mode.hook_function(24, &hkCreateMove, &oCreateMove);

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