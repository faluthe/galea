#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/game/client/c_baseentity.h

struct VarMapEntry_t
{
	unsigned short type;
	unsigned short m_bNeedsToInterpolate;
	void* data;
	void* watcher;
};

struct VarMapping_t
{
	VarMapEntry_t* m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationtime;
};