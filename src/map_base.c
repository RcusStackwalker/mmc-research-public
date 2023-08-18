#include <adc.h>
#include <fmath.h>

#define ADC_CHANNEL_MAP (ADC1_CH_FLAG | 4)
#define ADC_CHANNEL_MAT (ADC1_CH_FLAG | 5)

uint16_t adc_byte_mat;
uint16_t adc_full_mat;
uint16_t mat;

uint16_t adc_byte_map;

uint32_t map_sum;
uint16_t map_samples;
uint16_t map_current;
uint16_t map_prev;
uint16_t map_avg;

extern const uint16_t flash_map_kpa_per_volt;
extern const uint16_t flash_map_zero_offset;

extern const void *const flash_mat_sensor_axis;
extern const void *const flash_mat_sensor_2dmap8;


void update_mat()
{
	adc_run(ADC_CHANNEL_MAT, &adc_byte_mat, &adc_full_mat);
	temp_axis_src = adc_byte_mat;
	calc_axis(&flash_mat_sensor_axis);
	mat = map8u16(&flash_mat_sensor_2dmap8);
}

static void adc_convert_map()
{
	uint16_t temp;
	adc_run(ADC_CHANNEL_MAP, &adc_byte_map, &temp);
	if (map_samples != 0xffff) {
		pushi();
		map_sum = s_add32(map_sum, ps_scale_base128(s_sub16(temp, flash_map_zero_offset), flash_map_kpa_per_volt));
		map_samples = s_add16(map_samples, 1);
		popi();
	}
}

void cycle_process_map()
{
	map_prev = map_current;
	map_current = ps16_divu32_16(map_sum, map_samples);
	map_samples = 0;
	map_sum = 0;
	map_avg = (map_prev + map_current + 1) / 2;
}

void hijack_calc_iat()
{
	calc_iat();
	update_mat();
}


void hijack_800hz_adc_call()
{
	adc_convert_maf();
	adc_convert_map();
}

uint32_t hijack_maf_charge_aprx_bound(uint32_t p0_val, uint32_t p1_min, uint32_t p2_max)
{
	uint32_t ret = mid32(p0_val, p1_min, p2_max);
	cycle_process_map();
	return ret;
}
