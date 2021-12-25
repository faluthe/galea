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

void sdk::debug::print(const std::string& str)
{
#ifdef DEBUG
	std::cout << "[+] " << str << "\n";
#endif
}

void sdk::debug::print_address(const std::string& title, uintptr_t address, bool is_offset)
{
#ifdef DEBUG
	if (is_offset)
		std::cout << "[+] Found " << title << " at offset 0x" << std::hex << address << "\n";
	else
		std::cout << "[+] Found " << title << " at 0x" << std::hex << address << "\n";
#endif
}

void sdk::debug::error(const std::string& message)
{
#ifdef DEBUG
	std::cout << "[-] Error: " << message << "\n";
	
	// Wait for uninjection
	while (true)
		Sleep(1000);
#endif
}