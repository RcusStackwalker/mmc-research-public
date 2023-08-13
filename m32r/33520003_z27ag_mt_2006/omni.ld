INCLUDE ../m32170.ld
INCLUDE ../math.ld
INCLUDE description.ld

post_fuel_cut_enrichment = 0x805012;

decays_x1_gear_unstable = 0x804966;

calculated_gear = 0x805088;
current_gear = 0x805089;
dash_flash_runner = 0x80508a;
asc_change_lamp = 0x80508e;
asc_off = 0x80508f;
asc_off_prev = 0x805090;
shift_light_pattern = 0x805091;
cvt_dash_data0 = 0x805092;
cvt_dash_data1 = 0x805093;

decays_x1_alt_mode_change_cel_flash_timer = 0x804968;

/*
decays_x1_knock_mil_flash = 0x8049de;
decays_x1_mil_pulse_timer = 0x8049f0;
knock_mil_state = 0x804e34;
knock_mil_flags = 0x804e32;
overrev_cycle_decay = 0x804e36;
revolution_limit = 0x804e38;
nlts_state	= 0x804e3a;
nlts_flags	= 0x804e3c;
nlts_target_rpm	= 0x804e3e;
nlts_rpm_error	= 0x804e40;
overrev_spark_limit = 0x804e42;
init_overrev_spark_limit = 0x804e44;
overrev_spark_limit_dec_step = 0x804e46;

decays_x1_nlts_active = 0x8049e4;

load1byte = 0x804e2c;
*/

/*load400 bindings*/
calc_ipw_override_shaft_multiplication_location = 0x3321c;
calc_ipw_override_load_x_nominal_ipw_division_location = 0x339b6;
calc_engine_loads_override_lsv_to_load_multiplier1_location = 0x1e255;
calc_engine_loads_override_lsv_to_load_multiplier2_location = 0x1e273;
calc_engine_loads_override_lsv_to_comp_load_multiplier_location = 0x1e28e;
tomo_calc_engine_loads_override_lsv_to_load_multiplier_location = 0x64d3d;
tomo_calc_engine_loads_override_lsv_to_flow_multiplier_location = 0x64d8e;
divide_by2_maf_charge_max_base_vs_rpm_2dmap16_location = 0x6222;
flash_base_spark_limit_reset_load_delta_positive_threshold = 0xac4;
maf_fault_default_load_location = 0x332a6;
calc_engine_loads_override_lsv_to_flow_multiplier_location = 0x1e346;
divide_by2_maf_load_high_vs_rpm_2dmap16_location = 0x7d18;
ipw_safe_change_load_source_threshold_location = 0x252a6;
load400_math_space = 0x4f9a8;


/*guard specific*/
regen_crankshaft_rotation_decays = 0x419b0;
regen_crankshaft_rotation_decays_call_location = 0x18668;
obd_rest_handler_injection_location = 0x5ef34;

cruise_control_call_location = 0x1b890;
cruise_control = 0x1b8ec;

get_ig1 = 0x14410;

eeprom_start_area = 0x3b108;

sio0_rx_buffer = 0x8053d4;
sio0_tx_buffer = 0x8053ea;
sio0_tx_count = 0x80542c;
age_x1_ignition = 0x8048fc;

decays_x1_signature = 0x804afc;

update_mil = 0x2f57c;
update_mil_call_location = 0x2e2fc;
update_gpio_outputs = 0x147d4;
update_gpio_outputs_call_location = 0x1b8bc;

calc_iat_call_location = 0x1cfd0;
calc_iat = 0x1d244;

maf_charge_aprx_bound_calc_location = 0x3326c;
adc_convert_maf_call_location = 0x35680;
adc_convert_maf = 0x144f8;

can0_40ms_tx_call_location = 0x38f18;

can0_slot12_rx_update_call_location = 0x49160;


MEMORY {
	UNUSED_MEMORY_FOR_MODS : ORIGIN = 0x56130, LENGTH =0x1000
	UNUSED_RAM_FOR_MODS : ORIGIN = 0x80553c, LENGTH = 0x20
}

