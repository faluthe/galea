#include <deque>

#include "../valve/CNetChan.h"
#include "../sdk/interfaces/interfaces.h"
#include "features.h"

struct sequence_data
{
	int m_nInReliableState;
	int m_nInSequenceNr;
	float realtime;
};

std::deque<sequence_data> sequences;

void features::backtrack::add_latency(CNetChan* netchan, float latency)
{
	for (auto& seq : sequences)
	{
		if (ifaces::global_vars->realtime - seq.realtime >= latency)
		{
			netchan->m_nInReliableState = seq.m_nInReliableState;
			netchan->m_nInSequenceNr = seq.m_nInSequenceNr;
			break;
		}
	}
}

void features::backtrack::update_sequences()
{
	if (ifaces::netchan && ifaces::netchan->m_nInSequenceNr > last_sequence)
	{
		last_sequence = ifaces::netchan->m_nInSequenceNr;
		sequences.push_front(sequence_data{
			ifaces::netchan->m_nInReliableState,
			ifaces::netchan->m_nInSequenceNr,
			ifaces::global_vars->realtime });
	}

	if (sequences.size() > 2048)
		sequences.pop_back();
}