#pragma once

#include <deque>

#include "../classes/entity/player.h"
#include "../classes/entity/record.h"
#include "../classes/rendering/font.h"

namespace g
{
	namespace fonts
	{
		void setup_fonts();

		inline Font config;
	}

	void get_localplayer();
	void get_screen_size();
	
	inline std::deque<Record> lagcomp_records[65];
	inline Player* localplayer{};
	inline int screen_width{};
	inline int screen_height{};
	inline int screen_center_x{};
	inline int screen_center_y{};
}