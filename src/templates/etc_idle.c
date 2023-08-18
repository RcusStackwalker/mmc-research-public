#include "maps_desc.h"

DECLARE_AXIS_DESC_EX(flash_isv_to_target_throttle_position_axis, "Idle Air Control Position", "uint16");
DECLARE_2DMAP16_DESC(flash_isv_to_target_throttle_position_2dmap16,
	"Throttle",
	"IAC to Throttle Position"
	"uint16",
	"DXflash_isv_to_target_throttle_position_axis");
