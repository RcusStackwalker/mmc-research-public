#define TORQUE_NEW_AXIS_SIZE 29
DECLARE_AXIS_WITH_DESC(flash_new_internal_torque_axis, TORQUE_NEW_AXIS_SIZE, "Torque Axis", "CVTInternalEngineTorque16%") = {
	TEMP_AXIS_SRC_YDST,
	.size = TORQUE_NEW_AXIS_SIZE,
	.data = {
		0,
		0x20,
		0x28,
		0x30,
		0x40,
		0x50,
		0x60,
		0x70,
		0x80,
		0x90,
		0xa0,
		0xb0,
		0xc0,
		0xd0,
		0xe0,
		0xf0,
		0x100,
		0x110,
		0x120,
		0x130,
		0x140,
		0x150,
		0x160,
		0x170,
		0x180,
		0x190,
		0x1a0,
		0x1b0,
		0x1c0,
	}
};

#define TTP_RPM_AXIS_SIZE 15


DECLARE_3DMAP16_WITH_DESC(flash_new_target_throttle_position_rpm_x_torque_3dmap16,
	TTP_RPM_AXIS_SIZE,
	TORQUE_NEW_AXIS_SIZE,
	"LoadExtendedMaps",
	"Target Throttle Position - RPM x Torque",
	"TargetThrottlePosition%1843Max",
	"DDflash_new_internal_torque_axis",
	"DXflash_ttp_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.offset = 0,
	.xsize = TTP_RPM_AXIS_SIZE,
	.data = {}
};

#define TORQUE_OUTPUT_RPM_AXIS_SIZE 16

#define NEW_COMBUSTION_TORQUE_LOAD_AXIS_SIZE 21

DECLARE_AXIS_WITH_DESC(flash_new_combustion_torque_output_load_axis, NEW_COMBUSTION_TORQUE_LOAD_AXIS_SIZE, "Load Axis", "Load") = {
	TEMP_AXIS_SRC_YDST,
	.size = NEW_COMBUSTION_TORQUE_LOAD_AXIS_SIZE,
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

DECLARE_3DMAP16_WITH_DESC(flash_new_combustion_torque_output_3dmap16,
	TORQUE_OUTPUT_RPM_AXIS_SIZE,
	NEW_COMBUSTION_TORQUE_LOAD_AXIS_SIZE,
	"LoadExtendedMaps",
	"Internal Torque",
	"CVTInternalEngineTorque16%",
	"DDflash_new_combustion_torque_output_load_axis",
	"DXflash_torque_ouput_calculations_rpm_axis") =
{
	TEMP_3DMAP_SRC,
	.xsize = TORQUE_OUTPUT_RPM_AXIS_SIZE,
	.data = {}

};
