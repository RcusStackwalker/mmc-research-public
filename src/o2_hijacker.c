#include <fmath.h>
#include <adc.h>

#define ADC_CHANNEL_O2_FRONT 62
#define ADC_CHANNEL_O2_REAR 78

extern uint16_t adc_byte_o2_front;
extern uint16_t adc_byte_o2_rear;
extern uint16_t adc_byte_o2_rear_replacement;
extern uint16_t adc_full_o2_rear_replacement;

void new_o2_adc_runs()
{
	uint16_t tmp;
	adc_run(ADC_CHANNEL_O2_FRONT, &adc_byte_o2_front, &tmp);
	adc_byte_o2_rear = ps_divu16(adc_byte_o2_front, 2);
	adc_run(ADC_CHANNEL_O2_REAR, &adc_byte_o2_rear_replacement, &adc_full_o2_rear_replacement);
}

