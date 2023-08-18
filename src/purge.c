
void calc_purge_control_duty()
{
	desired_purge_control_duty_prev = desired_purge_control_duty;
	if (mode_flags[1] & 0x1000) {//enabled
		update_purge_flags_extra();
		purge_related_call40774();
		uint16_t l_duty = get_purge_control_duty();
		if ((run_state_flags & 0x10)
		&& ((mut_actuator_tests[0] & 0x04)
		|| (mut_actuator_tests[1] & 0x08))) {
			l_duty = 255;
		}
		if (!(slow_valve_test_state_flags & 0x01))
			desired_purge_control_duty = MIN16(test_substitute_purge_control_duty(l_duty), 255);
	} else {
		desired_purge_control_duty = 0;
	}
	purge_control_duty_age = 0;
}

void update_purge_flags_extra()
{
	HYSTERESIS_FLAG(purge_flags, 0x08, engine_rpm_8kmax, flashd9c_u16, flashd9a_u16);
	HYSTERESIS_FLAG(purge_flags, 0x02, ecu_load8, flashd96_u16, flashd94_u16);

	calc_axis(&flashb5e0_rpm_axis);
	uint16_t l_load_threshold = map8u16(&flash2e20_const0_2dmap8);
	HYSTERESIS_FLAG(purge_flags, 0x04, map_engine_load8, s_scale_base256(l_load_threshold, flash98_u16), l_load_threshold);

	BIT_CONDITION16(purge_flags, 0x0800,  (flash148a_u16 < ecu_load8) && (flash148c_u16 < tps_main_rcord));

	if (!(run_state_flags & 0x08)) {
		decays_x1.fp13814_u16 = flash10d6_u16;
	}
	if (mode_flags[3] & 0x2000) { // disabled
		if (fp11648 & 0x40) {
			fps_and_ac_support_flags |= 0x20;
		} else {
			fps_and_ac_support_flags &= ~0x20;
		}
		if ((fp10418_f16 & 0x08)
		&& (injector_disable_reason_flags & 0xef)) {
			fps_and_ac_support_flags |= 0x40;
		} else {
			fps_and_ac_support_flags &= ~0x40;
		}
	} else {
		fps_and_ac_support_flags &= ~0x60;
	}

	uint16_t l_flags = 0;
	if (is_purge_not_advisable()) {
		l_flags = 0x20;
	} else if (is_purge_needed()) {
		l_flags = 0x40;
	}
	purge_flags = (purge_flags & ~0x60) | (l_flags & 0x60);

	BIT_CONDITION16(purge_flags, 0x1000, ((purge_flags & 0x0840) == 0x0840) && !(run_state_flags & 0x80));
}

