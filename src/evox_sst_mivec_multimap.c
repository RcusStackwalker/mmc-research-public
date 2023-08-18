#include <stdint.h>
#include <maps_decl.h>
#include <maps_desc.h>

extern const void *const flash_intake_mivec_target_3dmap8;
extern const void *const flash_mdp_load_mivec_target_3dmap16;

extern const void *const flash_mivec_target_rpm_axis;
extern const void *const flash_mivec_target_load_axis;

DECLARE_AXIS_DESC_EX(flash_mivec_target_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_mivec_target_load_axis, "Engine Load", "Load");

#define MIVEC_RPM_AXIS_SIZE 24
#define MIVEC_LOAD_AXIS_SIZE 21

#define DECLARE_MIVEC_TARGET_MAP(symbol, username)				\
	DECLARE_3DMAP8_WITH_DESC(symbol,					\
		MIVEC_RPM_AXIS_SIZE,					\
		MIVEC_LOAD_AXIS_SIZE,						\
		"SST Rcus Moded MIVEC",						\
		username,							\
		"ValveTimingIntake",						\
		"DXflash_mivec_target_load_axis",				\
		"DXflash_mivec_target_rpm_axis") = {				\
		TEMP_3DMAP_SRC,							\
		.xsize = MIVEC_RPM_AXIS_SIZE,					\
		.data = { 0x70 }							\
	}

extern const void *const flash_mdp_load_mdp_axis;
extern const void *const flash_mdp_load_rpm_axis;

DECLARE_AXIS_DESC_EX(flash_mdp_load_rpm_axis, "Engine RPM", "RPM");
DECLARE_AXIS_DESC_EX(flash_mdp_load_mdp_axis, "MAP", "MAP16");

#define MDP_LOAD_RPM_AXIS_SIZE 19
#define MDP_LOAD_MDP_AXIS_SIZE 19

#define DECLARE_MDP_LOAD_MAP(symbol, username)				\
	DECLARE_3DMAP16_WITH_DESC(symbol,					\
		MDP_LOAD_RPM_AXIS_SIZE,					\
		MDP_LOAD_MDP_AXIS_SIZE,						\
		"SST Rcus Moded MIVEC",						\
		username,							\
		"Loadify",						\
		"DXflash_mdp_load_mdp_axis",				\
		"DXflash_mdp_load_rpm_axis") = {				\
		TEMP_3DMAP_SRC,							\
		.xsize = MDP_LOAD_RPM_AXIS_SIZE,					\
		.data = { 0x70 }							\
	}

DECLARE_MIVEC_TARGET_MAP(flash_intake_mivec_target_sport_3dmap8, "Intake MIVEC Target - Sport");
DECLARE_MIVEC_TARGET_MAP(flash_intake_mivec_target_super_sport_3dmap8, "Intake MIVEC Target - Super Sport");

const void *const flash_intake_mivec_targets[3] = {
	&flash_intake_mivec_target_3dmap8,
	&flash_intake_mivec_target_sport_3dmap8,
	&flash_intake_mivec_target_super_sport_3dmap8,
};


DECLARE_MDP_LOAD_MAP(flash_mdp_load_mivec_target_sport_3dmap16, "MAP Load - Sport");
DECLARE_MDP_LOAD_MAP(flash_mdp_load_mivec_target_super_sport_3dmap16, "MAP Load - Super Sport");

const void *const flash_mdp_loads[3] = {
	&flash_mdp_load_mivec_target_3dmap16,
	&flash_mdp_load_mivec_target_sport_3dmap16,
	&flash_mdp_load_mivec_target_super_sport_3dmap16,
};
