#include <array>
#include <Windows.h>

#include "../../sdk/classes/rendering/color.h"
#include "../../sdk/globals/globals.h"
#include "../../sdk/sdk.h"
#include "config.h"

struct option
{
	const std::wstring text;
	bool& state;
	bool selected{ false };
};

static std::array<option, 2> options{
		option{ L"Autopistol", config::autopistol },
		option{ L"Bunnyhop", config::bunnyhop }
};

static void render_option(const option& option, int& y_offset)
{
	if (option.selected)
		g::fonts::config.print(L"> " + option.text, g::screen_width / 4, y_offset, option.state ? colors::red : colors::grey);
	else
		g::fonts::config.print(option.text, g::screen_width / 4, y_offset, option.state ? colors::red : colors::grey);

	y_offset += g::fonts::config.height + 3;
}

void config::render_watermark()
{
	g::fonts::config.print(L"Galea by falu", g::screen_width - (g::screen_height / 8), 3);
}

void config::render()
{
	static bool menu_active{ false };

	if (GetAsyncKeyState(menu_button) & 1)
		menu_active = !menu_active;

	if (menu_active)
	{
		int y_offset{ 3 };

		static size_t selected{ 0 };

		if (GetAsyncKeyState(VK_DOWN) & 1 && selected < options.size() - 1)
			selected++;
		else if (GetAsyncKeyState(VK_UP) & 1 && selected > 0)
			selected--;

		for (size_t i{ 0 }; i < options.size(); i++)
		{
			if (i == selected)
				options[i].selected = true;
			else
				options[i].selected = false;

			if (options[i].selected && (GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(VK_LEFT) & 1))
				options[i].state = !options[i].state;

			render_option(options[i], y_offset);
		}
	}	
}