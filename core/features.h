#pragma once

#include "../sdk/classes/math/matrix.h"
#include "../valve/CUserCmd.h"
#include "../valve/IVModelRender.h"

namespace features
{
	namespace backtrack
	{
		void update_records();
		void run(CUserCmd* cmd);
		bool valid_tick(float simtime);

		inline int target{};
		inline int record{};
	}

	void autopistol(CUserCmd* cmd);
	void bunnyhop(CUserCmd* cmd);
	void chams(void* _this, void* _edx, void* pRenderContext, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, Matrix3x4* pCustomBoneToWorld);
}