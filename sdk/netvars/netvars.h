#pragma once

#include <Windows.h>

namespace netvars
{
	uintptr_t get_netvar(const char* table_name, const char* netvar_name);
}

#define NETVAR(type, function_name, table, prop) \
type& functionName() \
{ \
	static uintptr_t offset{}; \
	if (!offset) offset = netvars::get_netvar(table, prop); \
	\
	return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
}