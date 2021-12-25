#include <string>

#include "../interfaces/interfaces.h"
#include "globals.h"

void g::get_localplayer()
{
	localplayer = ifaces::entity_list->GetClientEntity<Player>(ifaces::engine->GetLocalPlayer());
	
	if (localplayer)
		sdk::debug::print_address("localplayer", reinterpret_cast<uintptr_t>(localplayer));
}

void g::get_screen_size()
{
	int new_width, new_height;

	ifaces::engine->GetScreenSize(new_width, new_height);

	if (new_width != screen_width || new_height != screen_height)
	{
		screen_width = new_width;
		screen_height = new_height;

		screen_center_x = screen_width / 2;
		screen_center_y = screen_height / 2;

		sdk::debug::print("Window size: " + std::to_string(screen_width) + "x" + std::to_string(screen_height));

		// If the screen size is changed, fonts need to be re-initialized
		fonts::setup_fonts();
	}
}

void g::fonts::setup_fonts()
{
	config.setup(20, 500, 0x200);

	sdk::debug::print("Fonts set");
}