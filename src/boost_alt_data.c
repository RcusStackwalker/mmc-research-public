#include <stdint.h>
#include <fmath.h>
#include <maps_decl.h>
#include <maps_desc.h>

#define BOOST_CONTROL_RPM_AXIS_SIZE 14
#define BOOST_CONTROL_TPS_AXIS_SIZE 9

DECLARE_AXIS_DESC_EX(flash_boost_control3d_rpm_axis, "RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_boost_control3d_tps_axis, "Throttle", "Throttle %");

DECLARE_3DMAP8_WITH_DESC(flash_wastegate_base_duty_high_gear_3dmap8_alt,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Turbo",
	"Wastegate Base Duty High Gear - Alt",
	"WGDuty",
	"DXflash_boost_control3d_tps_axis",
	"DXflash_boost_control3d_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { 0x01, 0x02 }
};

DECLARE_3DMAP8_WITH_DESC(flash_wastegate_base_duty_low_gear_3dmap8_alt,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Turbo",
	"Wastegate Base Duty Low Gear - Alt",
	"WGDuty",
	"DXflash_boost_control3d_tps_axis",
	"DXflash_boost_control3d_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { 0x01, 0x02 }
};

DECLARE_3DMAP8_WITH_DESC(flash_boost_target_load_high_gear_3dmap8_alt,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Turbo",
	"Boost Target Load High Gear - Alt",
	"Load8",
	"DXflash_boost_control3d_tps_axis",
	"DXflash_boost_control3d_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { 0x01, 0x02 }
};

DECLARE_3DMAP8_WITH_DESC(flash_boost_target_load_low_gear_3dmap8_alt,
	BOOST_CONTROL_RPM_AXIS_SIZE,
	BOOST_CONTROL_TPS_AXIS_SIZE,
	"Turbo",
	"Boost Target Load Low Gear - Alt",
	"Load8",
	"DXflash_boost_control3d_tps_axis",
	"DXflash_boost_control3d_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = BOOST_CONTROL_RPM_AXIS_SIZE,
	.data = { 0x01, 0x02 }
};

#define DEFINE_ALT_3DMULTIMAPU8(name) \
extern const void *const flash_##name##_3dmap8; \
const void *const flash_##name##_3dmultimapu8[8] = { \
	&flash_##name##_3dmap8,		\
	&flash_##name##_3dmap8_alt,	\
	&flash_##name##_3dmap8,		\
	&flash_##name##_3dmap8,		\
	&flash_##name##_3dmap8,		\
	&flash_##name##_3dmap8,		\
	&flash_##name##_3dmap8,		\
	&flash_##name##_3dmap8,		\
}

DEFINE_ALT_3DMULTIMAPU8(wastegate_base_duty_high_gear);
DEFINE_ALT_3DMULTIMAPU8(wastegate_base_duty_low_gear);

DEFINE_ALT_3DMULTIMAPU8(boost_target_load_high_gear);
DEFINE_ALT_3DMULTIMAPU8(boost_target_load_low_gear);

