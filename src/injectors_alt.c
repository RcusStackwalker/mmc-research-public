#include <fmath.h>
#include <maps_desc.h>
#include <maps_decl.h>

extern uint16_t injector_scaling_to_volume_correction;
extern const uint16_t flash_cylinder_volume;

const uint16_t flash_new_injector_scaling_u16a[8] = {
	109,
	109,
	109,
	109,

	109,
	109,
	109,
	109,
};

DECLARE_ARRAY_DESC(flash_new_injector_scaling_u16a,
	"Injectors",
	"Injector Scaling - Main/Alt",
	"InjectorScaling1",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"2\">"
	"<data>Main</data>"
	"<data>Alt</data>"
	"</table>");

#define INJECTOR_POWER_AXIS_SIZE 7

DECLARE_AXIS_DESC_EX(flash_injector_latency_power_axis, "Battery Voltage", "BatteryVoltage");

DECLARE_2DMAP8_WITH_DESC(flash_injector_latency_vs_power_2dmap8_alt,
	INJECTOR_POWER_AXIS_SIZE,
	"Injectors",
	"Injector Latency v Battery Voltage - Alt",
	"InjectorLatency",
	"DXflash_injector_latency_power_axis") =
{
	TEMP_2DMAP_SRC,
	.data = {}
};

extern const void *const flash_injector_latency_vs_power_2dmap8;

const void *const flash_injector_latency_vs_power_2dmultimap8[8] = {
	&flash_injector_latency_vs_power_2dmap8,
	&flash_injector_latency_vs_power_2dmap8_alt,
	&flash_injector_latency_vs_power_2dmap8,
	&flash_injector_latency_vs_power_2dmap8,
	&flash_injector_latency_vs_power_2dmap8,
	&flash_injector_latency_vs_power_2dmap8,
	&flash_injector_latency_vs_power_2dmap8,
	&flash_injector_latency_vs_power_2dmap8,
};


void new_update_injector_scaling_to_volume_correction()
{
	injector_scaling_to_volume_correction = (multiu16(flash_new_injector_scaling_u16a) * flash_cylinder_volume + 1) / 2;
}
