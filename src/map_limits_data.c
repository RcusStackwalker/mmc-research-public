#include <stdint.h>
#include <maps_decl.h>

#define MAP_SENSOR_AXIS_SIZE 2

DECLARE_AXIS_WITH_DESC(flash_map_sensor_axis,
	MAP_SENSOR_AXIS_SIZE,
	"MAP ADC Voltage",
	"ADCVoltage1024") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAP_SENSOR_AXIS_SIZE,
	.data = {
		0,
		1023
	}
}; 

DECLARE_2DMAP16_WITH_DESC(flash_map_sensor_characteristic_2dmap16,
	MAP_SENSOR_AXIS_SIZE,
	"MAF Limits with MAP",
	"MAP Sensor Characteristic",
	"MAPModPressure",
	"DDflash_map_sensor_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		0,
		40960
	}
};

#define MAP_LIMITS_RPM_AXIS_SIZE 16

DECLARE_AXIS_WITH_DESC(flash_map_limits_engine_rpm_axis,
	MAP_LIMITS_RPM_AXIS_SIZE,
	"RPM",
	"RPM") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAP_LIMITS_RPM_AXIS_SIZE,
	.data = {
		0x000,
		0x080,
		0x100,
		0x180,

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
		0x780
	}
};

#define MAP_LIMITS_MAP_AXIS_SIZE 26

DECLARE_AXIS_WITH_DESC(flash_map_limits_manifold_pressure_axis,
	MAP_LIMITS_MAP_AXIS_SIZE,
	"Manifold Pressure",
	"MAPModPressure") = {
	TEMP_AXIS_SRC_YDST,
	.size = MAP_LIMITS_MAP_AXIS_SIZE,
	.data = {
		0,
		1638,
		3277,
		4915,
		6554,

		8192,
		9830,
		11469,
		13107,
		14746,

		16384,
		18022,
		19661,
		21299,
		22938,

		24576,
		26214,
		27853,
		29491,
		31130,

		32768,
		34406,
		36045,
		37683,
		39322,

		40960
	}
};

DECLARE_3DMAP16_WITH_DESC(flash_map_limits_load_3dmap16,
	MAP_LIMITS_RPM_AXIS_SIZE,
	MAP_LIMITS_MAP_AXIS_SIZE,
	"MAF Limits with MAP",
	"MAP Load Base",
	"MasterLoad",
	"DDflash_map_limits_manifold_pressure_axis",
	"DDflash_map_limits_engine_rpm_axis") = {
	TEMP_3DMAP_SRC,
	.xsize = MAP_LIMITS_RPM_AXIS_SIZE,
	.data = { 32768, 32768, }
};

#define MAT_AXIS_SIZE 8

DECLARE_AXIS_WITH_DESC(flash_mat_axis,
	MAT_AXIS_SIZE,
	"MAT",
	"Temp") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAT_AXIS_SIZE,
	.data = {
		0,
		8,
		33,
		49,
		63,
		78,
		96,
		125
	}
};


DECLARE_2DMAP8_WITH_DESC(flash_map_limits_load_mat_compensation_2dmap8,
	MAT_AXIS_SIZE,
	"MAF Limits with MAP",
	"MAP Load - MAT Compensation",
	"Percent128U8",
	"DDflash_mat_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		128,
		128,
		128,
		128,

		128,
		128,
		128,
		128
	}
};

#define MAP_LIMITS_BARO_AXIS_SIZE 5

DECLARE_AXIS_WITH_DESC(flash_map_limits_baro_axis,
	MAP_LIMITS_BARO_AXIS_SIZE,
	"Barometric Pressure",
	"Baro") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAP_LIMITS_BARO_AXIS_SIZE,
	.data = {
		0x5d,
		0x7d,
		0x9d,
		0xad,
		0xbd
	}
};


DECLARE_2DMAP8_WITH_DESC(flash_map_limits_load_baro_compensation_2dmap8,
	MAP_LIMITS_BARO_AXIS_SIZE,
	"MAF Limits with MAP",
	"MAP Load - Baro Compensation",
	"Percent128U8",
	"DDflash_map_limits_baro_axis") = {
	TEMP_2DMAP_SRC,
	.data = {
		128,
		128,
		128,
		128,
		128
	}
};


const uint16_t flash_map_load_low_limit_correction = 230;
DECLARE_VALUE_DESC(flash_map_load_low_limit_correction,
        "MAF Limits with MAP",
        "Low Limit",
        "Percent256U16");
const uint16_t flash_map_load_high_limit_correction = 280;
DECLARE_VALUE_DESC(flash_map_load_high_limit_correction,
        "MAF Limits with MAP",
        "High Limit",
        "Percent256U16");
