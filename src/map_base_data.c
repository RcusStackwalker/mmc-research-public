#include <stdint.h>
#include <maps_desc.h>
#include <maps_decl.h>

const uint16_t flash_map_kpa_per_volt = 128 * 64;
DECLARE_VALUE_DESC(flash_map_kpa_per_volt, "MAP Sensor", "MAP Signal Volts to kPa conversion", "uint16");
const uint16_t flash_map_zero_offset = 80;
DECLARE_VALUE_DESC(flash_map_zero_offset, "MAP Sensor", "MAP Signal Zero Offset", "uint16");

#define MAT_SENSOR_AXIS_SIZE 139

DECLARE_AXIS_WITH_DESC(flash_mat_sensor_axis, MAT_SENSOR_AXIS_SIZE, "MAT Sensor Voltage", "ThrottleVoltage16") = {
	TEMP_AXIS_SRC_XDST,
	.size = MAT_SENSOR_AXIS_SIZE,
	.data = {
		0x0e, 0x10,
		0x11, 0x12,
		0x13, 0x14,
		0x15, 0x16,
		0x17, 0x18,
		0x19, 0x1a,
		0x1b, 0x1c,
		0x1d, 0x1e,
		0x1f, 0x20,
		0x21, 0x22,
		0x23, 0x24,
		0x25, 0x26,
		0x27, 0x28,
		0x29, 0x2a,
		0x2b, 0x2c,
		0x2d, 0x2e,
		0x2f, 0x30,
		0x31, 0x32,
		0x34, 0x35,
		0x36, 0x37,
		0x39, 0x3a,
		0x3b, 0x3d,
		0x3e, 0x40,
		0x41, 0x43,
		0x44, 0x46,
		0x48, 0x49,
		0x4b, 0x4d,
		0x4e, 0x50,
		0x52, 0x54,
		0x56, 0x58,
		0x59, 0x5b,
		0x5d, 0x5f,
		0x61, 0x63,
		0x66, 0x68,
		0x6a, 0x6c,
		0x6e, 0x70,
		0x72, 0x75,
		0x77, 0x79,
		0x7b, 0x7e,
		0x80, 0x82,
		0x84, 0x87,
		0x89, 0x8b,
		0x8e, 0x90,
		0x92, 0x94,
		0x97, 0x99,
		0x9b, 0x9d,
		0xa0, 0xa2,
		0xa4, 0xa6,
		0xa8, 0xaa,
		0xac, 0xaf,
		0xb1, 0xb3,
		0xb5, 0xb7,
		0xb8, 0xba,
		0xbc, 0xbe,
		0xc0, 0xc1,
		0xc3, 0xc5,
		0xc6, 0xc8,
		0xc9, 0xcb,
		0xcc, 0xce,
		0xcf, 0xd1,
		0xd2, 0xd3,
		0xd4, 0xd6,
		0xd7, 0xd8,
		0xd9, 0xda,
		0xdb, 0xdc,
		0xdd, 0xde,
		0xdf, 0xe0,
		0xe1, 0xe2,
		0xe3, 0xe4,
		0xe5
	}
};

DECLARE_2DMAP8_WITH_DESC(flash_mat_sensor_2dmap8,
	MAT_SENSOR_AXIS_SIZE,
	"MAP Sensor",
	"MAT Sensor Characteristic",
	"TempScale",
	"DDflash_mat_sensor_axis") =
{
	TEMP_2DMAP_SRC,
	.offset = 40,
	.data = {
		0x78, 0x71,
		0x6f, 0x6d, 0x6b, 0x69,
		0x67, 0x65, 0x63, 0x61,
		0x5f, 0x5d, 0x5c, 0x5a,
		0x59, 0x58, 0x56, 0x55,
		0x54, 0x52, 0x51, 0x50,
		0x4f, 0x4e, 0x4d, 0x4c,
		0x4b, 0x4a, 0x49, 0x48,
		0x47, 0x46, 0x45, 0x44,
		0x43, 0x42, 0x41, 0x40,
		0x3f, 0x3e, 0x3d, 0x3c,
		0x3b, 0x3a, 0x39, 0x38,
		0x37, 0x36, 0x35, 0x34,
		0x33, 0x32, 0x31, 0x30,
		0x2f, 0x2e, 0x2d, 0x2c,
		0x2b, 0x2a, 0x29, 0x28,
		0x27, 0x26, 0x25, 0x24,
		0x23, 0x22, 0x21, 0x20,
		0x1f, 0x1e, 0x1d, 0x1c,
		0x1b, 0x1a, 0x19, 0x18,
		0x17, 0x16, 0x15, 0x14,
		0x13, 0x12, 0x11, 0x10,
		0x0f, 0x0e, 0x0d, 0x0c,
		0x0b, 0x0a, 0x09, 0x08,
		0x07, 0x06, 0x05, 0x04,
		0x03, 0x02, 0x01, 0x00,
		0xff, 0xfe, 0xfd, 0xfc,
		0xfb, 0xfa, 0xf9, 0xf8,
		0xf7, 0xf6, 0xf5, 0xf4,
		0xf3, 0xf2, 0xf1, 0xf0,
		0xef, 0xee, 0xed, 0xec,
		0xeb, 0xea, 0xe9, 0xe8,
		0xe7, 0xe6, 0xe5, 0xe4,
		0xe3, 0xe2, 0xe0, 0xdf,
		0xde, 0xdc, 0xdb, 0xd9,
		0xd8
	}

};

