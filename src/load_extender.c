#include <fmath.h>
#include <maps_decl.h>

#define NEW_FUEL_MAP_LOAD_AXIS_SIZE 21

#define LOAD16DATA(x) (x*32/10)

DECLARE_AXIS_DESC_EX(flash_fuel_map_rpm_axis, "RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_main_spark_maps_rpm_axis, "RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_mivec_target_rpm_axis, "RPM", "RPM");

DECLARE_AXIS_WITH_DESC(flash_new_fuel_map_load_axis, NEW_FUEL_MAP_LOAD_AXIS_SIZE, "New Fuel Load Axis", "Load") = {
	TEMP_AXIS_SRC_YDST,
	.size = NEW_FUEL_MAP_LOAD_AXIS_SIZE,
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

#define NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE 22

DECLARE_AXIS_WITH_DESC(flash_new_main_spark_maps_load_axis, NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE, "New Spark Load Axis", "Load") = {
	TEMP_AXIS_SRC_YDST,
	.size = NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	.data = {
		LOAD16DATA(0),
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

#define NEW_MIVEC_MAP_LOAD_AXIS_SIZE 21

DECLARE_AXIS_WITH_DESC(flash_new_mivec_map_load_axis, NEW_MIVEC_MAP_LOAD_AXIS_SIZE, "New Mivec Load Axis", "Load") = {
	TEMP_AXIS_DST_Y,
	.src = MAP_ENGINE_LOAD_POINTER,
	.size = NEW_MIVEC_MAP_LOAD_AXIS_SIZE,
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

#define FUEL_RPM_AXIS_SIZE 14

DECLARE_3DMAP8_WITH_DESC(flash_new_low_octane_fuel_3dmap8,
	FUEL_RPM_AXIS_SIZE,
	NEW_FUEL_MAP_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Target AFR - Low Octane",
	"AFR",
	"DDflash_new_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.xsize = FUEL_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_high_octane_fuel_3dmap8,
	FUEL_RPM_AXIS_SIZE,
	NEW_FUEL_MAP_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Target AFR - High Octane",
	"AFR",
	"DDflash_new_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.xsize = FUEL_RPM_AXIS_SIZE,
	.data = {}
};

#define SPARK_RPM_AXIS_SIZE 18

DECLARE_3DMAP8_WITH_DESC(flash_new_spark_angle_low_octane_mivec_advance_min_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Spark Angle - Low Octane - Intake MIVEC Advance Min",
	"Timing",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_spark_angle_low_octane_mivec_advance_max_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Spark Angle - Low Octane - Intake MIVEC Advance Max",
	"Timing",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_spark_angle_low_octane_mivec_advance_target_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Spark Angle - Low Octane - Intake MIVEC Advance at Target",
	"Timing",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_spark_angle_high_octane_mivec_advance_min_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Spark Angle - High Octane - Intake MIVEC Advance Min",
	"Timing",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_spark_angle_high_octane_mivec_advance_max_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Spark Angle - High Octane - Intake MIVEC Advance Max",
	"Timing",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_spark_angle_high_octane_mivec_advance_target_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Spark Angle - High Octane - Intake MIVEC Advance at Target",
	"Timing",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.offset = 20,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_warmup_retard_mivec_advance_min_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Warmup Spark Retard - Intake MIVEC Advance Min",
	"IgnitionCompensation",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_warmup_retard_mivec_advance_max_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Warmup Spark Retard - Intake MIVEC Advance Max",
	"IgnitionCompensation",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

DECLARE_3DMAP8_WITH_DESC(flash_new_warmup_retard_mivec_advance_target_3dmap8,
	SPARK_RPM_AXIS_SIZE,
	NEW_MAIN_SPARK_MAPS_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Warmup Spark Retard - Intake MIVEC Advance at Target",
	"IgnitionCompensation",
	"DDflash_new_main_spark_maps_load_axis",
	"DXflash_main_spark_maps_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.xsize = SPARK_RPM_AXIS_SIZE,
	.data = {}
};

#define MIVEC_RPM_AXIS_SIZE 16

DECLARE_3DMAP8_WITH_DESC(flash_new_mivec_target_3dmap8,
	MIVEC_RPM_AXIS_SIZE,
	NEW_MIVEC_MAP_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"MIVEC Intake Target Angle",
	"ValveTimingIntake",
	"DDflash_new_mivec_map_load_axis",
	"DXflash_mivec_target_rpm_axis") = 
{
	TEMP_3DMAP_SRC,
	.xsize = MIVEC_RPM_AXIS_SIZE,
	.data = {}
};

#ifdef CVT_BUILD
#include "src/load_extender_cvt.c"
#elif TOMO_MT_BUILD
#include "src/load_extender_tomo_mt.c"
#endif
