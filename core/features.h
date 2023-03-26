#pragma once

#include "../sdk/classes/math/matrix.h"
#include "../valve/CNetChan.h"
#include "../valve/CUserCmd.h"
#include "../valve/IVModelRender.h"

namespace features
{
	namespace backtrack
	{
		void add_latency(CNetChan* netchan, float latency);
		void disable_interpolation();
		void update_records();
		void update_sequences();
		void run(CUserCmd* cmd);
		bool valid_tick(float simtime);

		inline int target{};
		inline int record{};
		inline int last_sequence{ 0 };
	}

	namespace esp
	{
		void crosshair();
		void lerp_test();
		inline float lerp{};
	}

	void autopistol(CUserCmd* cmd);
	void bunnyhop(CUserCmd* cmd);
	void chams(void* _this, void* _edx, void* pRenderContext, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, Matrix3x4* pCustomBoneToWorld);
	void skinchanger();
	void triggerbot(CUserCmd* cmd);
}