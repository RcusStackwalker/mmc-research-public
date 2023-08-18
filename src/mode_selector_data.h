#ifndef MODE_SELECTOR_DATA_H
#define MODE_SELECTOR_DATA_H

#include <stdint.h>

//extern const uint8_t flash_alt_disable_o2_feedback[];
extern const uint8_t flash_alt_mode_ac_switch;
extern const uint8_t flash_reset_alt_mode_on_ignition_cycle;

extern const uint8_t flash_mode_change_patterns[4][16];
extern const uint16_t flash_alt_mode_change_cel_flash_time;
extern const const uint16_t flash_alt_mode_change_cel_flash_time_slice;
extern const uint16_t flash_m_depressed_threshold;
extern const uint16_t flash_tps_alt_threshold;

extern const uint8_t flash_adc_ac_pressure_master;
extern const uint16_t flash_init_mode_switch_delay;
extern const uint16_t flash_mode_selector_adc_ac_pressure_thresholds[2];


#endif /*MODE_SELECTOR_DATA_H*/
