#pragma once

class Hook
{
private:
	void* pInterface;
public:
	Hook(void* pInterface) : pInterface{ pInterface } {}
	void hook_function(unsigned short index, void* hkFunc, void* oFunc);
};

namespace hooks
{
	void init();
	void restore_all();
}