#include "../../sdk/interfaces/interfaces.h"
#include "config.h"

namespace config::convars {
	void set() {
		if (apollo) {
			ifaces::cvar->FindVar("r_3dsky")->SetInt(0);
			ifaces::cvar->FindVar("sv_skyname")->SetString("sky_lunacy");
		}
		if (crosshair_recoil) {
			ifaces::cvar->FindVar("cl_crosshair_recoil")->SetInt(1);
		}
		if (nade_preview) {
			ifaces::cvar->FindVar("cl_grenadepreview")->SetInt(1);
		}
	}
	void restore() {
		ifaces::cvar->FindVar("r_3dsky")->SetInt(1);
		// You're stranded on the moon :(
		ifaces::cvar->FindVar("cl_crosshair_recoil")->SetInt(0);
		ifaces::cvar->FindVar("cl_grenadepreview")->SetInt(0);
	}
}