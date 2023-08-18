void cvt_slip_detection()
{
	if (flash80038_u8) { //1
		cvt_axle_speed_sanity_check();
		cvt_wheel_speed_sanity_check();
		cvt_speeds_sanity_check_completion();
	} else {
		fpp952_f16 &= ~0x01;
	}
	if (fp1748_fstate & 0x03) {
		fpp716_high_acceleration_counter = 0;
		fpp924_age = 0;
	} else {
		l_ss_safe_bound_delta_smoothedd = ss_safe_bound_delta_smoothedd;/*sp14*/
		l_axle1_acceleration_smoothed = axle1_acceleration_smoothed;
		r10 = 0;
		sp18 = 0;
		fp212_secondary_pulley_torque = sh16_mul16_divu16(secondary_pulley_torque, 1000, flash8064a_u16);
		fp210_secondary_pulley_torque_plusc = s_add16(fp212_secondary_pulley_torque, flash80524_u16);
		l_fp210_secondary_pulley_torque_plusc = fp210_secondary_pulley_torque_plusc;/*sp16*/
		if (at_accel_avg < flash80528_u16) {
			S_INC_U16(fp554_low_apps_counter);
		} else {
			fp554_low_apps_counter = 0;
		}
		if (l_ss_safe_bound_delta_smoothedd < flash809a2_u16) { //0
			S_INC_U16(fp552_low_ss_delta_counter);
		} else {
			fp552_low_ss_delta_counter = 0;
		}
		if (fp2220_f16 & 0x04) {
			S_INC_U16(fp550_stop_switch_counter);
		} else {
			fp550_stop_switch_counter = 0;
		}
		if (l_ss_safe_bound_delta_smoothedd < flash80526_u16) {
			fpp716_high_acceleration_counter = 0;
			if (!(fp1746_f16 & 0x1000))
				ss_speed_preslip = secondary_speed_safe;
		} else {
			S_INC_U16(fpp716_high_acceleration_counter);
		}
		if (flash8003b_u8 == 2) {
			r8 = flash80038_u8 ? flash80b44_u16 : flash80b40_u16;
		} else {
			r8 = flash80038_u8 ? flash80b46_u16 : flash80b42_u16;
		}
		if ((fp1746_f16 & 0x1000)
		|| fpp716_high_acceleration_counter) {
			S_INC_U16(fpp846_u16);
			l_ss_slip_attenuated = ps_mul32_16_divu16(s_sub16(secondary_speed_safesecondary_speed_safe, ss_speed_preslip), 5000, fpp846_u16);
			ss_slip_diff = s_32to16(s_sub32(s_add32(l_ss_slip_attenuated, 0x8000), ss_slip_attenuated));
			ss_slip_diff_smoothed = aprxu16_256(ss_slip_diff_smoothed, ss_slip_diff, flash8099c_u16);
			fpp856_u32 = s_sub32(s_add32(fpp856_u32, fp212_secondary_pulley_torque), 0x8000);
			ret = ps_mul32_16_divu16(ABS_DIFF(fpp856_u32, 0x80000000), 588, 314);
			ret = ps_mul32_16_divu16(ret, flash80642_u16, flash80640_u16);
			r9 = ps16_divu32_16(ps32_scale_base128(ret, r8), 1000);
			if (0x80000000 < fpp856_u32) {
				fpp862_u16 = s_add16(fpp844_u16, r9);
			} else {
				fpp862_u16 = s_sub16(fpp844_u16, r9);
			}
		} else {
			fpp846_u16 = 0;
			ss_slip_diff = 0x8000;
			ss_slip_diff_smoothed = 0x8000;
			fpp856_u32 = 0x80000000;
			fpp862_u16 = 0;
		} ss_slip_attenuated = l_ss_slip_attenuated;
		ss_slip_attenuated16 = s_32to16(ss_slip_attenuated);
		if ((s_sh16abs(ss_slip_diff_smoothed) < flash809a0_u16) //100
		&& (secondary_speed_safe < fpp862_u16)) {
			S_INC_U16(fp556_ss_slip_low_age);
		} else {
			fp556_ss_slip_low_age = 0;
		}
		if ((cvt_axle_speed0 < s_add16(cvt_axle_speed1, flash80a16_u16))
		&& !(fp1746_f16 & 0x0800)) {
			S_INC_U16(fpp934_u16);
		} else {
			fpp934_u16 = 0;
		}
		if (cvt_axle_speed0 < s_add16(cvt_axle_speed1, flash80a16_u16)) {
			S_INC_U16(fpp1082_u16);
		} else {
			fpp1082_u16 = 0;
		}
		if (l_axle1_acceleration_smoothed < flash80526_u16) {
			fpp930_high_axle1_acceleration_upcounter = 0;
			if (!(fp1746_f16 & 0x0800))
				preslip_cvt_axle_speed1 = cvt_axle_speed1;
		} else {
			S_INC_U16(fpp930_high_axle1_acceleration_upcounter);
		}
		if ((fp1746_f16 & 0x0800)
		|| fpp930_high_axle1_acceleration_upcounter) {
			S_INC_U16(fpp924_age);
			l_axle_slip_attenuated = ps_mul_divu16(s_sub16(cvt_axle_speed1, cvt_axle_speed0), 50, fpp924_age);
			axle_slip_diff = s_sub16(s_add16(0x8000, l_axle_slip_attenuated), axle_slip_attenuated);
			axle_slip_diff_smoothed = aprxu16_256(axle_slip_diff_smoothed, axle_slip_diff, flash8099c_u16);
			fpp936_u32 = s_sub32(s_add32(fpp936_u32, fp212_secondary_pulley_torque), 0x8000);
			r8 = ps16_divu32_16(ps32_scale_base128(s_mul32(ABSDIFF(fpp936_u32, 0x8000), r8), 50000);
			if (0x8000 < fpp936_u32) {
				fpp948_u16 = s_add16(preslip_cvt_axle_speed1, r8);
			} else {
				fpp948_u16 = s_sub16(preslip_cvt_axle_speed1, r8);
			}
		} else {
			fpp924_age = 0;
		}
		axle_slip_attenuated = l_axle_slip_attenuated;
		fpp950_u16 = s_32to16(s32_divu32_16(ps_mul32_16_divu16(mul16(s_sh16abs(axle_slip_diff_smoothed), flash80642_u16), 1000, flash80640_u16), 376));
		if ((fpp950_u16 < flash809a0_u16) //100
		&& (cvt_axle_speed1 < fpp948_u16)) {
			S_INC_U16(fpp932_u16);
		} else {
			fpp932_u16 = 0;
		}
		if (!(fpp952_f16 & 0x01)) { fp1746_f16 &= ~0x0800; }
		else if ((fp1746_f16 & 0x1000)
		&& (fpp930_high_axle1_acceleration_upcounter >= flash8095a_u16)
		&& (l_axle1_acceleration_smoothed >= l_fp210_secondary_pulley_torque_plusc)) {
			fp1746_f16 |= 0x0800;
		}
		else if (!(fp1746_f16 & 0x1000)
		|| (fpp932_u16 >= flash8099e_u16)) {
			fp1746_f16 &= ~0x0800;
		}
		if (!fp554_low_apps_counter
		&& !fp550_stop_switch_counter
		&& !(fp1748_fstate & 0x30)
		&& !(atsen_faults & 0x4000)
		&& (at_ignition_age >= flash80ad0_u16)
		&& (((l_ss_safe_bound_delta_smoothedd >= l_fp210_secondary_pulley_torque_plusc)
		&& (fpp716_high_acceleration_counter >= flash8095a_u16))
		|| ((fpp952_f16 & 0x01)
		&& (cvt_axle_speed0 >= s_add16(s_add16(cvt_axle_speed1, flash80a14_u16), flash80a16_u16))
		&& (secondary_speed_safe >= flash80bb6_u16)))) {
			fp1746_f16 |= 0x1000;
		}
		else if (
		) {
			fp1746_f16 &= ~0x1000;
		}
	}
	if (0x80000000 < fpp856_u32) {
		fpp860_u16 = s_add16(0x8000, ps16_divu32_16(s_sub32(fpp856_u32, 0x80000000), 10));
	} else {
		fpp860_u16 = s_sub16(0x8000, s16_divu32_16(s_sub16(0x80000000, fpp856_u16), 10));
	}
	if (0x80000000 < fpp936_u32) {
		fpp940_u16 = s_add16(0x8000, ...);
	} else {
	}

}
