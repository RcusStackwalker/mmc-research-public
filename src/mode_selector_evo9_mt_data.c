#include "mode_selector_data.h"
#include <mode_selector.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>

#define FUEL_RPM_AXIS_SIZE 15
/*this can actually differ, gt-a has only 18*/
#define FUEL_LOAD_AXIS_SIZE 20

DECLARE_AXIS_DESC_EX(flash_fuel_map_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_fuel_map_load_axis, "Load", "Load");

DECLARE_3DMAP8_WITH_DESC(flash_alt_fuel_low_octane_3dmap8,
	FUEL_RPM_AXIS_SIZE,
	FUEL_LOAD_AXIS_SIZE,
	"Alt Maps",
	"AFR - Low Octane",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.xsize = FUEL_RPM_AXIS_SIZE,
	.data = { },
};

DECLARE_3DMAP8_WITH_DESC(flash_alt_fuel_high_octane_3dmap8,
	FUEL_RPM_AXIS_SIZE,
	FUEL_LOAD_AXIS_SIZE,
	"Alt Maps",
	"AFR - High Octane",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.xsize = FUEL_RPM_AXIS_SIZE,
	.data = { },
};

#define SPARK_RPM_AXIS_SIZE 20
#define SPARK_LOAD_AXIS_SIZE 21

DECLARE_AXIS_DESC_EX(flash_main_spark_maps_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_main_spark_maps_load_axis, "Load", "Load");



#define DECLARE_SPARK_MAP(name, username) \
DECLARE_3DMAP8_WITH_DESC(name, \
	SPARK_RPM_AXIS_SIZE, \
	SPARK_LOAD_AXIS_SIZE, \
	"Alt Maps", \
	username, \
	"Timing", \
	"DXflash_main_spark_maps_load_axis", \
	"DXflash_main_spark_maps_rpm_axis") = { \
	TEMP_3DMAP_SRC, \
	.offset = 20, \
	.xsize = SPARK_RPM_AXIS_SIZE, \
	.data = { }, \
}

DECLARE_SPARK_MAP(flash_alt_spark_angle_low_octane_mivec_advance_min_3dmap8, "Ignition - Low Octane - MIVEC Min");
DECLARE_SPARK_MAP(flash_alt_spark_angle_low_octane_mivec_advance_target_3dmap8, "Ignition - Low Octane - MIVEC Target");
DECLARE_SPARK_MAP(flash_alt_spark_angle_low_octane_mivec_advance_max_3dmap8, "Ignition - Low Octane - MIVEC Max");
DECLARE_SPARK_MAP(flash_alt_spark_angle_high_octane_mivec_advance_min_3dmap8, "Ignition - High Octane - MIVEC Min");
DECLARE_SPARK_MAP(flash_alt_spark_angle_high_octane_mivec_advance_target_3dmap8, "Ignition - High Octane - MIVEC Target");
DECLARE_SPARK_MAP(flash_alt_spark_angle_high_octane_mivec_advance_max_3dmap8, "Ignition - High Octane - MIVEC Max");
