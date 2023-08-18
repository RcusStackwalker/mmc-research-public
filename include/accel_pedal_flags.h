#ifndef ACCEL_PEDAL_FLAGS_H
#define ACCEL_PEDAL_FLAGS_H

#define ACCEL_PEDAL_MAIN_SHORTED_POWER_EX	0x0001
//unknown reset condition
#define ACCEL_PEDAL_MAIN_SHORTED_POWER_LONG	0x0002
//unknown reset condition
#define ACCEL_PEDAL_MAIN_SHORTED_GROUND_LONG	0x0004
//unknown reset condition
#define ACCEL_PEDAL_SUB_SHORTED_POWER_LONG	0x0008
//unknown reset condition
#define ACCEL_PEDAL_SUB_SHORTED_GROUND_LONG	0x0010
/*short mismatch?*/
#define ACCEL_PEDAL_UNKNOWN20		0x0020
#define ACCEL_PEDAL_NEUTRAL_SWITCH_FAULT_LONG	0x0040
#define ACCEL_PEDAL_NEUTRAL_SWITCH_FAULT2	0x0080
#define ACCEL_PEDAL_MISMATCH		0x0100
#define ACCEL_PEDAL_MAIN_SHORTED_POWER	0x0200
#define ACCEL_PEDAL_MAIN_SHORTED_GROUND	0x0400
#define ACCEL_PEDAL_SUB_SHORTED_POWER	0x0800
#define ACCEL_PEDAL_SUB_SHORTED_GROUND	0x1000

#define ACCEL_PEDAL_NEUTRAL_SWITCH_FAULT	0x4000

#endif /*ACCEL_PEDAL_FLAGS_H*/
