#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "configuration/config.h"
#include "features.h"

void features::esp::crosshair()
{
	if (config::crosshair_mode != 2 || !g::localplayer->valid_ptr() || !g::localplayer->is_alive())
		return;

	int x = g::screen_center_x - static_cast<int>(g::screen_width / 90 * g::localplayer->aim_punch().y);
	int y = g::screen_center_y + static_cast<int>(g::screen_height / 90 * g::localplayer->aim_punch().x);

	ifaces::surface->DrawSetColor(config::colors::crosshair);
	ifaces::surface->DrawLine(x + 5, y, x - 5, y);
	ifaces::surface->DrawLine(x, y + 5, x, y - 5);
}

void features::esp::anti_flash()
{
	if (g::localplayer->valid_ptr())
		g::localplayer->flash_alpha() = config::anti_flash;
}

void features::esp::restore_flash()
{
	if (g::localplayer->valid_ptr())
		g::localplayer->flash_alpha() = 255.f;
}