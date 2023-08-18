#ifndef MMC_ADC_H
#define MMC_ADC_H

#include <stdint.h>

#define ADC1_CH_FLAG 0x20
#define ADC_P0D5_FLAG 0x10


#define ADC_THROTTLE_POWER_CH	0

#define ADC_OIL_TEMPERATURE_CH (ADC1_CH_FLAG | 6)

void adc_run(unsigned ch, uint16_t *byte_result_out, uint16_t *full_result_ptr);

#endif /*MMC_ADC_H*/
