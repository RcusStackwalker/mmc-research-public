#ifndef NLTS2_DATA_H
#define NLTS2_DATA_H

#include <stdint.h>

extern const uint16_t flash_nlts_integral_torque_correction_limits[2];
extern const uint16_t flash_nlts_torque_limits[2];
extern const uint16_t flash_nlts_speed_averaging_rate;
extern const uint16_t flash_nlts_rpm_overshoot;
extern const uint16_t flash_nlts_gear_ratios[7];
extern const uint16_t flash_nlts_app_thresholds[2];
extern const uint16_t flash_init_nlts_active_decay;
extern const uint16_t flash_init_nlts_active_decay_partial_engagement;
extern const uint16_t flash_nlts_delta_holdoff;
extern const uint16_t flash_nlts_rpm_delta_threshold;
extern const uint8_t flash_nlts_integral_divisor_multiu8a[8];
extern const uint8_t flash_nlts_proportional_divisor_multiu8a[8];
extern const uint16_t flash_nlts_gear_ratio_high;
extern const uint16_t flash_nlts_rpm_ratio_high;
extern const uint16_t flash_nlts_rpm_ratio_low;
//extern const uint16_t flash_nlts_fuelcut_holdoff;


#define NLTS_NEUTRAL_TORQUE 16384


extern const uint16_t flash_nlts_gear_down_rpm_max;
extern const uint8_t flash_nlts_gear_max;

extern uint16_t nlts_speed;
extern uint16_t nlts_speed_filtered;
extern uint16_t nlts_flags;
extern uint8_t nlts_target_gear;
extern uint8_t nlts_state;
extern uint16_t decays_x1_nlts_active;
extern uint16_t nlts_target_rpm;
extern uint16_t nlts_rpm_error;
extern uint16_t nlts_torque_limit;
extern uint16_t nlts_integral_torque_correction;

#define NLTS_FLAGS_APPS_HIGH			0x01
#define NLTS_FLAGS_CLUTCH_DEPRESSED		0x02
#define NLTS_FLAGS_GEAR_DOWN_RPM		0x04
#define NLTS_FLAGS_CURRENT_GEAR_CORRECT		0x08
#define NLTS_FLAGS_CLUTCH_PARTIAL_ENGAGEMENT	0x10
#define NLTS_FLAGS_FUEL_CUT			0x20
#define NLTS_FLAGS_GEAR_HIGH			0x40
#define NLTS_FLAGS_SPARK_CUT			0x80
#define NLTS_FLAGS_CUTS				(NLTS_FLAGS_FUEL_CUT | NLTS_FLAGS_SPARK_CUT)
#define NLTS_FLAGS_RPM_HIGH			0x0100

#define NLTS_STATE_OFF 0
#define NLTS_STATE_ON 1
#define NLTS_STATE_UNLIMITED 2


#endif /*NLTS2_DATA_H*/