uint16_t is_purge_not_advisable()
{
	l_rpm_age = (coolant_temp_prestart >= flash10e6_u16 ? flash10e8_u16 : flash10ea_u16) * 80;

	BIT_CONDITION16(purge_flags, 0x4000, conv8to16(flash10ec_u16) >= oxygen_feedback_trim);
	BIT_CONDITION16(purge_flags, 0x2000, (run_state_flags & 0x0800) && (decays_x4.stoich_cross2 < s_sub16(flash_init_stoich_cross_decay, alt_inputs1_processed & 0x80 ? flash2032_u16 : flash10f4_u16)));

	r0 = flash1692_u16;
	if ((run_state_flags & 0x11)
	|| (sensor_faults & 0x08)
	|| (!(purge_flags & 0x1000) && !decays_x4.purge_in_progress)
	|| (fp10418_f16 & 0xbb)
	|| (fp10144_f16 & 0x02)) {
		r0 = 0;
		purge_flags &= ~0x11;
		decays_x1.fp13796_u16 = 0;
		decays_x1.fp13800_u16 = 0;
		decays_x1.fp13798_u16 = 0;
		decays_x1.purge_unused_fp13794_u16 = flash161e_u16;
	} else {
		if ((flash1612_u16 < engine2_load8)
		&& (flash1d06_u16 < current_max_apps_main_delta_negative)
		&& (vehicle_speed_frequency < flash1616_u16)
		&& !(alt_inputs1_processed & 0x20)//false
		&& (r0 >= purge_fp11570_u16)) {
			purge_flags |= 0x01;

			if (!decays_x1.fp13798_u16 && !decays_x1.fp13800_u16)
				decays_x1.fp13796_u16 = flash1620_u16;

			decays_x1.fp13798_u16 = flash1618_u16;
		} else {
			purge_flags &= ~0x01;
		}
		if ((flash161a_u16 < engine2_load8)
		&& (vehicle_speed_frequency < flash161c_u16)
		&& !(alt_inputs1_processed & 0x80)
		&& !(alt_inputs1_processed & 0x20) { //false
			if (!decays_x1.purge_unused_fp13794_u16) {
				purge_flags |= 0x10;
				decays_x1.fp13800_u16 = flash1624_u16;
			}
		} else {
			purge_flags &= ~0x10;
			decays_x1.purge_unused_fp13794_u16 = flash161e_u16;
		}
	}
	if ((sensor_faults & 0x08)
	&& ((flash10d8_u16 >= engine_rpm_8kmax) || (flash10da_u16 >= adc_byte_tps_main_raw)))
		return 1;

	if (!(sensor_faults & 0x08)
	&& ((closed_loop_flags & 0x80) || !(purge_flags & 0x04) || (purge_flags & 0x02)))
		return 1; //too high load

	if (run_state_flags & 0x08)
		return 1;

	if (flash_modulated_displacement_mode //1
	&& flash33a_u8 //1
	&& ((afr_correction_flags & 0x40) || decays_x1.modulated_displacement_active))
		return 1;

	if ((fps_and_ac_support_flags & 0x40)
	|| (purge_flags & 0x4000) //stft negative clipping
	|| (purge_flags & 0x2000) //closed loop unable to cross stoich
	|| !(purge_flags & 0x08)) //low rpm
		return 1;

	if (age_x1.rpm < l_rpm_age)
		return 1;

	if (run_state_flags & 0x11)
		return 1;

	if (coolant_temp_filtered < flashd8c_u16)
		return 1;//64 deg

	if (decays_x1.fp13800_u16
	|| decays_x1.fp13798_u16)
		return 1;

	if (purge_flags & 0x8000)
		return 1;//purge induced stft fault

	if (!(sensor_faults & 0x08) && !(run_state_flags & 0x80) && !(purge_flags & 0x0800))
		return 1;

	if ((mode_flags[3] & 0x04) //jdm disabled
	&& (usdm_purge_flags & 0x08))
		return 1;

	if ((mode_flags[3] & 0x80) //enabled
	&& (usdm_purge_flags & 0x04))
		return 1;

	if (flash340_u8) { //false
		if (!flash_oxygen_trim_fuel_cut_mode && decays_x1.fuel_cut_continuing)
			return 1;

		if (flash_oxygen_trim_fuel_cut_mode && (fp12486_f16 & 0x2000))
			return 1;
	}

	if ((mode_flags[3] & 0x2000)
	&& (usdm_purge_flags & 0x10))
		return 1;

	if ((mode_flags[3] & 0x2000)
	&& (fp10144_f16 & 0x02))
		return 1;

	return 0;
}

uint16_t is_purge_needed()
{
	if (!(run_state_flags & 0x80)
	&& (purge_flags & 0x0800)) return 1;

	if (baro_pressure < flash8e0_u16) return 1;

	if (iat >= flash8dc_u16) return 1;

	if ((mode_flags[3] & 0x2000)
	&& (usdm_purge_flags & 0x20)) return 1;

	if (!(sensor_faults & 0x08)) return 0;

	if (flash10d8_u16 >= engine_rpm_8kmax) return 0;

	if (flash10da_u16 >= adc_byte_tps_main_raw) return 0;

	return 1;
}

void purge_related_call40774()
{
	if ((run_state_flags & 0x10)
	|| !decays_x1.fp13436_u16) {
		if ((run_state_flags & 0x10)
		&& (purge_flags & 0x80) //never set?
		&& !(purge_flags & 0x20)) {
			decays_x1.fp13436_u16 = flashd8e_u16 * 80;
			purge_flags &= ~0x80;
		} else if (!(purge_flags & 0xc0)) {
			decays_x1.fp13436_u16 = flashd90_u16 * 80;
			purge_flags |= 0x30;
		}
	}
}

void get_purge_control_duty()
{
	update_purge_open_rate();
	update_purge_base_state();
	ret = calc_purge_duty();
	return fault_safe_purge_duty(ret);
}

void update_purge_base_state()
{
	if (!decays_x2.purge_related_load_change
	&& ((flash_purge_lsvdp_min < current_max_load_source_value_delta_positive)
	|| (flash_purge_lsvdn_min < current_max_load_source_value_delta_negative))) {
		decays_x2.purge_related_load_change = flash1458_u16;
	}

	l_prev = fp11560_f16 & 0x0800;
	BIT_CONDITION16(fp11560_f16, 0x0800, decays_x1.fp13798_u16 || (purge_flags & 0x01));

	if (l_prev && !(fp11560_f16 & 0x0800))
		purge_valve_force = 0;

	if (!desired_purge_control_duty) {
		purge_valve_force = decays_x1.fp13798_u16 || (purge_flags & 0x01) ? 128 : 0;
		fp11560_f16 &= ~0x1000;
	} else if (!(alt_inputs1_processed & 0x80) //apps non neutral
	|| (flash343_u8/*1*/ && (closed_loop_flags & 0x0400))) {//reset
		fp11560_f16 |= 0x1000;
		if (update_flags_main & 0x04) {
			purge_valve_force = MIN16(s_add16(purge_valve_force, flash1698_u16), 128);
		}
		if (purge_valve_force >= 128)
			fp11560_f16 &= ~0x1000;
	} else {
		fp11560_f16 |= 0x1000;
		if (update_flags_main & 0x04) {
			purge_valve_force = MIN16(s_add16(purge_valve_force, flash1610_u16), 128);
		}
		if (purge_valve_force >= 128)
			fp11560_f16 &= ~0x1000;
	}
	purge_fp11570_u16 = s_sub16(s_mul_divu16(conv16to8(purge_stft_corrector_hires_smoothed), purge_valve_force, 128) + 128, purge_valve_force);

	BIT_CONDITION16(purge_flags, 0x8000, (purge_flags & 0x6000) && desired_purge_control_duty && !(fp10418_f16 & 0xbb));

	if ((run_state_flags & 0x11)
	|| !decays_x4.purge_in_progress
	|| (purge_flags & 0x1000) //open loop
	|| (fp10418_f16 & 0xbb)
	|| (fp10144_f16 & 0x02)
	|| (purge_flags & 0x8000)) {//purge induced stft fault
		fp11580_sum = 0;
		fp11584_u16_smoothed = 0;
		fp11584_u16 = 0;
		fp11586_step = 0;
		purge_tank_pressure_rate = 0;
		purge_stft_corrector_prev = 128;
		purge_stft_corrector = 128;
		purge_fp11570_u16 = 128;
		purge_stft_in_use = 128;
		purge_stft_corrector_hires_smoothed = 0x8080;
		fp11568_decay = flash13c0_u16;
		fp11560_f16 &= ~0xc000;
		purge_flags &= ~0x11;
		decays_x1.fp13796_u16 = 0;
		decays_x1.fp13800_u16 = 0;
		decays_x1.fp13798_u16 = 0;
		decays_x1.purge_unused_fp13794_u16 = flash161e_u16;
	}

	HYSTERESIS_FLAG(purge_flags, 0x0400, maf_sensor_flow8, flash10de_u16, flash10dc_u16);

	if (((sensor_faults & 0x08) || !(purge_flags & 0x0400))
	&& (!(fpp12532_f16 & 0x0300) || !(usdm_purge_flags & 0x30))) {
		purge_flags &= ~0x0100;
	} else {
		purge_flags |= 0x0100;
	}

	if (purge_flags & 0x0100) {
		calc_axis(&flash_purge_base_high_rpm_axis);//0.5-4k
		calc_axis(&flash_purge_base1_load_axis);
		purge_duty_max = map8u16(&flash_purge_duty_max_high_3dmap8);
		calc_axis(&flash_purge_base1_load_axis);
		estimated_purge_tank_pressure_rate_max = map8u16(&flash33e4_purge_3dmap8);
		purge_duty_min = flash13c4_u16;
	} else {
		calc_axis(&flash_purge_base_low_rpm_axis);//0.5-2k
		calc_axis(&flash_purge_base1_load_axis);
		purge_duty_max = map8u16(&flash_purge_duty_max_low_3dmap8);
		calc_axis(&flash_purge_base1_load_axis);
		estimated_purge_tank_pressure_rate_max = map8u16(&flash3396_purge_3dmap8);
		purge_duty_min = flash13c2_u16;
	}

	estimated_purge_tank_pressure_rate = MIN16(s_scale_base128(purge_tank_pressure_rate, flash13da_u16/*128*/), estimated_purge_tank_pressure_rate_max);
	fp11560_f16 &= ~0x0400;
	fuel_tank_pressure_absdiff = ABS_DIFF(adc_byte_fuel_tank_pressure_prev,adc_byte_fuel_tank_pressure);
	if (fuel_tank_pressure_absdiff >= flash2040_u16) {
		fp11560_f16 |= 0x0200;
		decays_x2.unstable_fuel_tank_pressure = flash2042_u16;
	} else if (decays_x2.unstable_fuel_tank_pressure) {
		fp11560_f16 |= 0x0200;
	} else {
		fp11560_f16 &= ~0x0200;
	}

	if (update_flags_main & 0x20)
		adc_byte_fuel_tank_pressure_prev = adc_byte_fuel_tank_pressure;

	if (!(sensor_faults & 0x08)
	&& desired_purge_control_duty
	&& !(purge_flags & 0x1000)
	&& !(fp10418_f16 & 0xbb)
	&& !(fp10144_f16 & 0x02)) {
		if (update_flags_main & 0x02) {
			if (!(fp11560_f16 & 0x1000) //upcounted purge_valve_force
			&& !(fp11560_f16 & 0x0200)) { //stable fuel tank pressure
				if (!fp11568_decay) {
					fp11584_u16 = s16_divu32_16(fp11580_sum, fp11560_f16 & 0x2000 ? flash1456_u16 : flash13c0_u16);//100
					if (!(fp11560_f16 & 0x4000)) {
						fp11584_u16_smoothed = fp11584_u16;
						fp11560_f16 |= 0x4000;
					} else {
						fp11584_u16_smoothed = aprxu16_256(fp11584_u16_smoothed, fp11584_u16, flash13de_u16 >= purge_tank_pressure_rate ? flash13e6_u16 : flash13e8_u16);
					}
					if (decays_x2.purge_related_load_change) {
						fp11568_decay = flash1456_u16;
						fp11560_f16 |= 0x2000;
					} else {
						fp11568_decay = flash13c0_u16;
						fp11560_f16 &= ~0x2000;
					}
					fp11580_sum = 0;
					fp11560_f16 |= 0x8000;//reinit stft
				} else {
					S_DEC(fp11568_decay);
					fp11560_f16 &= ~0x8000;
				}
			} else {
				fp11580_sum = 0;
				fp11560_f16 &= ~0x8000;
				fp11568_decay = flash13c0_u16;
				fp11560_f16 &= ~0x2000;
			}
			purge_stft_corrector_prev = purge_stft_corrector;
			purge_stft_corrector = s_sub16(
				s_16to8(s_add16(128, s_divu16(estimated_purge_tank_pressure_rate, 8))),
				s_mul_divu16(fp11584_u16_smoothed, estimated_purge_tank_pressure_rate, 1024)
			);
			purge_stft_corrector_hires_smoothed = aprxu16_256(purge_stft_corrector_hires_smoothed, purge_stft_corrector * 256, flash13c6_u16);
			purge_fp11570_u16 = s_sub16(s_mul_divu16(conv16to8(purge_stft_corrector_hires_smoothed), purge_valve_force, 128) + 128, purge_valve_force);
			if (fp11560_f16 & 0x8000) {
				purge_modified_stft = get_purge_modified_stft(&flash_cylinder_head);
			}
			purge_stft_in_use = fp11560_f16 & 0x8000 ? purge_modified_stft : oxygen_feedback_trim_smoothed;
			if (!(fp11560_f16 & 0x1000)
			&& !(fp11560_f16 & 0x0200)) { //stable fuel tank pressure
				if (estimated_purge_tank_pressure_rate) {
					fp11586_step = s16_divu32_16(
						s_sub32(mul16(s_add16(estimated_purge_tank_pressure_rate, 2048), 128),
							mul16(s_add16(purge_stft_in_use * 2, 256), s_add16(purge_fp11570_u16 * 2, 256))),
						estimated_purge_tank_pressure_rate);
				} else {
					fp11586_step = 0;
				}
				fp11580_sum = s_add32(fp11580_sum, fp11586_step);
			}
		} //update_flags_main & 0x02

		if (flash13e2_u16 >= purge_stft_corrector) { //0x40
			purge_tank_pressure_rate = MIN16(purge_tank_pressure_rate, flash13d8_u16); //16
		} else if ((vehicle_speed_frequency < flash2044_u16) && APPS_IDLE_OFF_EVENT ) {
			purge_tank_pressure_rate = MIN16(purge_tank_pressure_rate, flash2046_u16); //61
		}

		if ((update_flags_main & 0x10)
		&& (estimated_purge_tank_pressure_rate < estimated_purge_tank_pressure_rate_max)
		&& (purge_stft_corrector >= flash13e4_u16)) {
			purge_tank_pressure_rate += purge_tank_pressure_rate <= flash13de_u16 ? flash13ca_u16 : flash13dc_u16;
		}
		purge_tank_pressure_rate = MIN16(purge_tank_pressure_rate, flash13e0_u16/*143*/);
		decays_x4.purge_in_progress = flash13cc_u16;
	} else if ((128 >= purge_fp11570_u16) && (decays_x1.fp13798_u16 || (purge_flags & 0x01))) { //false with mt
		fp11568_decay = flash13c0_u16;
		fp11580_sum = 0;
		fp11560_f16 &= ~0x8000;
		fp11560_f16 &= ~0x2000;
		if (!decays_x1.fp13796_u16 && (update_flags_main & 0x01)) {
			purge_fp11570_u16 = MIN16(s_add16(purge_fp11570_u16, flash1622_u16), 128);
			purge_stft_corrector_prev = purge_fp11570_u16;
			purge_stft_corrector = purge_fp11570_u16;
			purge_stft_corrector_hires_smoothed = conv8to16(purge_stft_corrector) + 128;
		}
	} else {
		purge_stft_corrector_hires_smoothed = 0x8080;
		purge_stft_corrector_prev = 128;
		purge_stft_corrector = 128;
		purge_fp11570_u16 = 128;
		fp11568_decay = flash13c0_u16;
		fp11580_sum = 0;
		fp11560_f16 &= ~0x8000;
		fp11560_f16 &= ~0x2000;
	}
}

uint16_t get_purge_modified_stft(const struct cylinder_bank *ptr)
{
	if (purge_stft_corrector) {
		if (!purge_stft_corrector_prev) {
			l_stft = s_sub16(ps_mul_divu16(128, s_add16(128, s_divu16(*ptr->oxygen_feedback_trim, 256)), s_add16(128, purge_stft_corrector)), 128);
		} else {
			l_stft = s_sub16(ps_mul_divu16(s_add16(128, purge_stft_corrector_prev), s_add16(128, s_divu16(*ptr->oxygen_feedback_trim, 256)), s_add16(128, purge_stft_corrector)), 128);
		}
	} else {
		l_stft = s_sub16(ps_mul_divu16(s_add16(128, purge_stft_corrector_prev), s_add16(128, s_divu16(*ptr->oxygen_feedback_trim, 256)), 128), 128);
	}
	return mid16(s_mul16(l_stft, 256), *ptr->oxygen_trim_max, *ptr->oxygen_trim_min);
}

uint16_t calc_purge_duty()
{
	if ((mode_flags[3] & 0x2000) //disabled
	|| (mode_flags[4] & 0x0800)) {//disabled
		temp_axis_src = fuel_tank_pressure / 256;
		calc_axis(&flashc460_axis);
		fp11556_u16 = map8u16(&flash94b4_vs_fuel_tank_pressure_2dmap8);
	}

	if ((fp10418_f16 & 0xbb)
	|| (fp10144_f16 & 0x02)) {//disabled
		r5 = flash1ac4_u16 < maf_sensor_flow8 ? flash14b8_u16 : fp11556_u16;
	} else {
		r5 = purge_flags & 0x1000 ? flash148e_u16 : purge_tank_pressure_rate;
	}

	if (purge_open_rate) {
		l_duty_rate = ps_mul_divu16(s_mul16(r5, 2), purge_open_rate, 255);
		calculated_purge_duty = s_add16(ps_mul_divu16(s_sub16(purge_duty_max, purge_duty_min), l_duty_rate, 41), purge_duty_min);
		l_duty_smoothing = calculated_purge_duty < flash203a_u16 ? flash203e_u16 : flash203c_u16;
		if (update_flags_main & 0x08) {
			calculated_purge_duty_smoothed = aprxu16_256(calculated_purge_duty_smoothed, calculated_purge_duty, l_duty_smoothing);
		}
		l_duty = MIN16(calculated_purge_duty_smoothed, calculated_purge_duty);
	} else {
		l_duty = 0;
	}

	if ((mode_flags[3] & 0x2000) //disabled
	&& (fpp12532_f16 & 0x0300)
	&& (usdm_purge_flags & 0x30)) {
		if (fpp12532_f16 & 0x0100) {
			l_duty = ps_mul_divu16(flash14b4_u16, purge_open_rate, 255);
		} else {
			l_duty = ps_mul_divu16(flash14be_u16, purge_open_rate, 255);
		}
	}
	return r0;
}

void update_purge_open_rate()
{
	l_rate = purge_open_rate;/*r8*/

	r0 = 4;
	if ((mode_flags[3] & 0x2000) //disabled
	&& ((usdm_purge_flags & 0x30)
	|| (fp10144_f16 & 0x02))) {
		r0 = 8;
	}

	if ((run_state_flags & 0x08) //fuel cut
	|| !(closed_loop_flags & 0x80)) { //load < closed loop min
		l_force_purge_close = 1;/*r1*/
	} else {
		l_force_purge_close = 0;
		decays_x2.stft_multisourced_reset_in_fuel_cut_delay = flash10e2_u16;
	}

	if (!(fps_and_ac_support_flags & 0x40)) {
		if ((fps_and_ac_support_flags & 0x20)
		&& (usdm_purge_flags & 0x20)) {
			purge_open_rate = purge_open_rate_cond_prev;
			l_rate = purge_open_rate_cond_prev;
		}
		purge_open_rate_cond_prev = purge_open_rate;
	}

	if ((run_state_flags & 0x11)
	|| (fps_and_ac_support_flags & 0x40)) {
		l_rate = 0;
	} else if ((mode_flags[3] & 0x2000) //disabled
	&& (usdm_purge_flags & 0x20)
	&& (fpp12532_f16 & 0x0300)) {
		l_rate = 255;
	} else if (((mode_flags[3] & 0x2000) && (usdm_purge_flags & 0x10) && (fpp12532_f16 & 0x0300))
	|| (l_force_purge_close && !(fp10418_f16 & 0xbb))
	|| (fp10418_f16 & 0x03)
	|| (usdm_purge_flags & 0x10)
	|| (fp10144_f16 & 0x02)) {
		l_rate = 0;
	} else if (update_flags_main & 0x8000) {
		if (usdm_purge_flags & 0x30) {
			l_inc = flash1206_u16;/*r0*/
			l_dec = flash1204_u16;/*r1*/
		} else if (fp10144_f16 & 0x02) {
			l_inc = 0;
			l_dec = flash1204_u16;
		} else if (alt_inputs1_processed & 0x80) {
			l_inc = flash10d2_u16;
			l_dec = flash10d4_u16;
		} else {
			l_inc = flash1694_u16;
			l_dec = flash1696_u16;
		}
		if (!(usdm_purge_flags & 0x20) //not set
		&& ((usdm_purge_flags & 0x10) //not set
		|| (fp10144_f16 & 0x02) //not set
		|| ((purge_flags & 0xa0) && !(purge_flags & 0x40)))) {
			l_increase_rate = 0;
		} else {
			l_increase_rate = 1;
		}
		l_rate = l_increase_rate == 1 ? s_add16(l_rate, l_inc) : s_sub16(l_rate, l_dec);
	}
	purge_open_rate = MIN16(l_rate, 255);
}

uint16_t fault_safe_purge_duty(uint16_t p0)
{
	return sensor_faults & 0x08 ? (purge_flags & 0x40 ? flash_maf_fault_purge_duty : 0) : p0;
}