SECTIONS {
	"ReplaceROMID" 0x226 : { LONG(0x3352A403) }

	"MainLoadAxesExtension#1 [m32r-ld24-r0]" 0x27af0 : { LONG(flash_new_main_spark_maps_load_axis) }
	"MainLoadAxesExtension#2 [m32r-ld24-r0]" 0x23bc4 : { LONG(flash_new_fuel_map_load_axis) }
	"MainLoadAxesExtension#3 [m32r-ld24-r0]" 0x2e034 : { LONG(flash_new_mivec_map_load_axis) }
	"MainLoadAxesExtension#4.1 [m32r-ld24-r0]" 0x2e03c : {
		LONG(flash_new_mivec_target_3dmultimap8)
	}
	"MainLoadAxesExtension#4.2 [m32r-bl]" 0x2e040 : {
		LONG(multimap8u16)
	}
	"MainLoadAxesExtension#5" 0xcaf0 : {
		LONG(flash_new_high_octane_fuel_3dmap8_main)
		LONG(flash_new_high_octane_fuel_3dmap8_alt)
	}
	"MainLoadAxesExtension#6" 0xcb10 : {
		LONG(flash_new_low_octane_fuel_3dmap8_main)
		LONG(flash_new_low_octane_fuel_3dmap8_alt)
	}

	"MainLoadAxesExtension#7 [m32r-ld24-r0]" 0x27b04 : {
		LONG(flash_new_spark_angle_low_octane_mivec_advance_min_multiset)
	}
	"MainLoadAxesExtension#8 [m32r-bl]" 0x27b08 : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#9 [m32r-ld24-r0]" 0x27b1c : {
		LONG(flash_new_spark_angle_low_octane_mivec_advance_target_multiset)
	}
	"MainLoadAxesExtension#10 [m32r-bl]" 0x27b20 : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#11 [m32r-ld24-r0]" 0x27b54 : {
		LONG(flash_new_spark_angle_low_octane_mivec_advance_target_multiset)
	}
	"MainLoadAxesExtension#12 [m32r-bl]" 0x27b58 : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#13 [m32r-ld24-r0]" 0x27b6c : {
		LONG(flash_new_spark_angle_low_octane_mivec_advance_max_multiset)
	}
	"MainLoadAxesExtension#14 [m32r-bl]" 0x27b70 : {
		LONG(sparkgearmultimap8u16)
	}


	"MainLoadAxesExtension#15 [m32r-ld24-r0]" 0x27be0 : {
		LONG(flash_new_spark_angle_high_octane_mivec_advance_min_multiset)
	}
	"MainLoadAxesExtension#16 [m32r-bl]" 0x27be4 : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#17 [m32r-ld24-r0]" 0x27bec : {
		LONG(flash_new_spark_angle_high_octane_mivec_advance_target_multiset)
	}
	"MainLoadAxesExtension#18 [m32r-bl]" 0x27bf0 : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#19 [m32r-ld24-r0]" 0x27c0c : {
		LONG(flash_new_spark_angle_high_octane_mivec_advance_target_multiset)
	}
	"MainLoadAxesExtension#20 [m32r-bl]" 0x27c10 : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#21 [m32r-ld24-r0]" 0x27c18 : {
		LONG(flash_new_spark_angle_high_octane_mivec_advance_max_multiset)
	}
	"MainLoadAxesExtension#22 [m32r-bl]" 0x27c1c : {
		LONG(sparkgearmultimap8u16)
	}

	"MainLoadAxesExtension#23" 0xcb30 : {
		LONG(flash_new_warmup_retard_mivec_advance_max_3dmap8)
		LONG(flash_new_warmup_retard_mivec_advance_max_3dmap8)
	}
	"MainLoadAxesExtension#24" 0xcb50 : {
		LONG(flash_new_warmup_retard_mivec_advance_min_3dmap8)
		LONG(flash_new_warmup_retard_mivec_advance_min_3dmap8)
	}
	"MainLoadAxesExtension#25" 0xcb70 : {
		LONG(flash_new_warmup_retard_mivec_advance_target_3dmap8)
		LONG(flash_new_warmup_retard_mivec_advance_target_3dmap8)
	}
	"MainLoadAxesExtension#16" 0x49a00 : { ../../src/load_extender_alt.o(.rodata) }

	"Alt Injector Scaling [m32r-bl]" 0x236dc : { LONG(new_update_injector_scaling_to_volume_correction) }

	"Use separate mode index for multimap8u16 [m32r-lduh-r1]" 0x4f7b4 : {
		LONG(new_mode_idx)
	}
	"Use separate mode index for multimapu16 [m32r-lduh-r1]" 0x4f7cc : {
		LONG(new_mode_idx)
	}
	"Use separate mode index for multiu16 [m32r-lduh-r1]" 0x4f810 : {
		LONG(new_mode_idx)
	}

	"Alt Boost #1 [m32r-ld24-r0]" 0x2cf14 : {
		LONG(flash_wastegate_base_duty_high_gear_3dmultimapu8)
	}
	"Alt Boost #2 [m32r-ld24-r0]" 0x2cf1c : {
		LONG(flash_wastegate_base_duty_high_gear_3dmultimapu8)
	}
	"Alt Boost #3 [m32r-ld24-r0]" 0x2cf30 : {
		LONG(flash_wastegate_base_duty_low_gear_3dmultimapu8)
	}
	"Alt Boost #4 [m32r-ld24-r0]" 0x2cf38 : {
		LONG(flash_wastegate_base_duty_low_gear_3dmultimapu8)
	}
	"Alt Boost #5 [m32r-bl]" 0x2cf3c : {
		LONG(multimap8u16)
	}

	"Alt Boost #6 [m32r-ld24-r0]" 0x2d0d0 : {
		LONG(flash_boost_target_load_high_gear_3dmultimapu8)
	}
	"Alt Boost #7 [m32r-ld24-r0]" 0x2d0d8 : {
		LONG(flash_boost_target_load_low_gear_3dmultimapu8)
	}
	"Alt Boost #8 [m32r-bl]" 0x2d0dc : {
		LONG(multimap8u16)
	}


	INCLUDE ../guard_injection.ld
	INCLUDE ../load400.ld
	INCLUDE ../nlts.ld


	"MAP Voltage Logging - MUT B1" mut_table_start + 0xb1 * 4 : { LONG(adc_byte_map + 1) }
	"Extended Load Logging - MUT B6" mut_table_start + 0xb6 * 4 : { LONG(load_source_value) }
	"MAP Signal Logging - MUT B7" mut_table_start + 0xb7 * 4 : { LONG(map_avg) }
	"MAT Voltage Logging - MUT B8" mut_table_start + 0xb8 * 4 : { LONG(adc_byte_mat + 1) }
	"MAT Logging - MUT B9" mut_table_start + 0xb9 * 4 : { LONG(mat + 1) }
	"Mode Logging - MUT BA" mut_table_start + 0xba * 4 : { LONG(new_mode_idx + 1) }

	"Omni#1" 0x68eac : {
/*
		obd.o(.rodata*)
		obd.o(.text)
		obd_data.o(.rodata)
		obd_data.o(.text)
*/
		*(.text)
		*(.rodata)
		*(.rodata*)
		*(knock_mil_data_section)
	}


	"MAP Logging: Inject update_mat [m32r-bl]" calc_iat_call_location : { LONG(hijack_calc_iat) }
	"MAP Logging: Inject adc_convert_map [m32r-bl]" adc_convert_maf_call_location : { LONG(hijack_800hz_adc_call) }
	"MAP Logging: Inject cycle_process_map [m32r-bl]" maf_charge_aprx_bound_calc_location : { LONG(hijack_maf_charge_aprx_bound) }

	/*We need to disable access to one rx slot and reconfigure it to receive ETACS messages. then we need 0x1b5 transmission slot*/
	"CVT Engine to Dash message: Reconfigure can slot#15 RX->TX" 0x11cf3 : { BYTE(0x80) }
	"CVT Engine to Dash message: Reconfigure can slot#15 SID0" 0x11d03 : { BYTE(0x06) }
	"CVT Engine to Dash message: Reconfigure can slot#15 SID1" 0x11d13 : { BYTE(0x35) }
	"CVT Engine to Dash message: Reconfigure can slot#15 DLC" 0x11d53 : { BYTE(0x08) }
	"CVT Engine to Dash message: send [m32r-bl]" can0_40ms_tx_call_location : { LONG(new_can0_40ms_tx) }

	/*SID=0x239, DLC=8*/
	"CVT Dash Control. ASC to Dash message: Reconfigure can slot#12 SID0" 0x11d00 : { BYTE(0x08) }
	"CVT Dash Control. ASC to Dash message: Reconfigure can slot#12 SID1" 0x11d10 : { BYTE(0x39) }
	"CVT Dash Control. ASC to Dash message: Reconfigure can slot#12 DLC" 0x11d50 : { BYTE(0x08) }
	"CVT Dash Control. ASC to Dash message: Receive [m32r-bl]" can0_slot12_rx_update_call_location : {
		LONG(update_asc_to_dash_rx)
	}

	"Mode Selector. Activate Selection [m32r-bl]" 0x1c318 : {
		LONG(new_adc_convert_mode_input)
	}

	/*SID=0x423, DLC=8*/
	"Mode Selector. ETACS Message: Reconfigure can slot#5(OBD Reply) TX->RX" 0x11ce9 : { BYTE(0x40) }
	"Mode Selector. ETACS Message: Reconfigure can slot#5(OBD Reply) SID0" 0x11cf9 : { BYTE(0x10) }
	"Mode Selector. ETACS Message: Reconfigure can slot#5(OBD Reply) SID1" 0x11d09 : { BYTE(0x23) }
	"Mode Selector. ETACS Message: Stubout can slot#5 tx access" 0x492b8 : {
		SHORT(0x7000)
		SHORT(0x7000)
	}
	"Mode Selector. ETACS Message: Replace can slot#15 access [m32r-bl]" 0x4915c : {
		LONG(can_etacs_rx_update)
	}

	"Precision Boost: Replace purge control with boost (x4 precision) [m32r-bl]" 0x417e8 : {
		LONG(update_purge_solenoid_duty_from_wastegate)
	}

	"Start Ceremony: tachometer [m32r-bl]" 0x1d7f8 : {
		LONG(new_reset_engine_rpm_state)
	}


	INCLUDE ../knockcel_injection.ld
	INCLUDE ../gpio_outputs_hijack.ld

	"RAM" : {
		*(COMMON)
	} > UNUSED_RAM_FOR_MODS

	"data_desc" 0x60000 : {
		*(data_desc)
	}

	"Overload map x2" 0x21e45 : { BYTE(0x43) }

}
