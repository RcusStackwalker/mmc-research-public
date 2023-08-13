	"Load400_Patch#1 [m32r-bl]" calc_ipw_override_shaft_multiplication_location : { LONG(ps_scale32_base512) }
	"Load400_Patch#2" calc_ipw_override_load_x_nominal_ipw_division_location : { SHORT(0x0400) }
	"Load400_Patch#3" calc_engine_loads_override_lsv_to_load_multiplier1_location : { BYTE(0x0a) }
	"Load400_Patch#4" calc_engine_loads_override_lsv_to_load_multiplier2_location : { BYTE(0x0a) }
	"Load400_Patch#5" calc_engine_loads_override_lsv_to_comp_load_multiplier_location : { SHORT(0x0140) }
	"Load400_Patch#6" load400_math_space : { ../../src/load400_math.o(.text) }
	"Load400_Patch#7" tomo_calc_engine_loads_override_lsv_to_load_multiplier_location : { BYTE(0x0a) }
	"Load400_Patch#8" tomo_calc_engine_loads_override_lsv_to_flow_multiplier_location : { SHORT(0x0200) }
	"Load400_Patch#9" divide_by2_maf_charge_max_base_vs_rpm_2dmap16_location : { 
		SHORT(0x2F5C)
		SHORT(0x328F)
		SHORT(0x37AE)
		SHORT(0x3CCD)
		SHORT(0x451E)
	}
	"Load400_Patch#10" flash_base_spark_limit_reset_load_delta_positive_threshold : { SHORT(0x0006) }
	"Load400_Patch#11" maf_fault_default_load_location : { SHORT(0x4000) }
	"Load400_Patch#12" calc_engine_loads_override_lsv_to_flow_multiplier_location : { SHORT(0x0200) }
	"Load400_Patch#13" divide_by2_maf_load_high_vs_rpm_2dmap16_location : {
		SHORT(0x3106)
		SHORT(0x3106)
		SHORT(0x31fc)
		SHORT(0x30e5)
		SHORT(0x3302)
		SHORT(0x328f)
		SHORT(0x2ec8)
		SHORT(0x3000)
		SHORT(0x3199)
		SHORT(0x32b0)
		SHORT(0x33d7)
		SHORT(0x320c)
		SHORT(0x2fdf)
		SHORT(0x2fdf)
		SHORT(0x2fdf)
		SHORT(0x2fdf)
	}
	"Load400_Patch#14" ipw_safe_change_load_source_threshold_location : { SHORT(102) }

