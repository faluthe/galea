#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "configuration/config.h"
#include "features.h"

void features::esp::crosshair()
{
	if (!config::crosshair || !g::localplayer->valid_ptr() || !g::localplayer->is_alive())
		return;

	int x = g::screen_center_x - (g::screen_width / 90 * static_cast<int>(g::localplayer->aim_punch().y));
	int y = g::screen_center_y + (g::screen_width / 90 * static_cast<int>(g::localplayer->aim_punch().x));

	ifaces::surface->DrawSetColor(config::colors::crosshair);
	ifaces::surface->DrawLine(x + 5, y, x - 5, y);
	ifaces::surface->DrawLine(x, y + 5, x, y - 5);
}