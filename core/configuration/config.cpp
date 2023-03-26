#include <vector>
#include <Windows.h>

#include "../../sdk/classes/rendering/color.h"
#include "../../sdk/globals/globals.h"
#include "../../sdk/sdk.h"
#include "config.h"

// Pixels between each option
static constexpr int y_distance{ 3 };

void config::render_watermark()
{
	g::fonts::config.print(L"Galea by falu", g::screen_width - (g::screen_height / 8), y_distance);
}

void config::render()
{
	static bool menu_active = false;
	if (GetAsyncKeyState(menu_button) & 1)
		menu_active = !menu_active;

	static std::vector<Option*> cfg = {
		new BoolOption(L"Autopistol", &config::autopistol),
		new BoolOption(L"Bunnyhop", &config::bunnyhop),
		new BoolOption(L"Triggerbot", &config::triggerbot),
		new BoolOption(L"Chams", &config::chams),
		new InvisibleBool(L"Ignore Z", &config::ignore_z, &config::chams),
		new InvisibleBool(L"Backtrack", &config::backtrack_chams, &config::chams),
		new InvisibleBool(L"Render Target Tick", &config::render_target_tick, &config::chams),
		new IntOption(L"Crosshair mode", &config::crosshair_mode, 1, 0, 2),
		new FloatOption(L"Fakeping", &config::fakeping, 0.02f, 0.f, 0.2f),
		new BoolOption(L"Streched Ratio", &config::convars::stretched_ratio)
	};

	if (menu_active)
	{
		static int selected = 0;
		if (GetAsyncKeyState(VK_DOWN) & 1)
			selected = selected >= static_cast<int>(cfg.size()) - 1 ? 0 : selected + 1;
		else if (GetAsyncKeyState(VK_UP) & 1)
			selected = selected <= 0 ? static_cast<int>(cfg.size()) - 1 : selected - 1;

		int y_offset = y_distance;
		for (size_t i = 0; i < cfg.size(); i++)
		{
			if (i == selected)
				cfg.at(i)->while_selected(g::screen_width / 4, y_offset);
			else
				cfg.at(i)->while_not_selected(g::screen_width / 4, y_offset);
		}
	}
}

void BoolOption::while_selected(int x, int& y)
{
	g::fonts::config.print(L"> " + title, g::screen_width / 4, y, *state ? colors::red : colors::grey);

	if ((GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(VK_LEFT) & 1))
		*state = !(*state);

	y += g::fonts::config.height + y_distance;
}

void BoolOption::while_not_selected(int x, int& y)
{
	g::fonts::config.print(title, g::screen_width / 4, y, *state ? colors::red : colors::grey);

	y += g::fonts::config.height + y_distance;
}

void InvisibleBool::while_selected(int x, int& y)
{
	if (!(*parent))
		return;

	g::fonts::config.print(L"\t> " + title, g::screen_width / 4, y, *state ? colors::red : colors::grey);

	if ((GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(VK_LEFT) & 1))
		*state = !(*state);

	y += g::fonts::config.height + y_distance;
}

void InvisibleBool::while_not_selected(int x, int& y)
{
	if (!(*parent))
		return;

	g::fonts::config.print(L"\t" + title, g::screen_width / 4, y, *state ? colors::red : colors::grey);

	y += g::fonts::config.height + y_distance;
}

void FloatOption::while_selected(int x, int& y)
{
	g::fonts::config.print(L"> " + title + L": " + std::to_wstring(*flt).substr(0, 5), g::screen_width / 4, y, colors::red);

	if (GetAsyncKeyState(VK_RIGHT) & 1)
		*flt = *flt >= max ? min : *flt + modifier;
	else if (GetAsyncKeyState(VK_LEFT) & 1)
		*flt = *flt <= min ? max : *flt - modifier;

	y += g::fonts::config.height + y_distance;
}

void FloatOption::while_not_selected(int x, int& y)
{
	g::fonts::config.print(title + L": " + std::to_wstring(*flt).substr(0, 5), g::screen_width / 4, y, colors::red);

	y += g::fonts::config.height + y_distance;
}

void IntOption::while_selected(int x, int& y)
{
	g::fonts::config.print(L"> " + title + L": " + std::to_wstring(*i).substr(0, 5), g::screen_width / 4, y, colors::red);

	if (GetAsyncKeyState(VK_RIGHT) & 1)
		*i = *i >= max ? min : *i + modifier;
	else if (GetAsyncKeyState(VK_LEFT) & 1)
		*i = *i <= min ? max : *i - modifier;

	y += g::fonts::config.height + y_distance;
}

void IntOption::while_not_selected(int x, int& y)
{
	g::fonts::config.print(title + L": " + std::to_wstring(*i).substr(0, 5), g::screen_width / 4, y, colors::red);

	y += g::fonts::config.height + y_distance;
}