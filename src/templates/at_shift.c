#include <maps_desc.h>

DECLARE_AXIS_DESC_EX(flash_shift_oss_tps_axis, "TPS", "ATTPS");

DECLARE_2DMAP8_DESC(flash_1st_to_2nd_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Upshift Speed - 1st to 2nd",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_2nd_to_3rd_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Upshift Speed - 2nd to 3rd",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_3rd_to_4th_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Upshift Speed - 3rd to 4th",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_4th_to_5th_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Upshift Speed - 4th to 5th",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_2nd_to_1st_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Downshift Speed - 2nd to 1st",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_3rd_to_2nd_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Downshift Speed - 3rd to 2nd",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_4th_to_3rd_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Downshift Speed - 4th to 3rd",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");

DECLARE_2DMAP8_DESC(flash_5th_to_4th_shift_normal_tarmac_oss_vs_tps_2dmap8,
	"AT",
	"Downshift Speed - 5th to 4th",
	"SpeedU8x50",
	"DXflash_shift_oss_tps_axis");
