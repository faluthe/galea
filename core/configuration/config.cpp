#include <vector>
#include <Windows.h>

#include "../../sdk/classes/rendering/color.h"
#include "../../sdk/globals/globals.h"
#include "../../sdk/sdk.h"
#include "config.h"

// Pixels between each option
static constexpr int y_distance{ 3 };

static int y_selected{ y_distance };

static void option_bool(const std::wstring& title, bool& state, int& y_offset, int& max_options)
{
	if (GetAsyncKeyState(VK_DOWN) & 1 && y_selected < max_options + y_selected)
		y_selected += g::fonts::config.height + y_distance;
	else if (GetAsyncKeyState(VK_UP) & 1 && y_selected > y_distance)
		y_selected -= g::fonts::config.height + y_distance;

	if (y_offset == y_selected)
	{
		g::fonts::config.print(L"> " + title, g::screen_width / 4, y_offset, state ? colors::red : colors::grey);
		
		if ((GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(VK_LEFT) & 1))
			state = !state;
	}
	else
		g::fonts::config.print(title, g::screen_width / 4, y_offset, state ? colors::red : colors::grey);

	y_offset += g::fonts::config.height + y_distance;

	max_options += y_distance;
}

void config::render_watermark()
{
	g::fonts::config.print(L"Galea by falu", g::screen_width - (g::screen_height / 8), y_distance);
}

void config::render()
{
	static bool menu_active{ false };

	if (GetAsyncKeyState(menu_button) & 1)
	{
		menu_active = !menu_active;
		y_selected = y_distance;
	}

	if (menu_active)
	{
		int y_offset{ y_distance };
		int max_options{ y_distance };

		option_bool(L"Autopistol", config::autopistol, y_offset, max_options);
		option_bool(L"Bunnyhop", config::bunnyhop, y_offset, max_options);
		option_bool(L"Chams", config::chams, y_offset, max_options);
	}
}