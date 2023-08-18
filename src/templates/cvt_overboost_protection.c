#include <maps_desc.h>


DECLARE_ARRAY_DESC(flash_overboost_limit_steps,
	"CVT Overboost",
	"Throttle Limit Steps",
	"uint16",
	"<table name=\"Type\" type=\"Static X Axis\" elements=\"2\">\n"
	"\t\t<data>Inc</data>\n"
	"\t\t<data>Dec</data>\n"
	"</table>");

DECLARE_AXIS_DESC_EX(flash_basic_rpm_axis, "RPM", "RPM");

DECLARE_2DMAP8_DESC(flash_overboost_on_load8_vs_rpm_2dmap8,
	"CVT Overboost",
	"Load Above Restricted, 255 Unrestricted",
	"Load8",
	"DXflash_basic_rpm_axis");

DECLARE_2DMAP8_DESC(flash_overboost_off_load8_vs_rpm_2dmap8,
	"CVT Overboost",
	"Load Below Prerequisites Cooldown",
	"Load8",
	"DXflash_basic_rpm_axis");

DECLARE_2DMAP8_DESC(flash_overboost_off_wastegate_duty_vs_rpm_2dmap8,
	"CVT Overboost",
	"WGDC Above Prerequisites Cooldown",
	"WGDC",
	"DXflash_basic_rpm_axis");
