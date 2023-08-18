#include "gear_detector_data.h"

#include <maps_desc.h>

#define GEAR_THRESHOLD_DEF(target, inth, outth) { .low_in = target - inth, .low_out = target - outth, .high_in = target + inth, .high_out = target + outth, } 

#if MACHINE_Z27AGMT
/**
 * gear ratio:
	1000 rpm = 256
	10 kph = (2260 / 7.9875 / 10) = 28 discrete period
	final drive 4.53
	1st gear 2.785 - 1040 rpm at 10kph
	1,883.26259781
 */

/**
 * gear ratio:
	can_vehicle_speed = 142 discretes per 8kph
 */

const struct gear_threshold flash_gear_thresholds[6] = {
	GEAR_THRESHOLD_DEF(9570, 1000, 1500),
	GEAR_THRESHOLD_DEF(17699, 1500, 2000),
	GEAR_THRESHOLD_DEF(23611, 2000, 2500),
	GEAR_THRESHOLD_DEF(30781, 2500, 3000),
	GEAR_THRESHOLD_DEF(39008, 2500, 3000),
	GEAR_THRESHOLD_DEF(48858, 2500, 3000),
};
#elif MACHINE_EVOX_MT
/**
 * gear ratio:
	1000 rpm = 256
 */
const struct gear_threshold flash_gear_thresholds[6] = {
	GEAR_THRESHOLD_DEF(9592, 1000, 2000),
	GEAR_THRESHOLD_DEF(14054, 1000, 2000),
	GEAR_THRESHOLD_DEF(18979, 1000, 2000),
	GEAR_THRESHOLD_DEF(25005, 1000, 2000),
	GEAR_THRESHOLD_DEF(36013, 2000, 4000),
	GEAR_THRESHOLD_DEF(36013, 2000, 4000),
};
#elif MACHINE_EVOX_MT_GP43
/**
 * gear ratio:
	1000 rpm = 256
 */
const struct gear_threshold flash_gear_thresholds[6] = {
	GEAR_THRESHOLD_DEF(10262, 1000, 2000),
	GEAR_THRESHOLD_DEF(15035, 1000, 2000),
	GEAR_THRESHOLD_DEF(20304, 1000, 2000),
	GEAR_THRESHOLD_DEF(26750, 1000, 2000),
	GEAR_THRESHOLD_DEF(38526, 2000, 4000),
	GEAR_THRESHOLD_DEF(38526, 2000, 4000),
};
#endif

DECLARE_ARRAY_DESC(flash_gear_thresholds,
	"NLTS",
	"Gear Detector Ratio Thresholds",
	"uint16",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"24\">"
	"<data>1 Low Out</data>"
	"<data>1 Low In</data>"
	"<data>1 High In</data>"
	"<data>1 High Out</data>"
	"<data>2 Low Out</data>"
	"<data>2 Low In</data>"
	"<data>2 High In</data>"
	"<data>2 High Out</data>"
	"<data>3 Low Out</data>"
	"<data>3 Low In</data>"
	"<data>3 High In</data>"
	"<data>3 High Out</data>"
	"<data>4 Low Out</data>"
	"<data>4 Low In</data>"
	"<data>4 High In</data>"
	"<data>4 High Out</data>"
	"<data>5 Low Out</data>"
	"<data>5 Low In</data>"
	"<data>5 High In</data>"
	"<data>5 High Out</data>"
	"<data>6 Low Out</data>"
	"<data>6 Low In</data>"
	"<data>6 High In</data>"
	"<data>6 High Out</data>"
	"</table>");


const uint16_t flash_init_gear_unstable = 2;

