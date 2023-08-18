#include <fmath.h>
#include "map_limits_data.h"

extern uint16_t temp_axis_src;

extern uint8_t mat;
extern uint16_t manifold_pressure;//16384 discretes per 100kpa
extern uint16_t map_load_base;
extern uint16_t map_load;

extern uint16_t maf_charge_min;
extern uint16_t maf_charge_max;
extern uint16_t maf_charge_min_compensated;
extern uint16_t maf_charge_max_compensated;
extern uint16_t warmup_fuel_correction;
extern uint16_t adc_full_fuel_temperature;
extern uint16_t adc_full_fuel_tank_pressure;
extern uint16_t engine_rpm;
extern uint16_t baro_pressure;
extern uint16_t default_maf_scaled1;
extern uint16_t fp12256_f16;

extern const void *const flash_fuel_temperature_sensor_axis;
extern const void *const flash_fuel_temperature_sensor_characteristic_2dmap16;

void new_update_air_mass_compensations_and_limits()
{
	temp_axis_src = adc_full_fuel_temperature;
	calc_axis(&flash_fuel_temperature_sensor_axis);

	mat = ps_divu16(mapu16(&flash_fuel_temperature_sensor_characteristic_2dmap16), 10);
	
	temp_axis_src = adc_full_fuel_tank_pressure;
	calc_axis(&flash_map_sensor_axis);

	manifold_pressure = mapu16(&flash_map_sensor_characteristic_2dmap16);

	temp_axis_src = manifold_pressure;
	calc_axis(&flash_map_limits_manifold_pressure_axis);

	temp_axis_src = engine_rpm;
	calc_axis(&flash_map_limits_engine_rpm_axis);

	map_load_base = mapu16(&flash_map_limits_load_3dmap16);//32768 per 100%


	uint16_t l_result = map_load_base;

	temp_axis_src = mat;
	calc_axis(&flash_mat_axis);
	l_result = ps_scale_base128(l_result, map8u16(&flash_map_limits_load_mat_compensation_2dmap8));

	temp_axis_src = baro_pressure;
	calc_axis(&flash_map_limits_baro_axis);
	l_result = ps_scale_base128(l_result, map8u16(&flash_map_limits_load_baro_compensation_2dmap8));

	map_load = l_result;

	maf_charge_min = ps_scale_base256(map_load, flash_map_load_low_limit_correction);
	maf_charge_max = ps_scale_base256(map_load, flash_map_load_high_limit_correction);

	default_maf_scaled1 = 0xffff;

	fp12256_f16 &= ~0x40;

	maf_charge_max_compensated = ps_scale_base128(maf_charge_max, warmup_fuel_correction);
	maf_charge_min_compensated = ps_scale_base128(maf_charge_min, warmup_fuel_correction);
}
