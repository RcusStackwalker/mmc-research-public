#include <stdint.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>

extern uint16_t current_sst_gear;

#define SST_GEAR_AXIS_SIZE 7

DECLARE_AXIS_WITH_DESC(flash_spark_correction_sst_gear_axis,
	SST_GEAR_AXIS_SIZE,
	"Gear",
	"uint16") = {
	TEMP_AXIS_SRC_XDST,
	.size = SST_GEAR_AXIS_SIZE,
	.data = { 0, 1, 2, 3, 4, 5, 6 }
};

DECLARE_2DMAP8_WITH_DESC(flash_sst_spark_vs_gear_correction_2dmap8,
	SST_GEAR_AXIS_SIZE,
	"SST Rcus Moded Ignition",
	"Ignition vs Gear Correction",
	"IgnitionCompensation",
	"DDflash_spark_correction_sst_gear_axis") = {
	TEMP_2DMAP_SRC,
	.data = { 127, 127, 127, 128, 128, 128, 129 }
};

uint16_t sst_spark_vs_gear_correction(uint16_t p0)
{
	temp_axis_src = current_sst_gear;
	calc_axis(&flash_spark_correction_sst_gear_axis);
	return s_sub16(s_add16(p0, map8u16(&flash_sst_spark_vs_gear_correction_2dmap8)), 128);
}
