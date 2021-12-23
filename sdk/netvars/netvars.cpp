#include <stdexcept>
#include <string>

#include "../interfaces/interfaces.h"
#include "../../valve/ClientClass.h"
#include "netvars.h"
#include "../../valve/Recv.h"

static uintptr_t check_recvtable(RecvTable* table, const char* table_name, const char* netvar_name)
{
	for (int i{ 0 }; i < table->m_nProps; i++)
	{
		const auto prop{ table->m_pProps[i] };

		if (!_stricmp(prop.m_pVarName, netvar_name))
			return prop.m_Offset;

		if (prop.m_pDataTable)
		{
			const auto offset = check_recvtable(prop.m_pDataTable, table_name, netvar_name);

			if (offset)
				return offset + prop.m_Offset;
		}
	}

	return 0;
}

uintptr_t netvars::get_netvar(const char* table_name, const char* netvar_name)
{
	if (!ifaces::client)
		return 0;

	static ClientClass* client_class{ ifaces::client->GetAllClasses() };

	for (auto current_node = client_class; current_node; current_node = current_node->m_pNext)
	{
		if (!_stricmp(table_name, current_node->m_pRecvTable->m_pNetTableName))
			return check_recvtable(current_node->m_pRecvTable, table_name, netvar_name);
	}

	throw std::runtime_error(std::string{ "Failed to get netvar: " } + netvar_name);
}