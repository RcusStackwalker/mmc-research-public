#include <fmath.h>
#include <maps_desc.h>
#include <maps_decl.h>

#include <engine_rpm_hires.h>
#include <conversions.h>

#define START_CEREMONY_AXIS_SIZE 8

const uint16_t flash_start_ceremony_time = MS_TO_40HZTICKS(4000);

DECLARE_VALUE_DESC(flash_start_ceremony_time,
	"Start Ceremony",
	"Total Time",
	"Time");

DECLARE_AXIS_WITH_DESC(flash_start_ceremony_time_axis,
	START_CEREMONY_AXIS_SIZE,
	"Ignition Time",
	"Time") =
{
	TEMP_AXIS_SRC_XDST,
	.size = START_CEREMONY_AXIS_SIZE,
	.data = {
		MS_TO_40HZTICKS(0),
		MS_TO_40HZTICKS(1000),
		MS_TO_40HZTICKS(1400),
		MS_TO_40HZTICKS(1800),

		MS_TO_40HZTICKS(2200),
		MS_TO_40HZTICKS(2600),
		MS_TO_40HZTICKS(3000),
		MS_TO_40HZTICKS(3400),
	}
};

DECLARE_2DMAP16_WITH_DESC(flash_engine_rpm_start_ceremony_2dmap16,
	START_CEREMONY_AXIS_SIZE,
	"Start Ceremony",
	"Tachometer Animation",
	"RPMhires",
	"DDflash_start_ceremony_time_axis") =
{
	TEMP_2DMAP_SRC,
	.data = {
		RPM_TO_HIRESTICKS(0),
		RPM_TO_HIRESTICKS(0),
		RPM_TO_HIRESTICKS(5000),
		RPM_TO_HIRESTICKS(8000),

		RPM_TO_HIRESTICKS(8000),
		RPM_TO_HIRESTICKS(4000),
		RPM_TO_HIRESTICKS(2000),
		RPM_TO_HIRESTICKS(0),
	}
};
