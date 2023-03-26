#include <string>

#include "../core/configuration/config.h"
#include "../sdk/classes/rendering/color.h"
#include "../sdk/classes/entity/player.h"
#include "../sdk/classes/math/matrix.h"
#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "../hooks/hooks.h"
#include "../valve/IVModelRender.h"
#include "features.h"

static IMaterial* setup_material(const char* material_name)
{
	// This implementation is temporary
	auto material = ifaces::mat_sys->FindMaterial(material_name, "Model textures");
	material->SetMaterialVarFlags(MaterialVarFlags_t::MATERIAL_VAR_NO_DRAW, false);

	return material;
}

static void render(IMaterial* material, const Color& color, bool ignore_z)
{
	material->ColorModulate(color.r / 255.f, color.g / 255.f, color.b / 255.f);
	material->AlphaModulate(color.a / 255.f);
	material->SetMaterialVarFlags(MaterialVarFlags_t::MATERIAL_VAR_IGNOREZ, ignore_z);

	ifaces::studio_render->ForcedMaterialOverride(material);
}

void features::chams(void* _this, void* _edx, void* pRenderContext, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, Matrix3x4* pCustomBoneToWorld)
{
	if (!config::chams || !g::localplayer->valid_ptr() || pInfo.pModel == nullptr)
		return;

	if (strstr(pInfo.pModel->name, "models/player") != nullptr)
	{
		const auto ent = ifaces::entity_list->GetClientEntity<Player>(pInfo.entity_index);

		if (!ent->valid_ptr() || ent->is_dormant() || !ent->is_alive() || ent == g::localplayer)
			return;

		static auto debug_material = setup_material("debug/debugambientcube");
		static auto flat_material = setup_material("debug/debugdrawflat");
		static auto wire_material = setup_material("debug/debugwireframe");

		if (ent->team() != g::localplayer->team())
		{
			if (config::ignore_z) {
				render(debug_material, config::colors::enemy_hidden, true);
				hooks::oDrawModelExecute(_this, _edx, pRenderContext, state, pInfo, pCustomBoneToWorld);
			}

			if (!g::lagcomp_records[pInfo.entity_index].empty())
			{
				auto interp_color = config::colors::enemy_visible;
				interp_color.a = 45;
				int target_tick = g::lagcomp_records[pInfo.entity_index].size();
				for (size_t i = 0; i < g::lagcomp_records[pInfo.entity_index].size(); i++)
				{
					interp_color.r += 4;
					interp_color.g += 4;
					interp_color.b += 4;
					auto record = &g::lagcomp_records[pInfo.entity_index][i];
					if (!record || record->bone_matrix == nullptr || !features::backtrack::valid_tick(record->sim_time))
						continue;
					if (config::render_target_tick && pInfo.entity_index == features::backtrack::target && i == features::backtrack::record)
						target_tick = i;
					else if (config::backtrack_chams)
					{
						render(flat_material, interp_color, false);
						hooks::oDrawModelExecute(_this, _edx, pRenderContext, state, pInfo, record->bone_matrix);
					}
				}
				// Render target tick on top
				if (static_cast<size_t>(target_tick) < g::lagcomp_records[pInfo.entity_index].size())
				{
					render(flat_material, config::colors::target_tick, false);
					hooks::oDrawModelExecute(_this, _edx, pRenderContext, state, pInfo, g::lagcomp_records[pInfo.entity_index][target_tick].bone_matrix);
				}
			}

			render(debug_material, config::colors::enemy_visible, false);
		}
	}
}