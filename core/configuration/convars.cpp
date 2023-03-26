#include "../../sdk/interfaces/interfaces.h"
#include "config.h"

namespace config::convars {
	void set() {
		// Should always be set (awp crosshair)
		ifaces::cvar->FindVar("weapon_debug_spread_show")->SetInt(2);

		if (apollo) {
			ifaces::cvar->FindVar("r_3dsky")->SetInt(0);
			ifaces::cvar->FindVar("sv_skyname")->SetString("sky_lunacy");
		}

		if (crosshair_mode == 1) {
			ifaces::cvar->FindVar("cl_crosshair_recoil")->SetInt(1);
		}
		else 
		{
			ifaces::cvar->FindVar("cl_crosshair_recoil")->SetInt(0);
		}

		if (nade_preview) {
			ifaces::cvar->FindVar("cl_grenadepreview")->SetInt(1);
		}

		if (stretched_ratio) {
			ifaces::cvar->FindVar("r_aspectratio")->SetFloat(1.33f);
		}
		else 
		{
			ifaces::cvar->FindVar("r_aspectratio")->SetFloat(0.f);
		}
	}
	void restore() {
		ifaces::cvar->FindVar("r_3dsky")->SetInt(1);
		// You're stranded on the moon :(
		ifaces::cvar->FindVar("cl_crosshair_recoil")->SetInt(0);
		ifaces::cvar->FindVar("weapon_debug_spread_show")->SetInt(0);
		ifaces::cvar->FindVar("cl_grenadepreview")->SetInt(0);
		ifaces::cvar->FindVar("r_aspectratio")->SetFloat(0.f);
	}
}