#pragma once

#include <string>

#include "classes/math/vector.h"

namespace sdk
{
	namespace debug
	{
		void create_console();
		void free_console();
		void print(const std::string& str);
		void print_address(const std::string& title, const uintptr_t address, bool is_offset = false);
		void error(const std::string& message);
	}

	namespace helpers
	{
		std::uint8_t* pattern_scan(const char* module_name, const char* signature);
		float get_fov(const Vector& view_angle, const Vector& aim_angle);
		template<typename R, int index, typename ...A>
		constexpr R call_virtual_method(void* pInterface, A... arguments)
		{
			return (*reinterpret_cast<R(__thiscall***)(void*, A...)>(pInterface))[index](pInterface, arguments...);
		}
	}
}

#define VIRTUAL_METHOD(type, function_name, index, function_args, real_args) \
type function_name function_args \
{ \
	return sdk::helpers::call_virtual_method<type, index>real_args; \
}