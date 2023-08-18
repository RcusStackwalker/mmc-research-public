
#include <maps_desc.h>


DECLARE_AXIS_DESC_EX(flash_basic3_secondary_speed_safe_axis, "Secondary Speed", "uint16");
DECLARE_AXIS_DESC_EX(flash_basic4_secondary_speed_safe_axis, "Secondary Speed", "uint16");

DECLARE_2DMAP8_DESC(flash_psst_max_tcunlocked_manual_vs_ss_2dmap8,
	"CVT Primary Speed Control",
	"Target Speed Max - Torque Converter Unlocked - Manual",
	"SpeedU8x50",
	"DXflash_basic3_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_psst_max_tcunlocked_auto_vs_ss_2dmap8,
	"CVT Primary Speed Control",
	"Target Speed Max - Torque Converter Unlocked - Auto",
	"SpeedU8x50",
	"DXflash_basic3_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_psst_max_tclocked_manual_vs_ss_2dmap8,
	"CVT Primary Speed Control",
	"Target Speed Max - Torque Converter Locked - Manual",
	"SpeedU8x50",
	"DXflash_basic3_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_psst_max_tclocked_auto_vs_ss_2dmap8,
	"CVT Primary Speed Control",
	"Target Speed Max - Torque Converter Locked - Auto",
	"SpeedU8x50",
	"DXflash_basic3_secondary_speed_safe_axis");


DECLARE_2DMAP8_DESC(flash_psst_kickdown_drive_vs_ss_2dmap8,
	"CVT Primary Speed Control",
	"Kickdown Target Speed - Drive",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_psst_kickdown_nondrive_vs_ss_2dmap8,
	"CVT Primary Speed Control",
	"Kickdown Target Speed - Nondrive",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");


DECLARE_2DMAP8_DESC(flash_inhibitor_position_pss_min_main_2dmap8,
	"CVT Primary Speed Control",
	"Target Speed Min - Main",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_inhibitor_position_pss_min_ds_2dmap8,
	"CVT Primary Speed Control",
	"Target Speed Min - Ds",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");


DECLARE_2DMAP8_DESC(flash_cvt_manual_mode_primary_speed_1st_2dmap8,
	"CVT Primary Speed Control",
	"Manual Mode Thresholds - 1",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_cvt_manual_mode_primary_speed_2nd_2dmap8,
	"CVT Primary Speed Control",
	"Manual Mode Thresholds - 2",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_cvt_manual_mode_primary_speed_3rd_2dmap8,
	"CVT Primary Speed Control",
	"Manual Mode Thresholds - 3",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_cvt_manual_mode_primary_speed_4th_2dmap8,
	"CVT Primary Speed Control",
	"Manual Mode Thresholds - 4",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_cvt_manual_mode_primary_speed_5th_2dmap8,
	"CVT Primary Speed Control",
	"Manual Mode Thresholds - 5",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");

DECLARE_2DMAP8_DESC(flash_cvt_manual_mode_primary_speed_6th_2dmap8,
	"CVT Primary Speed Control",
	"Manual Mode Thresholds - 6",
	"SpeedU8x50",
	"DXflash_basic4_secondary_speed_safe_axis");
