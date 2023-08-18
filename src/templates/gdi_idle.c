#include "maps_desc.h"

DECLARE_AXIS_DESC_EX(flash_idle_coolant_axis, "Coolant Temperature", "Temp");

DECLARE_2DMAP8_DESC(flash_icomp_base_neutral_1a_2dmap8, "Idle", "Base IAC - Neutral - 1A", "uint8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_icomp_base_neutral_1b_2dmap8, "Idle", "Base IAC - Neutral - 1B", "uint8", "DXflash_idle_coolant_axis");

DECLARE_2DMAP8_DESC(flash_icomp_base_neutral_2a_2dmap8, "Idle", "Base IAC - Neutral - 2A", "uint8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_icomp_base_neutral_2b_2dmap8, "Idle", "Base IAC - Neutral - 2B", "uint8", "DXflash_idle_coolant_axis");

DECLARE_2DMAP8_DESC(flash_icomp_base_neutral_3a_2dmap8, "Idle", "Base IAC - Neutral - 3A", "uint8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_icomp_base_neutral_3b_main_2dmap8, "Idle", "Base IAC - Neutral - 3B - MAIN", "uint8", "DXflash_idle_coolant_axis");

DECLARE_2DMAP8_DESC(flash_target_idle_rpm_neutral_1a_2dmap8, "Idle", "Target Idle RPM - Neutral - 1A", "RPM8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_target_idle_rpm_neutral_1b_2dmap8, "Idle", "Target Idle RPM - Neutral - 1B", "RPM8", "DXflash_idle_coolant_axis");

DECLARE_2DMAP8_DESC(flash_target_idle_rpm_neutral_2a_2dmap8, "Idle", "Target Idle RPM - Neutral - 2A", "RPM8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_target_idle_rpm_neutral_2b_2dmap8, "Idle", "Target Idle RPM - Neutral - 2B", "RPM8", "DXflash_idle_coolant_axis");

DECLARE_2DMAP8_DESC(flash_target_idle_rpm_neutral_3a_2dmap8, "Idle", "Target Idle RPM - Neutral - 3A", "RPM8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_target_idle_rpm_neutral_3b_main_2dmap8, "Idle", "Target Idle RPM - Neutral - 3B - MAIN", "RPM8", "DXflash_idle_coolant_axis");




DECLARE_2DMAP8_DESC(flash_icomp_base_drive1_2dmap8, "Idle", "Base IAC - Drive - 1", "uint8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_icomp_base_drive2_2dmap8, "Idle", "Base IAC - Drive - 2", "uint8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_icomp_base_drive3_main_2dmap8, "Idle", "Base IAC - Drive - 3 - MAIN", "uint8", "DXflash_idle_coolant_axis");

DECLARE_2DMAP8_DESC(flash_target_idle_rpm_drive1_2dmap8, "Idle", "Target Idle RPM - Drive - 1", "RPM8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_target_idle_rpm_drive2_2dmap8, "Idle", "Target Idle RPM - Drive - 2", "RPM8", "DXflash_idle_coolant_axis");
DECLARE_2DMAP8_DESC(flash_target_idle_rpm_drive3_main_2dmap8, "Idle", "Target Idle RPM - Drive - 3 - MAIN", "RPM8", "DXflash_idle_coolant_axis");
