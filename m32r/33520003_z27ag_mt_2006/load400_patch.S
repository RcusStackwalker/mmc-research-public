	.section calc_ipw_override_shaft_multiplication, "a"
	bl ps_scale32_base512

	.section calc_ipw_override_load_x_nominal_ipw_division, "a"
	ldi r2,#1024	; originally it was 2048, in evo they divide by 2048 but multiplier by 2, we'll just take easier way

	.section calc_engine_loads_override_lsv_to_load_multiplier1, "a"
	ldi r1,#10

	.section calc_engine_loads_override_lsv_to_load_multiplier2, "a"
	slli r2,#0x2
	ldi r1,#10

	.section calc_engine_loads_override_lsv_to_comp_load_multiplier, "a"
	ldi r1,#320

	.section calc_engine_loads_override_lsv_to_flow_multiplier, "a"
	ldi r1,#512

	.section tomo_calc_engine_loads_override_lsv_to_load_multiplier, "a"
	ldi r1,#10

	.section tomo_calc_engine_loads_override_lsv_to_flow_multiplier, "a"
	ldi r1,#512

	.section divide_by2_maf_charge_max_base_vs_rpm_2dmap16, "a"
	.short 0xcd36
	.short 0x2F5C
	.short 0x328F
	.short 0x37AE
	.short 0x3CCD
	.short 0x451E

	.section maf_fault_default_load, "a"
	ldi r9,0x4000

	.section flash_base_spark_limit_reset_load_delta_positive_threshold, "a"
	.short 0x0006
	.short 0x0080

	.section divide_by2_maf_load_high_vs_rpm_2dmap16, "a"
	.short 0x3106
	.short 0x3106
	.short 0x31fc
	.short 0x30e5
	.short 0x3302
	.short 0x328f
	.short 0x2ec8
	.short 0x3000
	.short 0x3199
	.short 0x32b0
	.short 0x33d7
	.short 0x320c
	.short 0x2fdf
	.short 0x2fdf
	.short 0x2fdf
	.short 0x2fdf

exit:
	.end
