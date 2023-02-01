#pragma once

class Hook
{
private:
	void* pInterface;
public:
	Hook(void* pInterface) : pInterface{ pInterface } {}
	void hook_function(unsigned short index, void* hkFunc, void** oFunc);
};

namespace hooks
{
	inline void(__fastcall* oDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, const ModelRenderInfo_t&, void*);

	void init();
	void restore_all();
}