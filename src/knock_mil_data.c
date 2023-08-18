#include <stdint.h>
#include <maps_desc.h>

const uint16_t flash_init_knock_mil_flash_timer[4] = {
	0, 40, 20, 10,
};
DECLARE_ARRAY_DESC(flash_init_knock_mil_flash_timer,
	"KnockCEL",
	"Flash Period",
	"Time",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"4\">"
	"<data>Leave0</data>"
	"<data>Low</data>"
	"<data>Med</data>"
	"<data>High</data>"
	"</table>");

const uint16_t flash_init_knock_mil_flash_decay = 80;
DECLARE_VALUE_DESC(flash_init_knock_mil_flash_decay,
	"KnockCEL",
	"Flash Sequence Duration",
	"Time");

const uint8_t flash_knock_mil_thresholds[6] = { 3, 5, 6, 8, 9, 11 };
DECLARE_ARRAY_DESC(flash_knock_mil_thresholds,
	"KnockCEL",
	"KnockSum Thresholds",
	"uint8",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"6\">"
	"<data>Low->Off</data>"
	"<data>Off->Low</data>"
	"<data>Med->Low</data>"
	"<data>Low->Med</data>"
	"<data>High->Med</data>"
	"<data>Med->High</data>"
	"</table>");

#ifndef KNOCK_MIL_LOAD_MIN
#define KNOCK_MIL_LOAD_MIN 320
#endif

const uint16_t flash_knock_mil_load_min = KNOCK_MIL_LOAD_MIN;//100% load
DECLARE_VALUE_DESC(flash_knock_mil_load_min,
	"KnockCEL",
	"Load Min",
	"Load");

const uint16_t flash_knock_mil_tps_min = 0x80;//50% tps
DECLARE_VALUE_DESC(flash_knock_mil_tps_min,
	"KnockCEL",
	"TPS Min",
	"Throttle %");

const uint8_t flash_drop_knock_cel_on_low_tps_and_load = 0;
DECLARE_VALUE_DESC(flash_drop_knock_cel_on_low_tps_and_load,
	"KnockCEL",
	"Drop Flash sequence on low TPS and Load",
	"uint8");
