#pragma once

#include <Windows.h>

namespace config
{
	void render();
	void render_watermark();

	constexpr int menu_button{ VK_DELETE };
	constexpr int panic_button{ VK_END };

	inline bool autopistol{ false };
	inline bool bunnyhop{ true };
}