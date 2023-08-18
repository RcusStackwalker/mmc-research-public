#ifndef SHIFT_LIGHT_H
#define SHIFT_LIGHT_H

#define SHIFT_LIGHT_MAX_SLICE_COUNT 16
#define SHIFT_LIGHT_STAGE_COUNT 3

extern uint8_t flash_shift_light_flash_patterns[SHIFT_LIGHT_STAGE_COUNT][SHIFT_LIGHT_MAX_SLICE_COUNT];
extern const uint16_t flash_shift_light_rpm_thresholds[SHIFT_LIGHT_STAGE_COUNT];
extern const uint8_t flash_shift_light_control_mode;

#endif /*SHIFT_LIGHT_H*/
