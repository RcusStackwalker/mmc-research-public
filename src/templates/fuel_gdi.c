#include <maps_desc.h>

DECLARE_AXIS_DESC_EX(flash_gdi_fuel_rpm_axis, "GDI Fuel RPM Axis", "RPM");
DECLARE_AXIS_DESC_EX(flash_gdi_fuel_load_axis, "GDI Fuel Load Axis", "Load");

DECLARE_3DMAP8_DESC(flash_alt_base_fuel_3dmap8,
	"Fuel",
	"Target AFR - Alt Base",
	"AFR",
	"DXflash_fuel_map_load_axis",
	"DXflash_fuel_map_rpm_axis");

DECLARE_3DMAP8_DESC(flash_gdi_afr_warmed_3dmap8,
	"Fuel",
	"Target AFR - GDI Warmed",
	"AFR",
	"DXflash_gdi_fuel_load_axis",
	"DXflash_gdi_fuel_rpm_axis");


DECLARE_AXIS_DESC_EX(flash_gdi_lean_fuel_rpm_axis, "GDI Lean Fuel RPM Axis", "RPM");
DECLARE_AXIS_DESC_EX(flash_gdi_lean_fuel_load_axis, "GDI Lean Fuel Load Axis", "Load");

DECLARE_3DMAP8_DESC(flash_gdi_lean_afr_3dmap8,
	"Fuel",
	"Target AFR - GDI Lean",
	"AFR",
	"DXflash_gdi_lean_fuel_load_axis",
	"DXflash_gdi_lean_fuel_rpm_axis");
