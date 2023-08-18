#include <fmath.h>
#include <maps_desc.h>

extern uint8_t current_gear;
extern uint16_t accel_characteristic_limit;

const uint8_t flash_accel_limits_per_gear[7] = { 0x60, 0x60, 0xff, 0xff, 0xff, 0xff, 0xff };
DECLARE_ARRAY_DESC(flash_accel_limits_per_gear,
	"GearControl",
	"Accelerator Characteristic Limit - Gear",
	"uint8",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"7\">"
	"<data>0</data>"
	"<data>1</data>"
	"<data>2</data>"
	"<data>3</data>"
	"<data>4</data>"
	"<data>5</data>"
	"<data>6</data>"
	"</table>");

void new_update_accel_characteristic_limit()
{
	accel_characteristic_limit = flash_accel_limits_per_gear[current_gear];
}
