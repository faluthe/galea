#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/engine/net_chan.h

#include <cstddef>

struct CNetChan
{
    std::byte pad_0000[24];
    int m_nOutSequenceNr;
    int m_nInSequenceNr;
    int m_nOutSequenceNrAck;
    int m_nOutReliableState;
    int m_nInReliableState;
    int m_nChokedPackets;
    std::byte pad_0030[108];
    int m_Socket;
    int m_StreamSocket;
    int m_MaxReliablePayloadSize;
    std::byte pad_00A8[100];
    float last_received;
    float connect_time;
    std::byte pad_0114[4];
    int m_Rate;
    std::byte pad_011C[4];
    float m_fClearTime;
    std::byte pad_0124[16688];
    char m_Name[32];
    unsigned int m_ChallengeNr;
    float m_flTimeout;
    std::byte pad_427C[32];
    float m_flInterpolationAmount;
    float m_flRemoteFrameTime;
    float m_flRemoteFrameTimeStdDeviation;
    int m_nMaxRoutablePayloadSize;
    int m_nSplitPacketSequence;
    std::byte pad_42B0[40];
    bool m_bIsValveDS;
    std::byte pad_42D9[65];
};