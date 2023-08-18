#include <stdint.h>
#include <maps_desc.h>
#include <maps_decl.h>
#include <fmath.h>

const uint16_t flash_maf_fault_revolution_period_limit = 0x3da;
DECLARE_VALUE_DESC(flash_maf_fault_revolution_period_limit,
	"PatchedLimits",
	"MAF Fault RPM Limit",
	"RPMLimit");

const uint16_t flash_revolution_period_limit = 0x3da / 2;
DECLARE_VALUE_DESC(flash_revolution_period_limit,
	"PatchedLimits",
	"General RPM Limit",
	"RPMLimit");

const uint16_t flash_launch_control_revolution_limit = 0x3da;
DECLARE_VALUE_DESC(flash_launch_control_revolution_limit,
	"PatchedLimits",
	"Launch RPM Limit",
	"RPMLimit");

const uint16_t flash_init_overrev_cycle_decay[2] = {8,4};
DECLARE_ARRAY_DESC(flash_init_overrev_cycle_decay,
	"PatchedLimits",
	"Overrev cycle decay",
	"uint16",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"2\">\n"
	"<data>Launch</data>\n"
	"<data>NLTS</data>\n"
	"</table>");

const uint16_t flash_overrev_kill_spark_cycles[2] = {8,4};
DECLARE_ARRAY_DESC(flash_overrev_kill_spark_cycles,
	"PatchedLimits",
	"Overrev kill spark cycles",
	"uint16",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"2\">\n"
	"<data>Launch</data>\n"
	"<data>NLTS</data>\n"
	"</table>");

const uint8_t flash_simple_standing_revolution_limit_enabled = 1;
DECLARE_VALUE_DESC(flash_simple_standing_revolution_limit_enabled,
	"PatchedLimits",
	"Launch Limit Enabled",
	"uint8");

const uint16_t flash_revolution_limit_spark_decay_cycles_per_tick[2] = {2,2};
DECLARE_ARRAY_DESC(flash_revolution_limit_spark_decay_cycles_per_tick,
	"PatchedLimits",
	"Spark Limit Decay Cycles per Tick",
	"uint16",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"2\">\n"
	"<data>Launch</data>\n"
	"<data>NLTS</data>\n"
	"</table>");


#define REVOLUTION_LIMIT_RPM_AXIS_SIZE 12

DECLARE_AXIS_WITH_DESC(flash_revolution_limit_rpm_axis,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	"RPM",
	"RPM") =
{
	TEMP_AXIS_SRC_XDST,
	.size = REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	.data = {
		0x100,
		0x200,
		0x280,
		0x300,
		0x380,

		0x400,
		0x480,
		0x500,
		0x580,
		0x600,

		0x680,
		0x700,
	}
};

#define REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE 21

#define LOAD16DATA(x) (x*32/10)

DECLARE_AXIS_WITH_DESC(flash_revolution_limit_load_axis, REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE, "Load", "Load") = {
	TEMP_AXIS_SRC_YDST,
	.size = REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE,
	.data = {
		LOAD16DATA(10),
		LOAD16DATA(20),
		LOAD16DATA(30),
		LOAD16DATA(40),
		LOAD16DATA(50),
		LOAD16DATA(60),
		LOAD16DATA(70),
		LOAD16DATA(80),
		LOAD16DATA(90),
		LOAD16DATA(100),
		LOAD16DATA(120),
		LOAD16DATA(140),
		LOAD16DATA(160),
		LOAD16DATA(180),
		LOAD16DATA(200),
		LOAD16DATA(220),
		LOAD16DATA(240),
		LOAD16DATA(260),
		LOAD16DATA(280),
		LOAD16DATA(300),
		LOAD16DATA(320),
	}
};

DECLARE_3DMAP8_WITH_DESC(flash_post_fuel_cut_enrichment_launch_3dmap8,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE,
	"PatchedLimits",
	"Post fuel cut enrichment - Launch",
	"Percent (128)",
	"DDflash_revolution_limit_load_axis",
	"DDflash_revolution_limit_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	.data = { [0 ... (REVOLUTION_LIMIT_RPM_AXIS_SIZE * REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE - 1)] = 26 }
};

DECLARE_3DMAP8_WITH_DESC(flash_post_fuel_cut_enrichment_nlts_3dmap8,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE,
	"PatchedLimits",
	"Post fuel cut enrichment - NLTS",
	"Percent (128)",
	"DDflash_revolution_limit_load_axis",
	"DDflash_revolution_limit_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	.data = { [0 ... (REVOLUTION_LIMIT_RPM_AXIS_SIZE * REVOLUTION_LIMIT_MAP_LOAD_AXIS_SIZE - 1)] = 30 }
};

#define INT_TO_SPARK_CRANK(x) (61 - (x)) * 256/90

DECLARE_2DMAP8_WITH_DESC(flash_revolution_limit_spark_limit_launch_2dmap8,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	"PatchedLimits",
	"Post fuel cut initial spark limit - Launch",
	"SparkCrankU8",
	"DDflash_revolution_limit_rpm_axis") =
{
	TEMP_2DMAP_SRC,
	.data = {
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),

		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),

		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_revolution_limit_spark_limit_nlts_2dmap8,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	"PatchedLimits",
	"Post fuel cut initial spark limit - NLTS",
	"SparkCrankU8",
	"DDflash_revolution_limit_rpm_axis") =
{
	TEMP_2DMAP_SRC,
	.data = {
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),

		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),

		INT_TO_SPARK_CRANK(-10),
		INT_TO_SPARK_CRANK(-10),
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_revolution_limit_spark_regeneration_launch_2dmap8,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	"PatchedLimits",
	"Post fuel cut spark limit decay per tick - Launch",
	"Deg90Per256U8",
	"DDflash_revolution_limit_rpm_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		1,
		1,
		1,
		1,
		1,

		1,
		1,
		1,
		1,
		1,

		1,
		1,
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_revolution_limit_spark_regeneration_nlts_2dmap8,
	REVOLUTION_LIMIT_RPM_AXIS_SIZE,
	"PatchedLimits",
	"Post fuel cut spark limit decay per tick - NLTS",
	"Deg90Per256U8",
	"DDflash_revolution_limit_rpm_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		1,
		1,
		1,
		1,
		1,

		1,
		1,
		1,
		1,
		1,

		1,
		1,
	}
};
