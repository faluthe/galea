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
	// Has to be here because its called in features::chams()
	inline void(__fastcall* oDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, const ModelRenderInfo_t&, void*);

	void init();
	void restore_all();
}

enum class FrameStage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};