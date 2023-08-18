#include "precise_gear_detector_data.h"

#include <maps_desc.h>

#define GEAR_THRESHOLD_DEF(target, inth, outth) { .low_in = target - inth, .low_out = target - outth, .high_in = target + inth, .high_out = target + outth, } 

/**
 * gear ratio:
	1000 rpm = 256
	10 kph = (2260 / 7.9875 / 10) = 28 discrete period
	final drive 4.53
	1st gear 2.785 - 1040 rpm at 10kph
	1,883.26259781
 */

/*
	can_vehicle_speed is 0.25kph per discrete
	engine_rpm is 1k per 256 discrete
	gear_ratio is 
*/

const struct gear_threshold flash_gear_thresholds[6] = {
	GEAR_THRESHOLD_DEF(1991, 50, 100),
	GEAR_THRESHOLD_DEF(1330, 50, 100),
	GEAR_THRESHOLD_DEF(981, 50, 100),
	GEAR_THRESHOLD_DEF(753, 40, 80),
	GEAR_THRESHOLD_DEF(594, 30, 60),
	GEAR_THRESHOLD_DEF(474, 30, 50),
};

DECLARE_ARRAY_DESC(flash_gear_thresholds,
	"Gear Detector",
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
DECLARE_VALUE_DESC(flash_init_gear_unstable, "Gear Detector", "Gear Debounce Time", "Time");

