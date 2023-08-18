#include <fmath.h>

#include "nlts_data.h"
#include "maps_desc.h"

const uint16_t flash_nlts_speed_averaging_rate = 128;
DECLARE_VALUE_DESC(flash_nlts_speed_averaging_rate, "NLTS", "Vehicle Speed Averaging Rate", "uint16");

const uint16_t flash_nlts_rpm_overshoot = 64;
DECLARE_VALUE_DESC(flash_nlts_rpm_overshoot, "NLTS", "Engine RPM Overshoot", "RPM");

const uint16_t flash_init_nlts_active_decay = 120;
DECLARE_VALUE_DESC(flash_init_nlts_active_decay, "NLTS", "Active Time Limit", "Time");

const uint16_t flash_init_nlts_active_decay_partial_engagement = 40;
DECLARE_VALUE_DESC(flash_init_nlts_active_decay_partial_engagement, "NLTS", "Partial Clutch Engagement Active Time Limit", "Time");

const uint16_t flash_nlts_delta_holdoff = 5;
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

#if 0
const uint16_t flash_nlts_gear_ratios[7] = {
	0,
	2328,
	3484,
	4723,
	6158,
	7803,
	9774,
};
#elif MACHINE_EVOX_MT
const uint16_t flash_nlts_gear_ratios[7] = {
	0,
	37,
	55,
	74,
	97,
	141,
	141,
};
#elif MACHINE_EVOX_MT_GP43
const uint16_t flash_nlts_gear_ratios[7] = {
	0,
	40,
	59,
	79,
	104,
	151,
	151,
};
#endif
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

const uint16_t flash_nlts_gear_down_rpm_max = 256 * 2;
DECLARE_VALUE_DESC(flash_nlts_gear_down_rpm_max, "NLTS", "Gear Down RPM Max", "RPM");

const uint8_t flash_nlts_gear_max = 6;
DECLARE_VALUE_DESC(flash_nlts_gear_max, "NLTS", "Gear Max", "uint8");
