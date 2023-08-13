mut_table_start = 0x3b4f4;

P0DATA = 0x800700;

/*load ext*/
flash_fuel_map_rpm_axis = 0xb2fa;
flash_main_spark_maps_rpm_axis = 0xb346;
flash_mivec_target_rpm_axis = 0xba5c;

flash_apps_limiting_stabilizer_rpm_axis = 0xb19e;
flash_apps_limiting_stabilizer_apps_limited_axis = 0xc3fe;

flash_apps_limiting_stabilizer_upper_limit_low_gear_neutral_3dmap8 = 0x87c2;
flash_acceleration_gear_shift_stage_limit_low_gear_neutral_3dmap8 = 0x894e;
flash_acceleration_gear_shift_stage1_apps_limit_increment_low_gear_neutral_3dmap8 = 0x8c66;
flash_acceleration_gear_shift_stage2_apps_limit_increment_low_gear_neutral_3dmap8 = 0x8f7e;

flash_acceleration_gear_shift_apps_limit_low_gear_nonneutral_2dmap8 = 0x8428;
flash_acceleration_gear_shift_stage_limit_low_gear_nonneutral_3dmap8 = 0x8a14;
flash_acceleration_gear_shift_stage1_apps_limit_increment_low_gear_nonneutral_3dmap8 = 0x8d2c;
flash_acceleration_gear_shift_stage2_apps_limit_increment_low_gear_nonneutral_3dmap8 = 0x9044;

flash_apps_limiting_stabilizer_upper_limit_high_gear_neutral_3dmap8 = 0x8888;
flash_acceleration_gear_shift_stage_limit_high_gear_smth_3dmap8 = 0x8ada;
flash_acceleration_gear_shift_stage1_apps_limit_increment_high_gear_smth_3dmap8 = 0x8df2;
flash_acceleration_gear_shift_stage2_apps_limit_increment_high_gear_smth_3dmap8 = 0x910a;

flash_acceleration_gear_shift_apps_limit_high_gear_normal_2dmap8 = 0x8436;
flash_acceleration_gear_shift_stage_limit_high_gear_normal_3dmap8 = 0x8ba0;
flash_acceleration_gear_shift_stage1_apps_limit_increment_high_gear_normal_3dmap8 = 0x8eb8;
flash_acceleration_gear_shift_stage2_apps_limit_increment_high_gear_normal_3dmap8 = 0x91d0;

flash_acceleration_gear_shift_apps_limit_coolant_correction_2dmap8 = 0x8444;

flash_decelerating_gear_shift_apps_limited_axis = 0xc478;
flash_decelerating_gear_shift_apps_low_limit_correction_vs_coolant_2dmap8 = 0x94c2;
flash_decelerating_gear_shift_apps_low_limit_ac_on_3dmap8 = 0x94ce;
flash_decelerating_gear_shift_apps_low_limit_ac_off_3dmap8 = 0x9526;
flash_deceleration_gear_shift_rpm_int_axis = 0xca14;
flash_deceleration_gear_shift_low_limit_stage_threshold_ac_off_low_gear_2dmap16 = 0xa8d2;
flash_deceleration_gear_shift_low_limit_stage_threshold_ac_on_low_gear_2dmap16 = 0xa8e6;
flash_deceleration_gear_shift_low_limit_stage_threshold_ac_off_high_gear_2dmap16 = 0xa8fa;
flash_deceleration_gear_shift_low_limit_stage_threshold_ac_on_high_gear_2dmap16 = 0xa90e;
flash_apps_limiting_stabilizer_low_limit_decrements_u16a = 0x204a;

flash_isv_to_target_throttle_position_axis = 0xb9c2;
flash_isv_to_target_throttle_position_2dmap16 = 0x403c;

flash_init_apps_neutral_engine_braking_delay_i1b5on = 0x85c;

flash_boost_control3d_rpm_axis = 0xbfbe;
flash_boost_control3d_tps_axis = 0xc448;
flash_boost_target_load_high_gear_3dmap8 = 0xa502;
flash_boost_target_load_low_gear_3dmap8 = 0xa47c;
flash_wastegate_base_duty_high_gear_3dmap8 = 0x93ec;
flash_wastegate_base_duty_low_gear_3dmap8 = 0x9366;

