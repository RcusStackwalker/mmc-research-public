#include <fmath.h>

#include <maps_decl.h>
#include <maps_desc.h>

#include "nlts_data.h"

const uint16_t flash_nlts_rpm_overshoot = 64;
DECLARE_VALUE_DESC(flash_nlts_rpm_overshoot, "NLTS", "Engine RPM Overshoot", "RPM");

const uint16_t flash_init_nlts_active_decay = 120;
DECLARE_VALUE_DESC(flash_init_nlts_active_decay, "NLTS", "Active Time Limit", "Time");

const uint16_t flash_init_nlts_active_decay_partial_engagement = 40;
DECLARE_VALUE_DESC(flash_init_nlts_active_decay_partial_engagement, "NLTS", "Partial Clutch Engagement Active Time Limit", "Time");

const uint16_t flash_nlts_delta_holdoff = 6;
DECLARE_VALUE_DESC(flash_nlts_delta_holdoff, "NLTS", "Clutch Engagement Detection Holdoff Time", "Time");

const uint16_t flash_nlts_rpm_delta_threshold = 13;//50rpm per 10ms is enough
DECLARE_VALUE_DESC(flash_nlts_rpm_delta_threshold, "NLTS", "Clutch Engagement Detection - Negative Engine RPM Delta", "RPM");

const uint16_t flash_nlts_app_thresholds[2] = { 250, 300 };
DECLARE_ARRAY_DESC(flash_nlts_app_thresholds,
	"NLTS",
	"APPS Threshold",
	"uint16",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"2\">"
	"<data>Off</data>"
	"<data>On</data>"
	"</table>");

const uint16_t flash_nlts_gear_down_rpm_max = 256 * 2;
DECLARE_VALUE_DESC(flash_nlts_gear_down_rpm_max, "NLTS", "Gear Down RPM Max", "RPM");


#define NLTS_RPM_AXIS_SIZE 7

DECLARE_AXIS_WITH_DESC(flash_nlts_rpm_axis,
	NLTS_RPM_AXIS_SIZE,
	"RPM",
	"RPM") = {
	TEMP_AXIS_SRC_XDST,
	.size = NLTS_RPM_AXIS_SIZE,
	.data = { 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700 }
};

#define NLTS_APPS_AXIS_SIZE 5

DECLARE_AXIS_WITH_DESC(flash_nlts_apps_axis,
	NLTS_APPS_AXIS_SIZE,
	"TPS[0.5-4.5V]",
	"VoltsADC1023") = {
	TEMP_AXIS_SRC_YDST,
	.size = NLTS_APPS_AXIS_SIZE,
	.data = { 250, 400, 500, 600, 750 }
};

DECLARE_3DMAP8_WITH_DESC(flash_nlts_fuelcut_holdoff_3dmap8,
	NLTS_RPM_AXIS_SIZE,
	NLTS_APPS_AXIS_SIZE,
	"NLTS",
	"Clutch Disengagement Fuel Cut Holdoff Time",
	"Time40HzU8",
	"DDflash_nlts_apps_axis",
	"DDflash_nlts_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.xsize = NLTS_RPM_AXIS_SIZE,
	.data = { 6, 4, 4, 3, 3, 0, 0,
		3, 3, 3, 3, 1, 0, 0,
		3, 3, 2, 1, 1, 0, 0 }
};

#ifdef NLTS_SIMPLE

const uint16_t flash_nlts_gear_ratio_high = 1600;
DECLARE_VALUE_DESC(flash_nlts_gear_ratio_high, "NLTS", "High Gear Ratio Threshold", "uint16");


const uint16_t flash_nlts_rpm_ratio_high = 256 * 10 / 13;
DECLARE_VALUE_DESC(flash_nlts_rpm_ratio_high, "NLTS", "Engine RPM Drop Ratio - High Gear", "Percent256U16");

const uint16_t flash_nlts_rpm_ratio_low = 256 * 10 / 15;
DECLARE_VALUE_DESC(flash_nlts_rpm_ratio_low, "NLTS", "Engine RPM Drop Ratio - Low Gear", "Percent256U16");

#else

DECLARE_ARRAY_DESC(flash_nlts_gear_ratios,
	"NLTS",
	"Gear Ratios",
	"uint16",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"7\">"
	"<data>0</data>"
	"<data>1</data>"
	"<data>2</data>"
	"<data>3</data>"
	"<data>4</data>"
	"<data>5</data>"
	"<data>6</data>"
	"</table>");

const uint8_t flash_nlts_gear_max = 6;
DECLARE_VALUE_DESC(flash_nlts_gear_max, "NLTS", "Gear Max", "uint8");

#endif
