#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/client_class.h

#include <cstddef>

#include "Recv.h"

enum class ClassId
{
	Ak47 = 1
};

struct ClientClass
{
	std::byte pad0[8];
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	ClassId m_ClassID;
};