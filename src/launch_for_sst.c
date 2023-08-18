#include "launch_for_sst.h"
#include <fmath.h>

extern const void *const flash_fuel_map_rpm_axis;
extern const void *const flash_fuel_map_load_axis;
extern uint16_t fuel_map_target_afr;
extern uint16_t vehicle_speed_frequency;
extern uint16_t get_fuel_map_load_source();

//#define IS_LAUNCH_ON ((apps_main > flash_launch_apps_threshold) && (vehicle_speed_frequency < flash_launch_speed_threshold))
#define IS_LAUNCH_ON (vehicle_speed_frequency < flash_launch_speed_threshold)

void hijack_update_fuel_map_target_afr()
{
	update_fuel_map_target_afr();
	if (!IS_LAUNCH_ON)
		return;

	calc_axis(&flash_fuel_map_rpm_axis);
	temp_axis_src = get_fuel_map_load_source();
	calc_axis(&flash_fuel_map_load_axis);
	uint_fast16_t l_afr_limit = map8u16(&flash_launch_afr_lean_limit_3dmap8);
	if (fuel_map_target_afr < l_afr_limit)
		fuel_map_target_afr= l_afr_limit;
}

uint16_t hijack_get_mapped_spark_advance()
{
	uint_fast16_t l_spark = get_mapped_spark_advance();
	if (IS_LAUNCH_ON) {
		calc_axis(&flash_fuel_map_rpm_axis);
		temp_axis_src = get_fuel_map_load_source();
		calc_axis(&flash_fuel_map_load_axis);
		uint_fast16_t l_spark_limit = map8u16(&flash_launch_spark_advance_limit_3dmap8);
		if (l_spark_limit < l_spark)
			l_spark = l_spark_limit;
	}
	return l_spark;
}
