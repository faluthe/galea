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
		constexpr Color enemy_hidden{ 0x00, 0x00, 0x00 };
		constexpr Color enemy_visible{ 0xFF, 0x5F, 0x15 };
	}
}