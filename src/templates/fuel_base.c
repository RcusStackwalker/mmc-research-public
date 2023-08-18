#include <maps_desc.h>

DECLARE_AXIS_DESC_EX(flash_fuel_map_rpm_axis, "Fuel RPM Axis", "RPM");
DECLARE_AXIS_DESC_EX(flash_fuel_map_load_axis, "Fuel Load Axis", "Load");

DECLARE_3DMAP8_DESC(flash_low_octane_fuel_3dmap8,
	"Fuel",
	"Target AFR - Low Octane",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis");

DECLARE_3DMAP8_DESC(flash_high_octane_fuel_3dmap8,
	"Fuel",
	"Target AFR - High Octane",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis");

DECLARE_AXIS_DESC_EX(flash_accelerator_lean_limit_axis, "Accelerator", "APPS");
DECLARE_2DMAP8_DESC(flash_accelerator_lean_limit_2dmap8,
	"Fuel",
	"AFR Lean Limit - Accelerator Pedal Position",
	"AFR",
	"DXflash_accelerator_lean_limit_axis");

DECLARE_AXIS_DESC_EX(flash_air_charge_efficiency_rpm_axis, "RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_air_charge_efficiency_load_axis, "Load", "Load");
DECLARE_3DMAP8_DESC(flash_air_charge_efficiency_vs_rpm_x_load_3dmap8,
	"Fuel",
	"Fueling correction vs RPM x Load",
	"Percent128",
	"DXflash_air_charge_efficiency_load_axis",
	"DXflash_air_charge_efficiency_rpm_axis");
