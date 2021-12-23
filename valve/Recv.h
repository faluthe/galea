#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/dt_recv.h

#include <cstddef>

struct RecvTable;

struct RecvProp
{
    char* m_pVarName;
    std::byte pad0[4];
    int m_Flags;
    int m_StringBufferSize;
    int m_bInsideArray;
    const void* m_pExtraData;
    RecvProp* m_pArrayProp;
    std::byte pad1[12];
    RecvTable* m_pDataTable;
    int m_Offset;
    int m_ElementStride;
    int m_nElements;
    const char* m_pParentArrayPropName;
};

struct RecvTable
{
    RecvProp* m_pProps;
    int m_nProps;
    void* m_pDecoder;
    char* m_pNetTableName;
};