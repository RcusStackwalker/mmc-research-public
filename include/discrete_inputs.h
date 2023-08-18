#ifndef MY_DISCRETE_INPUTS_H
#define MY_DISCRETE_INPUTS_H

#define APPS_IS_NEUTRAL	(readu16(alt_inputs1_processed) & 0x80)

#define CLUTCH_PEDAL_DEPRESSED (readu16(alt_inputs3_processed) & 0x01)

#define AC_SWITCH_ON	(readu16(alt_inputs1_processed) & 0x10)

#define AC_HOLDOFF_ON	(readu16(alt_inputs2_processed) & 0x0100)

#endif /*MY_DISCRETE_INPUTS_H*/
