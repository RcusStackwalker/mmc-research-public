#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>
#include <mode_selector.h>

#define BOOST_CONTROL_RPM_AXIS_SIZE 16

#define DECLARE_EMPTY_TEMP_2DMAP_WITH_DESC(name, size, username, scaling) \
DECLARE_2DMAP8_WITH_DESC(name, \
	size, \
	"Alt Maps", \
	username, \
	scaling, \
	"DXflash_boost_control_rpm_axis") = { \
	TEMP_2DMAP_SRC, \
	.data = { }, \
}

extern const void *const flash_boost_target_load_low_gear_2dmap8;
extern const void *const flash_boost_target_load_high_gear_2dmap8;
extern const void *const flash_wastegate_base_duty_low_gear_2dmap8;
extern const void *const flash_wastegate_base_duty_high_gear_2dmap8;


DECLARE_EMPTY_TEMP_2DMAP_WITH_DESC(flash_alt_boost_target_load_low_gear_2dmap8, BOOST_CONTROL_RPM_AXIS_SIZE, "Boost Target Load - Low Gear", "Load8");
DECLARE_EMPTY_TEMP_2DMAP_WITH_DESC(flash_alt_boost_target_load_high_gear_2dmap8, BOOST_CONTROL_RPM_AXIS_SIZE, "Boost Target Load - High Gear", "Load8");
DECLARE_EMPTY_TEMP_2DMAP_WITH_DESC(flash_alt_wastegate_duty_low_gear_2dmap8, BOOST_CONTROL_RPM_AXIS_SIZE, "Base Wastegate Duty - Low Gear", "WGDuty");
DECLARE_EMPTY_TEMP_2DMAP_WITH_DESC(flash_alt_wastegate_duty_high_gear_2dmap8, BOOST_CONTROL_RPM_AXIS_SIZE, "Base Wastegate Duty - High Gear", "WGDuty");

const void *const flash_boost_target_load_low_gear_2dmultimap8[MODE_COUNT] = {
	&flash_boost_target_load_low_gear_2dmap8,
	&flash_alt_boost_target_load_low_gear_2dmap8,
};

const void *const flash_boost_target_load_high_gear_2dmultimap8[MODE_COUNT] = {
	&flash_boost_target_load_high_gear_2dmap8,
	&flash_alt_boost_target_load_high_gear_2dmap8,
};
		  
const void *const flash_base_wastegate_duty_low_gear_2dmultimap8[MODE_COUNT] = {
	&flash_wastegate_base_duty_low_gear_2dmap8,
	&flash_alt_wastegate_duty_low_gear_2dmap8,
};

const void *const flash_base_wastegate_duty_high_gear_2dmultimap8[MODE_COUNT] = {
	&flash_wastegate_base_duty_high_gear_2dmap8,
	&flash_alt_wastegate_duty_high_gear_2dmap8,
};
