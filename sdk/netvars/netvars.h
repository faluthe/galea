#pragma once

#include <string>
#include <Windows.h>

#include "../sdk.h"

namespace netvars
{
	uintptr_t get_netvar(const char* table_name, const char* netvar_name);
}

#define NETVAR(type, function_name, table, prop) \
type& function_name() \
{ \
	static uintptr_t offset{}; \
	if (!offset) { offset = netvars::get_netvar(table, prop); sdk::debug::print_address(prop, offset, true); }\
	\
	return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
}