#include <stdexcept>
#include <string>
#include <Windows.h>

#include "interfaces.h"

typedef	void* (*create_interface_fn)(const char* name, int* return_code);

template<typename I>
static I* get_interface(HMODULE hModule, const char* version)
{
	auto f = reinterpret_cast<create_interface_fn>(GetProcAddress(hModule, "CreateInterface"));
	auto result = reinterpret_cast<I*>(f(version, nullptr));

	if (!result)
		throw std::runtime_error(std::string{ "Failed to get interface: " } + version);

	return result;
}

void ifaces::init()
{
	const auto client_dll = GetModuleHandleA("client.dll");
	const auto engine_dll = GetModuleHandleA("engine.dll");

	// All interfaces (except client_mode) are checked
	client = get_interface<IBaseClientDLL>(client_dll, "VClient018");
	client_mode = **reinterpret_cast<void***>((*reinterpret_cast<uintptr_t**>(client))[0xA] + 0x5);
	cvar = cvar = get_interface<ICvar>(GetModuleHandleA("vstdlib.dll"), "VEngineCvar007");
	engine = get_interface<IVEngineClient>(engine_dll, "VEngineClient014");
	entity_list = get_interface<IClientEntityList>(client_dll, "VClientEntityList003");
	mat_sys = get_interface<IMaterialSystem>(GetModuleHandleA("materialsystem.dll"), "VMaterialSystem080");
	mdl_render = get_interface<IVModelRender>(engine_dll, "VEngineModel016");
	panel = get_interface<IPanel>(GetModuleHandleA("vgui2.dll"), "VGUI_Panel009");
	studio_render = get_interface<IStudioRender>(GetModuleHandleA("studiorender.dll"), "VStudioRender026");
	surface = get_interface<ISurface>(GetModuleHandleA("vguimatsurface.dll"), "VGUI_Surface031");

	sdk::debug::print("Interfaces initialized");
}