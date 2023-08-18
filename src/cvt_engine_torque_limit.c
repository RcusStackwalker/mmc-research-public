void update_at_engine_torque_limit()
{
	if (!(fp1460_f16 & 0x04)
	|| (flash80a20_u16 < secondary_speed_safe)
	|| (at_engine_rpm_avg < flash80a24_u16) //1.5krpm
	|| (at_accel_avg < flash80a28_u16) //40%
	|| (atf_temp_filtered < flash80a2c_u16)) { //-40deg
		fp1746_f16 &= ~0x80;
	} else if ((fp1460_f16 & 0x04)
	&& (flash80a1e_u16 >= secondary_speed_safe) //< 200
	&& (at_engine_rpm_avg >= flash80a22_u16) // > 2000
	&& (at_accel_avg >= flash80a26_u16) // > 80%
	&& (atf_temp_filtered >= flash80a2a_u16)) { //-40deg
		fp1746_f16 |= 0x80;
	}

	l_torque_to_tlp_multiplier_map = attos1_psend_torque >= 0x8000 ? &flash_positive_torque_to_tlp_multiplier_vs_atgear_ratio_2dmap16 : &flash_negative_torque_to_tlp_multiplier_vs_atgear_ratio_2dmap16;/*r10*/

	l_zero_map = tc_lock_processing_state == 4 ? &flash830a0_const0_vs_atgear_ratio_2dmap8 : &flash82fb0_const0_vs_atgear_ratio_2dmap8;/*r9*/

	r8 = fp1746_f16 & 0x80 ? flash80a2e_u16 : map8u16(l_zero_map);//34 : 0

	l_wot_takeoff_ps_torque_max = s_correct16(
		ps_mul_divu16(s_sub16(s_add16(line_pressure, flash80532_u16/*5*/), r8),
			256,
			mapu16(l_torque_to_tlp_multiplier_map)),
		at_pshaft_acceleration_torque_correction);/*sp22*/
	l_line_pressure_system_diag_primary_shaft_torque_max = s_correct16(
		ps_mul_divu16(s_sub16(s_add16(line_pressure, flash80532_u16), map8u16(l_zero_map)),
			256,
			mapu16(l_torque_to_tlp_multiplier_map)),
		at_pshaft_acceleration_torque_correction);/*sp20*/

	r8 = MAX16(s_sub16(s_add16(flash80b10_u16, flash80532_u16), map8u16(&flash83e84_vs_atgear_ratio_2dmap8)), flash80b16_u16/*0*/);
	l_maybe_pshaft_torque_max3 = s_correct16(ps_mul_divu16(r8, 256, mapu16(l_torque_to_tlp_multiplier_map)), at_pshaft_acceleration_torque_correction);/*r10*/
	call8df58();
	if (fp2176_u16 < flash80b60_u16) {
		r0 = flash80b64_u16;
		r1 = flash80b68_u16;
	} else {
		r0 = flash80b66_u16;
		r1 = flash80b6a_u16;
	}
	if (clutch_engagement_torque_limit_flags & 0x02) {
		clutch_engagement_torque_limit_addenum = s_add16(clutch_engagement_torque_limit_addenum, r0);
	} else if (clutch_engagement_torque_limit_flags & 0x04) {
		clutch_engagement_torque_limit_addenum = s_add16(clutch_engagement_torque_limit_addenum, r1);
	} else {
		clutch_engagement_torque_limit_addenum = 0;
	}
	l_maybe_pshaft_torque_max4 = s_correct16(s_add16(flash80b62_u16, ps_divu16(clutch_engagement_torque_limit_addenum, 10)),
		at_pshaft_acceleration_torque_correction);/*r9*/
	if (fp1748_fstate & 0x14) { //clutch slip
		/*?*/
	}

	wot_takeoff_ps_torque_max = l_wot_takeoff_ps_torque_max;
	l_torque_conversion_ratio_corrected = fp1746_f16 & 0x80
		? s_add16(tc_torque_conversion_ratio, flash80a30_u16)
		: tc_torque_conversion_ratio;/*r8*/

	fpp788_u16 = s_add16(s_add16(lp_torque_loss, fpp792_u16), s_divu16(fpp790_u16, 16));

	l_lp_torque_loss = flash80034_u8/*0*/ ? fpp788_u16 : lp_torque_loss;/*sp18*/

	wot_takeoff_engine_torque_max = s_correct16(
		s_add16(ps_mul_divu16(wot_takeoff_ps_torque_max, 128, l_torque_conversion_ratio_corrected), l_lp_torque_loss),
		at_crankshaft_acceleration_torque_correction);

	line_pressure_system_diag_engine_torque_max = s_correct16(
		s_add16(ps_mul_divu16(l_line_pressure_system_diag_primary_shaft_torque_max, 128, tc_torque_conversion_ratio),
			lp_torque_loss),
		at_crankshaft_acceleration_torque_correction);

	maybe_cshaft_torque_max3 = s_correct16(
		s_add16(ps_mul_divu16(l_maybe_pshaft_torque_max3, 128, l_torque_conversion_ratio_corrected), l_lp_torque_loss),
		at_crankshaft_acceleration_torque_correction);

	clutch_engagement_engine_torque_max = s_correct16(
		s_add16(ps_mul_divu16(l_maybe_pshaft_torque_max4, 128, l_torque_conversion_ratio_corrected), l_lp_torque_loss),
		at_crankshaft_acceleration_torque_correction)

	at_update_fuel_cut_limp();
	if (fp1748_fstate & 0x14) { //clutch slip
		calc_axis(&flash81976_at_engine_rpm_avg_axis);
		r10 = map8u16(&flash83812_torque_max_vs_rpm_2dmap8);
		l_torque_limit = s_add16(s_add16(ps_mul_divu16(l_lp_torque_loss, 4096, flash8011e_u16), r10), flash_engine_torque_neutral_point);
		l_at_engine_torque_limit_state = 0x20;
	} else if (fp1746_f16 & 0x80) { //wot takeoff
		l_torque_limit = s_add16(ps_mul_divu16(wot_takeoff_engine_torque_max, 4096, flash8011e_u16), flash_engine_torque_neutral_point);
		l_at_engine_torque_limit_state = 0x10;
	} else if ((flash80016_u8/*0*/ || flash80034_u8/*0*/) && (fpp114_f16 & 0x01)) {
		l_torque_limit = s_add16(map8u16(&flash83350_2dmap8), 128);
		l_at_engine_torque_limit_state = 0x04;
	} else if ((flash80016_u8/*0*/ || flash80034_u8/*0*/) && (fpp114_f16 & 0x02)) {
		l_torque_limit = flash8077e_u16;
		l_at_engine_torque_limit_state = 0x08;
	} else {
		l_torque_limit = flash805f6_u16;//0x190
		l_at_engine_torque_limit_state = 1;
	}

	if (at_dtc_flags3 & 0x01) {
		l_torque_limit = MIN16(l_torque_limit, flash80a1c_u16);
	}
	if (!(flash80040_f16) //false
	&& (fp1396_f16 & 0x0100)
	) {
	}
	if (!(flash80040_f16 & 0x8000) //false
	&& (fpp230_f16 & 0x40)) {
	}
	if (flash8003a_u8/*1*/ && (fp2220_f16 & 0x04)) { //stop lamp
		r10 = ps_mul_divu16(flash80a9e_u16, 128, ps_torque_conversion_ratio);
		if (fp1748_fstate & 0x14) {
			r10 = ps_mul_divu16(r10, 256, flash80116_u16);
		}
		stop_torque_limit = s_add16(ps_mul_divu16(s_add16(r10, l_lp_torque_loss), 4096, flash8011e_u16),
			flash_engine_torque_neutral_point);
		l_torque_limit = MIN(l_torque_limit, stop_torque_limit);
	} else {
		stop_torque_limit = 0xffff;
	}
	if (clutch_engagement_torque_limit_flags & 0x07) {
		ret = s_add16(ps_mul_divu16(clutch_engagement_engine_torque_max, 4096, flash8011e_u16), flash_engine_torque_neutral_point);
		l_torque_limit = MIN16(l_torque_limit, ret);
	}
	at_engine_torque_limit_state = l_at_engine_torque_limit_state;
	at_current_engine_torque_limit = l_torque_limit;
	at_engine_torque_limit = aprxu16_256(at_engine_torque_limit, at_current_engine_torque_limit, flash80446_u16);
	fp450_u16 = at_engine_torque_limit;
}

