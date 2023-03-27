#include "../sdk/classes/entity/weapon.h"
#include "../sdk/interfaces/interfaces.h"
#include "../sdk/globals/globals.h"
#include "features.h"

struct Knife
{
	const char* model;
	int def_index;
};

// Paint kits
constexpr int SAPPHIRE_DOPPLER = 421;
constexpr int BLUE_DOPPLER = 416;
constexpr int RED_DOPPLER = 415;
constexpr int BLACK_PEARL = 417;
constexpr int TIGER_TOOTH = 409;
constexpr int M9_LORE = 562;
constexpr int MARBLE_FADE = 413;
constexpr int M9_AUTOTRONIC = 577;
constexpr int SLAUGHTER = 59;
constexpr int CRIMSON_WEB = 12;
constexpr int CASE_HARDENED = 44;
constexpr int FADE = 38;

// Models
Knife M9_BAYONET = Knife{ "models/weapons/v_knife_m9_bay.mdl", 508 };
Knife BAYONET = Knife{ "models/weapons/v_knife_bayonet.mdl", 500 };
Knife FLIP_KNIFE = Knife{ "models/weapons/v_knife_flip.mdl", 505 };
Knife GUT_KNIFE = Knife{ "models/weapons/v_knife_gut.mdl", 506 };
Knife KARAMBIT = Knife{ "models/weapons/v_knife_karam.mdl", 507 };
Knife HUNTSMAN = Knife{ "models/weapons/v_knife_tactical.mdl", 509 };
Knife FALCHION = Knife{ "models/weapons/v_knife_falchion_advanced.mdl", 512 };
Knife BOWIE = Knife{ "models/weapons/v_knife_survival_bowie.mdl", 514 };
Knife BUTTERFLY = Knife{ "models/weapons/v_knife_butterfly.mdl", 515 };
Knife SHADOW_DAGGERS = Knife{ "models/weapons/v_knife_push.mdl", 516 };

// Skin changer is limited for now, I'd rather focus elsewhere
void features::skinchanger()
{
	int knife_paint_kit = RED_DOPPLER;
	Knife knife = M9_BAYONET;

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
			auto index = ifaces::mdl_info->GetModelIndex(knife.model);
			view_model->model_index() = index;

			const auto worldModel = ifaces::entity_list->GetEntityFromHandle<ViewmodelEnt>(vm_weapon->world_model());

			if (!worldModel)
				return;

			worldModel->model_index() = index + 1;
		}

		if (weapon_ent->is_knife())
		{
			weapon_ent->item_def_index() = knife.def_index;
			weapon_ent->paint_kit() = knife_paint_kit;
			weapon_ent->model_index() = ifaces::mdl_info->GetModelIndex(knife.model);
			weapon_ent->quality() = 3;
			weapon_ent->wear() = 0.001f;
		}

		weapon_ent->og_owner_low() = 0;
		weapon_ent->og_owner_high() = 0;
		weapon_ent->fallback_seed() = 403;
		weapon_ent->item_id() = -1;
	}
}