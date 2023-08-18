#ifndef COLT_MT_CVT_DASH_CONTROL_DATA_H
#define COLT_MT_CVT_DASH_CONTROL_DATA_H

#include <stdint.h>

#define DASH_FLASH_MAX_SLICE_COUNT 16
#define SHIFT_LIGHT_STAGE_COUNT 6

extern const uint8_t flash_shift_light_flash_patterns[SHIFT_LIGHT_STAGE_COUNT][DASH_FLASH_MAX_SLICE_COUNT];
extern const uint16_t flash_shift_light_rpm_thresholds[SHIFT_LIGHT_STAGE_COUNT];
extern const uint8_t flash_asc_flash_pattern[DASH_FLASH_MAX_SLICE_COUNT];

#endif
