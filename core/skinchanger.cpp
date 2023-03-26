#include "../sdk/classes/entity/weapon.h"
#include "../sdk/interfaces/interfaces.h"
#include "../sdk/globals/globals.h"
#include "features.h"

void features::skinchanger()
{
	if (!g::localplayer || !g::localplayer->is_alive())
		return;

	auto weapon = g::localplayer->active_weapon();

	if (!weapon)
		return;

	for (auto handle : g::localplayer->my_weapons())
	{
		auto weapon_ent = ifaces::entity_list->GetEntityFromHandle<Weapon>(handle);

		if (!weapon_ent)
			return;

		if (weapon->is_knife())
		{
			auto view_model = ifaces::entity_list->GetEntityFromHandle<ViewmodelEnt>(g::localplayer->view_model());

			if (!view_model)
				return;

			const auto vm_weapon = ifaces::entity_list->GetEntityFromHandle<Weapon>(view_model->hWeapon());

			if (!view_model)
				return;

			// need to change item def index too
			auto index = ifaces::mdl_info->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			view_model->model_index() = index;

			const auto worldModel = ifaces::entity_list->GetEntityFromHandle<ViewmodelEnt>(vm_weapon->world_model());

			if (!worldModel)
				return;

			worldModel->model_index() = index + 1;
		}

		if (weapon_ent->is_knife())
		{
			weapon_ent->item_def_index() = 508;
			weapon_ent->paint_kit() = 421;
			weapon_ent->model_index() = ifaces::mdl_info->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			weapon_ent->quality() = 3;
			weapon_ent->wear() = 0.001f;
		}

		weapon_ent->og_owner_low() = 0;
		weapon_ent->og_owner_high() = 0;
		weapon_ent->fallback_seed() = 403;
		weapon_ent->item_id() = -1;
	}
}