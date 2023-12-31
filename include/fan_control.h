#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#define FAN_CONTROL_FLAGS_FAN_LOW_ON	0x0001
#define FAN_CONTROL_FLAGS_FAN_HIGH_ON	0x0002
#define FAN_CONTROL_FLAGS_FAN_CHANGED	0x0004
#define FAN_CONTROL_FLAGS_COOLANT_MED	0x0008
#define FAN_CONTROL_FLAGS_COOLANT_LOW	0x0010
#define FAN_CONTROL_FLAGS_COOLANT_HIGH	0x0020
#define FAN_CONTROL_FLAGS_SPEED_MED	0x0040
#define FAN_CONTROL_FLAGS_SPEED_HIGH	0x0080
#define FAN_CONTROL_FLAGS_AC_OVERHEAT	0x0100

#define FAN_CONTROL_FLAGS_OVER_TRANSIENT_DISABLE_TEMP	0x0400

#define FAN_CONTROL_FLAGS_TPS_FOR_TRANSIENT_DISABLE	0x1000
#define FAN_CONTROL_FLAGS_NOT_ENOUGH_SPEED			0x2000
#define FAN_CONTROL_FLAGS_VERY_HIGH_RPM				0x4000
#define FAN_CONTROL_FLAGS_COOLANT_JUST_BELOW_THERMOSTATE	0x8000

#endif /*FAN_CONTROL_H*/
