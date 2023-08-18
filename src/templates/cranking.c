#include <maps_desc.h>

DECLARE_AXIS_DESC_EX(flash_spark_cooldown_axis, "Spark Cooldown Timer", "Time800Hz960Sub");

DECLARE_2DMAP8_DESC(flash_cranking_ipw_vs_spark_cooldown_2dmap8,
	"Cranking",
	"IPW Correction vs Spark-to-Spark time",
	"Percent128",
	"DXflash_spark_cooldown_axis");

DECLARE_AXIS_DESC_EX(flash_cranking_coolant_axis, "Coolant Temperature", "Temp");

DECLARE_2DMAP8_DESC(flash_cranking_base_ipw_vs_coolant_2dmap8,
	"Cranking",
	"Base IPW",
	"CrankingIPW",
	"DXflash_cranking_coolant_axis");


DECLARE_AXIS_DESC_EX(flash_start_related_coolant_axis, "Coolant Temperature", "Temp");

DECLARE_2DMAP8_DESC(flash_cranking_decay1_init_vs_coolant_2dmap8,
	"Cranking",
	"Aftercranking Enrichment - Active State",
	"Percent64U8",
	"DXflash_start_related_coolant_axis");

DECLARE_2DMAP8_DESC(flash_cranking_decay2_init_vs_coolant_2dmap8,
	"Cranking",
	"Aftercranking Enrichment - Steady State",
	"Percent64U8",
	"DXflash_start_related_coolant_axis");

DECLARE_AXIS_DESC_EX(flash_warmup_fuel_load_axis, "Load", "Load");

DECLARE_3DMAP8_DESC(flash_warmup_fuel_active_state_3dmap8,
	"Cranking",
	"Warmup Enrichment - Active State",
	"Percent128",
	"DXflash_warmup_fuel_load_axis",
	"DXflash_start_related_coolant_axis");

DECLARE_3DMAP8_DESC(flash_warmup_fuel_steady_state_3dmap8,
	"Cranking",
	"Warmup Enrichment - Steady State",
	"Percent128",
	"DXflash_warmup_fuel_load_axis",
	"DXflash_start_related_coolant_axis");
