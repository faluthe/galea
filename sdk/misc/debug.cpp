#include <iostream>
#include <stdexcept>
#include <string>
#include <Windows.h>

#include "../sdk.h"

#define DEBUG
static FILE* fStream;

void sdk::debug::create_console()
{
#ifdef DEBUG
	if (AllocConsole() == 0)
		throw std::runtime_error("Process already has associated console");
	
	freopen_s(&fStream, "CONOUT$", "w", stdout);
#endif
}

void sdk::debug::free_console()
{
#ifdef DEBUG
	fclose(fStream);
	FreeConsole();
#endif
}

void sdk::debug::print(const std::string str)
{
#ifdef DEBUG
	std::cout << "[+] " << str << "\n";
#endif
}