#include "maps_desc.h"

DECLARE_AXIS_DESC_EX(flash_apps_to_ttp_correction_axis, "Accelerator Pedal Position", "Percent1024");
DECLARE_2DMAP8_DESC(flash_apps_to_ttp_correction_default_2dmap8,
	"Throttle",
	"APPS to Target Throttle Position Correction - Default",
	"Percent255U8",
	"DXflash_apps_to_ttp_correction_axis");

DECLARE_2DMAP8_DESC(flash_apps_to_ttp_correction_lowgear_2dmap8,
	"Throttle",
	"APPS to Target Throttle Position Correction - Low Gear",
	"Percent255U8",
	"DXflash_apps_to_ttp_correction_axis");

DECLARE_AXIS_DESC_EX(flash_tomo_apps_to_ttp_apps_axis, "APPS", "Percent1024");

DECLARE_2DMAP8_DESC(flash_tomo_apps_to_ttp_correction_max_2dmap8,
	"Throttle",
	"APPS to Target Throttle Position Correction - Torque Monitor (Max)",
	"Percent255U8",
	"DXflash_tomo_apps_to_ttp_apps_axis");
