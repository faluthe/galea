#include <string>

#include "../core/configuration/config.h"
#include "../sdk/classes/rendering/color.h"
#include "../sdk/classes/entity/player.h"
#include "../sdk/globals/globals.h"
#include "../sdk/interfaces/interfaces.h"
#include "../hooks/hooks.h"
#include "../valve/IVModelRender.h"
#include "features.h"

static IMaterial* setup_material()
{
	// This implementation is temporary
	auto material = ifaces::mat_sys->FindMaterial("debug/debugambientcube", "Model textures");
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

void features::chams(void* _this, void* _edx, void* pRenderContext, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld)
{
	if (!config::chams || !g::localplayer->valid_ptr() || pInfo.pModel == nullptr)
		return;

	if (strstr(pInfo.pModel->name, "models/player") != nullptr)
	{
		const auto ent = ifaces::entity_list->GetClientEntity<Player>(pInfo.entity_index);

		if (!ent->valid_ptr() || !ent->is_alive() || ent == g::localplayer)
			return;

		static auto player_material = setup_material();

		if (ent->team() != g::localplayer->team())
		{
			render(player_material, config::colors::enemy_hidden, true);
			hooks::oDrawModelExecute(_this, _edx, pRenderContext, state, pInfo, pCustomBoneToWorld);

			render(player_material, config::colors::enemy_visible, false);
		}
	}
}