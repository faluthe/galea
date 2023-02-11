#pragma once

#include <Windows.h>

#include "../../sdk/classes/rendering/color.h"

namespace config
{
	void render();
	void render_watermark();

	constexpr int menu_button{ VK_INSERT };
	constexpr int panic_button{ VK_END };

	inline bool autopistol{ false };
	inline bool bunnyhop{ true };
	inline bool chams{ true };

	namespace colors
	{
		constexpr Color enemy_hidden{ 0x04, 0x74, 0xBA };
		constexpr Color enemy_visible{ 0xF3, 0x69, 0x17 };
		constexpr Color interp_ticks{ 0xFF, 0xFF, 0xFF, 0x7F };
	}
}