alt_inputs3_processed = 0x804da8;
tps_main_rcord = 0x804e0a;
gear_ratio = 0x804f70;
engine_rpm = 0x804e5c;
engine_rpm_delta_neg = 0x804e60;
shaft_period1_copy_dline0 = 0x805490;
temp_axis_src = 0x804d30;
sensor_faults = 0x804f0e;
vehicle_movement_decay = 0x804efa;
run_state_extended_flags = 0x804f8e;
gpio1 = 0x804d7c;
knock_sum = 0x805164;
map_engine_load = 0x804e90;
oneshot_crank_event_flags = 0x804f1c;
run_state_flags = 0x804f22;

/*uAFS*/
flash_maf_limits_coolant_compensation_2dmap8 = 0x64ca;
flash_maf_limits_iat_compensation_2dmap8 = 0x64d6;
flash_maf_voltage_axis = 0xbdfa;
flash_maf_scaling_2dmap16 = 0x60f0;
flash_maf_baro_pressure_compensation_axis = 0xbf26;
flash_maf_baro_pressure_compensation_2dmap8 = 0x6250;
flash_maf_compensations_rpm_axis = 0xbf04;
flash_maf_charge_max_base_vs_rpm_2dmap16 = 0x621c;

/*MIVEC*/
flash_mivec_target_rpm_axis = 0xba5c;
flash_mivec_target_load_axis = 0xba32;
flash_mivec_target_3dmap8 = 0x57e6;
flash_mivec_limit_by_colant_2dmap8 = 0x590e;
flash_mivec_advance_max = 0x1c24;
flash_mivec_advance_min = 0x1c22;

/*Injectors*/
flash_injector_latency_power_axis = 0xb262;
flash_injector_latency_vs_power_2dmap8 = 0x28fa;
flash_injector_latency_scaling = 0x800;
flash_injector_low_duty_compensation = 0x2905;

/*Cranking*/
flash_spark_cooldown_axis = 0xb1b8;
flash_cranking_ipw_vs_spark_cooldown_2dmap8 = 0x2958;
flash_cranking_coolant_axis = 0xb59a;
flash_cranking_base_ipw_vs_coolant_2dmap8 = 0x574a;

/*spark kill*/
fuel_cut_splice_into_location = 0x330f0;
test_substitute_spark_advance_int_call_localtion = 0x32bec;
tacho_reset = 0x14ef0;
tacho_reset_call_location = 0x31a08;
const128_nominal_ipw_multiplier_call_location = 0x236e4;

/*map support*/
adc_run = 0x1533c;

/*iat sensor*/
flash_iat_sensor_axis = 0x133aa;
flash_iat_sensor_2dmap8 = 0x1331a;

can0_slot_tx_update = 0x19f04;
can0_slot_rx_get_data = 0x1a0f4;

/*stock RAM*/
can_vehicle_speed = 0x80624e;
can0_flags = 0x805b16;
update_flags_main = 0x804f1a;
torque_request_flags = 0x806262;
load_source_value = 0x804eb8;
can_rx_buffer_main = 0x805b21;

/*for multimode*/
adc_convert_mode_input = 0x147c4;
adc_convert_mode_input_call_location = 0x1c318;

flash_spark_angle_high_octane_mivec_advance_max_3dmultimap8 = 0xcc30;
flash_spark_angle_high_octane_mivec_advance_min_3dmultimap8 = 0xcc50;
flash_spark_angle_high_octane_mivec_advance_target_3dmultimap8 = 0xcc70;
flash_spark_angle_low_octane_mivec_advance_max_3dmultimap8 = 0xcc90;
flash_spark_angle_low_octane_mivec_advance_min_3dmultimap8 = 0xccb0;
flash_spark_angle_low_octane_mivec_advance_target_3dmultimap8 = 0xccd0;

flash_cylinder_volume = 0x1808;
injector_scaling_to_volume_correction = 0x804fe0;

flash_boost_control_high_gear_ratio = 0x233e;
gear_ratio = 0x804f70;

reset_engine_rpm_state = 0x1d818;

engine_rpm_hires = 0x805b42;

update_purge_control_solenoid_duty = 0x14cc4;
wastegate_solenoid_duty = 0x805290;
