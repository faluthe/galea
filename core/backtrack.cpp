#include <algorithm>

#include "../sdk/classes/entity/player.h"
#include "../sdk/classes/entity/record.h"
#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "../valve/ConVar.h"
#include "features.h"

struct Cvars
{
	ConVar* updaterate;
	ConVar* maxupdaterate;
	ConVar* interp;
	ConVar* interp_ratio;
	ConVar* min_interp_ratio;
	ConVar* max_interp_ratio;
	ConVar* maxunlag;
};

Cvars init_cvars()
{
	// # of snapshots requested from server per second
	auto updaterate = ifaces::cvar->FindVar("cl_updaterate");
	// Maximum amount of updates the server allows
	auto maxupdaterate = ifaces::cvar->FindVar("sv_maxupdaterate");
	// Interpolation period in seconds (usually 0, interp_ratio used instead)
	auto interp = ifaces::cvar->FindVar("cl_interp");
	// Interpolation period = (ratio / updaterate)
	auto interp_ratio = ifaces::cvar->FindVar("cl_interp_ratio");
	// Server's min/max interp ratio
	auto min_interp_ratio = ifaces::cvar->FindVar("sv_client_min_interp_ratio");
	auto max_interp_ratio = ifaces::cvar->FindVar("sv_client_max_interp_ratio");
	// Max time the server will rewind during lag compensation (in seconds)
	auto maxunlag = ifaces::cvar->FindVar("sv_maxunlag");

	return Cvars{ updaterate, maxupdaterate, interp, interp_ratio, min_interp_ratio, max_interp_ratio, maxunlag };
}

int time_to_ticks(float time)
{

}

bool valid_tick(float simtime)
{

}

// Updates g::lagcomp_records
void features::backtrack::update_records()
{
	// If the localplayer is dead, discard all records
	if (!g::localplayer->valid_ptr() || !g::localplayer->is_alive())
	{
		for (auto& record : g::lagcomp_records)
			record.clear();
		return;
	}

	for (int i = 1; i <= ifaces::engine->GetMaxClients(); i++)
	{
		auto ent = ifaces::entity_list->GetClientEntity<Player>(i);

		// Clear entity's record if entity not valid
		if (!ent->valid_ptr() || !ent->is_alive() || ent->is_dormant() || ent->team() == g::localplayer->team())
		{
			g::lagcomp_records[i].clear();
			continue;
		}

		// Continue if we already have the most recent record
		if (!g::lagcomp_records[i].empty() && g::lagcomp_records[i].front().sim_time == ent->sim_time())
			continue;

		Record record{};
		record.origin = ent->origin();
		record.sim_time = ent->sim_time();
		// Get entity's bone to world matrix (used for chams/rendering)
		ent->setup_bones(record.bone_matrix, 128, 0x7FF00, ifaces::global_vars->curtime);

		// New ticks are added to the front, old records are popped from the back
		g::lagcomp_records[i].push_front(record);

		// Store between 3 ticks and 200 milliseconds worth of ticks
		while (g::lagcomp_records[i].size() > 3 && g::lagcomp_records[i].size() > time_to_ticks(0.2f))
			g::lagcomp_records[i].pop_back();

		auto rstart = std::cbegin(g::lagcomp_records[i]);
		auto rend = std::cend(g::lagcomp_records[i]);
		// Find the first invalid tick, if any
		auto invalid_tick = std::find_if(rstart, rend, [](const Record& r) { return !valid_tick(r.sim_time); });

		// Delete all invalid ticks
		if (invalid_tick != rend)
			g::lagcomp_records[i].erase(invalid_tick, rend);
	}
}