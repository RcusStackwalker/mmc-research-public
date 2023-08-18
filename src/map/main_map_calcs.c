#include <fmath.h>
#include <maps_decl.h>

#include "main_map_calcs.h"

extern const uint16_t flash_map_scaling_kpa_per_volt;
extern const uint16_t flash_map_voltage_zero_offset;

extern uint16_t baro_pressure;
extern uint16_t adc_full_mat;
extern uint16_t adc_byte_mat;
extern uint16_t mat;

extern uint16_t adc_full_map;
extern uint16_t adc_byte_map;
extern uint16_t map_load_base;

extern uint32_t map_samples_sum;
extern uint32_t map_samples_sum_prev;
extern uint16_t map_samples;
extern uint16_t map_samples_prev;
extern uint16_t map_avg_voltage;//65536 per 5V
extern uint16_t map_avg16;

extern const void *const flash_fuel_temperature_sensor_axis;
extern const void *const flash_fuel_temperature_sensor_characteristic_2dmap16;

#define MAT_AXIS_SIZE 8

DECLARE_AXIS_WITH_DESC(flash_map_compensation_mat_axis,
	MAT_AXIS_SIZE,
	"MAT",
	"Temp") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAT_AXIS_SIZE,
	.data = {
		0,
		8,
		33,
		49,
		63,
		78,
		96,
		125
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_map_load_mat_compensation_2dmap8,
	MAT_AXIS_SIZE,
	"MAF Limits with MAP",
	"MAP Load - MAT Compensation",
	"Percent128U8",
	"DDflash_map_compensation_mat_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		128,
		128,
		128,
		128,

		128,
		128,
		128,
		128
	}
};


#define MAP_LIMITS_BARO_AXIS_SIZE 5

DECLARE_AXIS_WITH_DESC(flash_map_compensation_baro_axis,
	MAP_LIMITS_BARO_AXIS_SIZE,
	"Barometric Pressure",
	"Baro") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAP_LIMITS_BARO_AXIS_SIZE,
	.data = {
		0x5d,
		0x7d,
		0x9d,
		0xad,
		0xbd
	}
};


DECLARE_2DMAP8_WITH_DESC(flash_map_load_baro_compensation_2dmap8,
	MAP_LIMITS_BARO_AXIS_SIZE,
	"MAF Limits with MAP",
	"MAP Load - Baro Compensation",
	"Percent128U8",
	"DDflash_map_compensation_baro_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		128,
		128,
		128,
		128,
		128
	}
};

#define MAP_LIMITS_RPM_AXIS_SIZE 16

DECLARE_AXIS_WITH_DESC(flash_map_engine_rpm_axis,
	MAP_LIMITS_RPM_AXIS_SIZE,
	"RPM",
	"RPM") = {
	.dst = MAP_RPM_AXIS_DST,
	.src = MAP_RPM_AXIS_SRC,
	.size = MAP_LIMITS_RPM_AXIS_SIZE,
	.data = {
		0x000,
		0x080,
		0x100,
		0x180,

		0x200,
		0x280,
		0x300,
		0x380,

		0x400,
		0x480,
		0x500,
		0x580,

		0x600,
		0x680,
		0x700,
		0x780
	}
};


#define MAP_LIMITS_MAP_AXIS_SIZE 26

DECLARE_AXIS_WITH_DESC(flash_map_avg_axis,
	MAP_LIMITS_MAP_AXIS_SIZE,
	"Manifold Pressure",
	"MAPModPressure") = {
	.dst = MAP_AXIS_DST_SDA,
	.src = MAP_AXIS_SRC_SDA,
	.size = MAP_LIMITS_MAP_AXIS_SIZE,
	.data = {
		0,
		1638,
		3277,
		4915,
		6554,

		8192,
		9830,
		11469,
		13107,
		14746,

		16384,
		18022,
		19661,
		21299,
		22938,

		24576,
		26214,
		27853,
		29491,
		31130,

		32768,
		34406,
		36045,
		37683,
		39322,

		40960
	}
};

extern void adc_run(uint16_t p_channel, uint16_t *p_out_full, uint16_t *p_out_byte);

#define ADC_CHANNEL_FUEL_TANK_TEMPERATURE 44
#define ADC_CHANNEL_FUEL_TANK_PRESSURE 56

extern void adc_convert_maf();

void update_map_main_corrections()
{
	adc_run(ADC_CHANNEL_FUEL_TANK_TEMPERATURE, &adc_full_mat, &adc_byte_mat);
	
	temp_axis_src = adc_full_mat;
	calc_axis(&flash_fuel_temperature_sensor_axis);

	mat = ps_divu16(mapu16(&flash_fuel_temperature_sensor_characteristic_2dmap16), 10);

	temp_axis_src = mat;
	calc_axis(&flash_map_compensation_mat_axis);
	map_load_mat_compensation = map8u16(&flash_map_load_mat_compensation_2dmap8);

	temp_axis_src = baro_pressure;
	calc_axis(&flash_map_compensation_baro_axis);
	map_load_baro_compensation = map8u16(&flash_map_load_baro_compensation_2dmap8);

	calc_axis(&flash_map_engine_rpm_axis);
}

void adc_convert_map()
{
	adc_run(ADC_CHANNEL_FUEL_TANK_PRESSURE, &adc_full_map, &adc_byte_map);
	uint16_t l_map_samples = map_samples + 1;
	if (l_map_samples) {
		uint32_t l_map_sum = map_samples_sum + adc_full_map;
		if (l_map_sum >= map_samples_sum) {
			map_samples_sum = l_map_sum;
			map_samples = l_map_samples;
		}
	}
}

void new_adc_convert_maf()
{
	adc_convert_map();
	adc_convert_maf();
}

static uint32_t update_load_source_value_from_map_samples()
{
	uint_fast16_t l_samples = s_add16(map_samples, map_samples_prev);
	if (l_samples) {
		map_avg_voltage = s_mul32_16_divu16(s_add32(map_samples_sum, map_samples_sum_prev), 64, l_samples);
		map_avg16 = s_scale_base256(s_sub16(map_avg_voltage, flash_map_voltage_zero_offset), flash_map_scaling_kpa_per_volt);
	}
	map_samples_prev = map_samples;
	map_samples = 0;
	map_samples_sum_prev = map_samples_sum;
	map_samples_sum = 0;

	calc_axis(&flash_map_avg_axis);
	map_load_base = mapu16(&flash_map_limits_load_3dmap16);
	
	uint32_t l_result = map_load_base;
	l_result = ps_scale_base128(l_result, map_load_baro_compensation);
	l_result = ps_scale_base128(l_result, map_load_mat_compensation);

	return l_result * 65536;
}
