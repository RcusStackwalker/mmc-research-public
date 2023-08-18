#include "fmath.h"

DECLARE_AXIS_DESC_EX(flash_maf_compensations_rpm_axis, "RPM", "RPM");
DECLARE_2DMAP16_DESC(flash_maf_charge_max_base_vs_rpm_2dmap16,
	"uAFS",
	"MAF Load Base Max",
	"uint16",
	"DXflash_maf_compensations_rpm_axis");

DECLARE_AXIS_DESC_EX(flash_maf_voltage_axis, "ADC Voltage", "ADCVoltage");
DECLARE_2DMAP16_DESC(flash_maf_scaling_2dmap16,
	"uAFS",
	"MAF Scaling",
	"uAFS_Scaling",
	"DXflash_maf_voltage_axis");
