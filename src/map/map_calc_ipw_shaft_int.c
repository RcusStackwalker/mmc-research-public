#include <stdint.h>
#include <fmath.h>
#include <run_state_flags.h>
#include "main_map_calcs.h"
#include <defs.h>
#include "ipw_int_components.h"

#define CAMSHAFT_SYNC_FLAGS_ACTIVE_SYNC	0x02
#define CAMSHAFT_SYNC_FLAGS_TRIED_SYNC	0x04

#define CYLINDER_COUNT 4

#define INJECTION_MODE_DISABLED		0
#define INJECTION_MODE_NORMAL		1
#define INJECTION_MODE_MONO		2
#define INJECTION_MODE_ALL		3

extern void injectors_fault_detection();
extern uint16_t get_ipw_fuel_film_compensated(uint16_t p0);

extern uint16_t afr_correction_flags;
extern uint16_t camshaft_sync_flags;
extern uint16_t purge_fuel_trim;
extern uint16_t aftercranking_enrichment;
extern uint16_t coolant_temp_prestart;

extern uint16_t fault_recheck_request_flags;
extern uint16_t shaft_int_temp_axis_src;

extern uint16_t trust_limp_fuel_cut_flags;
extern uint16_t cylinder_active2;
extern uint16_t winter_start_decay;

extern const uint16_t flash_cylinder_direct_mask[5];


extern uint16_t map_delayed1;
extern uint16_t map_delayed2;
extern uint16_t map_delayed3;
extern uint16_t map_delayed4;
extern uint16_t tps_based_failsafe_map8;


extern const void *const flash_map_avg_axis;
extern const void *const flash_map_limits_load_3dmap16;


extern uint16_t shaft_period1_short_copy_dline0;
extern const uint16_t flash_revolution_period_limit;
extern uint16_t run_state_extended_flags;

#if 0
static void update_overrev_state()
{
	/*if mivec off rpm limit should be lower*/
	if (shaft_period1_short_copy_dline0 < flash_revolution_period_limit) {
		run_state_extended_flags |= RUN_STATE_EXTENDED_FLAGS_OVERREV;
	} else {
		run_state_extended_flags &= ~RUN_STATE_EXTENDED_FLAGS_OVERREV;
	}
}


extern uint16_t max_load_source_value_delta_positive;
extern uint16_t max_load_source_value_delta_negative;

#define MAX(x,y) ((x) < (y) ? (y) : (x))

static void sharpen_load()
{
	uint_fast16_t l_sharp_load;
#if 0
	if (map_delayed1 <= map_avg16) {
		l_sharp_load = s_add16(map_avg16, s_mul_divu16((map_avg16 - map_delayed1) * 256, flash2542_u16, 32));
	} else {
		l_sharp_load = s_sub16(map_avg16, s_mul_divu16((map_delayed1 - map_avg16) * 256, flash2544_u16, 32));
	}
#else
	l_sharp_load = map_avg16;
#endif
	fiload_sharp = l_sharp_load;

	if (map_avg16 >= map_delayed4) {
		max_load_source_value_delta_positive = MAX(max_load_source_value_delta_positive, map_avg16 - map_delayed4);
	} else {
		max_load_source_value_delta_negative = MAX(max_load_source_value_delta_negative, map_delayed4 - map_avg16);
	}
}

extern uint16_t ipw_addition_rate;
extern uint16_t ipw_subtraction_rate;
extern uint16_t ipw_addition;
extern uint16_t ipw_subtraction;

static void update_ipw_addition_subtraction()
{

#if 0
	unsigned l_flag = 1;
	if (ipw_addition_rate) {
		if (flash1672_u16 < ipw_addition_rate) {
			ipw_addition_rate = MAX16(flash1672_u16, s_scale_base256(ipw_addition_rate, ipw_addition_rate_coolant_decay_rate));
		} else if (!ram6c1c_u16) {
			ipw_addition_rate = s_scale_base256(ipw_addition_rate, flash1674_u16);//0xf8
		} else {
			l_flag = 0;
		}
	}
	if (l_flag
	&& (flash167a_u16 >= coolant_temp_filtered)) {
		ram6c1c_u16 = flash1678_u16;
	}

	S_DEC(ram6c1c_u16);
	S_DEC(ram6c20_u16);

	l_flag = 1;

	if (ipw_subtraction_rate) {
		if (flash168c_u16 <= ipw_subtraction_rate) {
			//TODO
		} else if (!ram6c1e_u16) {
			//TODO
		} else {
			l_flag = 0;
		}
	}

	if (l_flag
	&& (flash1690_u16 >= coolant_temp_filtered)) {
		ram6c1e_u16 = flash1692_u16;
	}
	S_DEC(ram6c1e_u16);

	if ((run_state_extended_flags & 0x13)
	|| (flash1664_u16 >= ram6618_u16)) {
		ipw_addition_rate = 0;
	} else if (!get_ig1()
	|| (run_state_extended_flags & 0x28)
	|| (afr_correction_flags & 0x40)) {
		//based on colt
		ipw_addition_rate = 0;
		if ((run_state_extended_flags & 0x28)
		|| (afr_correction_flags & 0x40))
			ipw_subtraction_rate = 0;
	} else {
		if (load_source_value >= load_source_value_prev) {
			if (ipw_safe_addition_decay) {
			}
		} else if (load_source_value < load_source_value_prev) {
		}

		if (ELABORATE_APPS_NEUTRAL)
			ipw_addition_rate = 0;
		if (decays_x1_aftercranking_ipw_subtraction_restrict)
			ipw_subtraction_rate = 0;
	}

	ipw_addition = ipw_addition_rate ? s_32to16(s_mul32_16_divu16(ipw_addition_base, ipw_addition_rate, 2048)) : 0;
	ipw_subtraction = ipw_subtraction_rate ? s_mul_divu16(ipw_subtraction_rate, ipw_subtraction_base, 2048) : 0;
#endif
	ipw_addition_rate = 0;
	ipw_subtraction_rate = 0;
	ipw_addition = 0;
	ipw_subtraction = 0;
}

extern uint16_t get_ig1();

extern uint16_t ffilm3_approximated_dline[7];
extern uint16_t ffilm4_approximated_dline[7];

static void load_up_fuel_film(uint16_t p0)
{
	ffilm3_approximated_dline[6] = p0;
	ffilm3_approximated_dline[5] = p0;
	ffilm3_approximated_dline[4] = p0;
	ffilm3_approximated_dline[3] = p0;
	ffilm3_approximated_dline[2] = p0;
	ffilm3_approximated_dline[1] = p0;
	ffilm3_approximated_dline[0] = p0;
	ffilm4_approximated_dline[6] = p0;
	ffilm4_approximated_dline[5] = p0;
	ffilm4_approximated_dline[4] = p0;
	ffilm4_approximated_dline[3] = p0;
	ffilm4_approximated_dline[2] = p0;
	ffilm4_approximated_dline[1] = p0;
	ffilm4_approximated_dline[0] = p0;
}

static void reset_fuel_film()
{
	load_up_fuel_film(0);
}

void calc_ipw_shaft_int(uint16_t p0, uint16_t p1)
{
	uint16_t l_check_injectors = 0;
	uint8_t l_injection_mode;
	uint16_t l_ipw;

	if (p0 == 1)
		goto skip_calculations;

	update_overrev_state();
	update_load_source_value_from_map_samples();
	update_fiload();
	update_ipw_addition_subtraction();

	map_delayed4 = map_delayed3;
	map_delayed3 = map_delayed2;
	map_delayed2 = map_delayed1;
	map_delayed1 = master_load;

	if (!get_ig1()
	|| (trust_limp_fuel_cut_flags & 0x01)
	|| (run_state_extended_flags & 0x38)) {
		l_ipw = 0;//
		if (((run_state_extended_flags & 0x28) | (trust_limp_fuel_cut_flags & 0x01))
		&& ((flash_ffilm3_min_during_fuel_cut >= ffilm3_approximated_dline[0]) | (flash_ffilm4_min_during_fuel_cut >= ffilm4_approximated_dline[0]))) {
			reset_fuel_film();
		} else {
			get_ipw_fuel_film_compensated(0);
		}
	} else if ((run_state_extended_flags & 0x28)
	&& !(run_state_extended_flags & 0x1000)) {
		l_ipw = 0;
		reset_fuel_film();
	} else if ((run_state_extended_flags & 0x01)
	|| (fault_recheck_request_flags & 0x10)
	|| (run_state_extended_flags & 0x03)) {
		l_ipw = cranking_or_load_sensor_fault_ipw_int;
		load_up_fuel_film(l_ipw);
		shaft_int_temp_axis_src = coolant_temp_prestart;
		calc_axis(&flash_fuel_film_coolant_axis);
		decays_x2_init10_instant_ipw_use_decay1 = map8u16(&flash_instant_ipw_use_decay_vs_coolant_prestart_2dmap8);
		decays_x2_fuel_film_negative_compensation_unusable = map8u16(&flash_fuel_film_negative_compensation_unusable_vs_coolant_prestart_2dmap8);
	} else {
		uint_fast16_t l_nom_ipw_trimmed = s_mul_divu16(nominal_load_ipw_int, conv16to8(oxygen_feedback_trim) * 2 + o2_offset_trim_int + long_term_fuel_trim_int, 512);
		uint_fast16_t ret = s_mul_divu16(l_nom_ipw_trimmed, fiload_sharp, 2048);
		ret = s_mul32_16_divu16(ret, 128, aftercranking_enrichment * 2 + 128);
		ret = get_ipw_fuel_film_compensated(s_mul32_16_divu16(ret, 256, purge_fuel_trim + 128));
		ret = s32_scale_base128(ret, aftercranking_enrichment * 2 + 128);
		l_ipw = s32_scale_base256(ret, purge_fuel_trim + 128);
		if (ipw_addition)
			l_ipw = s_add16(l_ipw, ipw_addition);
		if (ipw_subtraction) {
			l_ipw = s_sub16(l_ipw, ipw_subtraction);
			l_ipw = MAX(l_ipw, 1);
		}
	}
	if (run_state_extended_flags & RUN_STATE_EXTENDED_FLAGS_WINTER_CRANKING) {
		l_injection_mode = INJECTION_MODE_ALL;
		l_ipw = start_pulse_ipw_int;
		S_DEC(winter_start_decay);
		if (!winter_start_decay) {
			run_state_extended_flags &= ~RUN_STATE_EXTENDED_FLAGS_WINTER_CRANKING;
		}
	} else if ((afr_correction_flags & 0x80) //never true
	&& (run_state_extended_flags & RUN_STATE_FLAGS_CRANKING)
	&& (hot_cranking_injection_restriction_decay || !(camshaft_sync_flags & CAMSHAFT_SYNC_FLAGS_ACTIVE_SYNC))) {
		l_injection_mode = INJECTION_MODE_DISABLED;
	} else if (run_state_extended_flags & RUN_STATE_EXTENDED_FLAGS_CRANKING_RELATED) {
		l_injection_mode = INJECTION_MODE_MONO;
	} else if (!(camshaft_sync_flags & CAMSHAFT_SYNC_FLAGS_ACTIVE_SYNC)
	&& !(camshaft_sync_flags & (CAMSHAFT_SYNC_FLAGS_ACTIVE_SYNC | CAMSHAFT_SYNC_FLAGS_TRIED_SYNC))) {
		l_injection_mode = INJECTION_MODE_MONO;
		l_ipw = s_divu16(l_ipw, CYLINDER_COUNT);
	} else {
		l_injection_mode = INJECTION_MODE_NORMAL;
	}
	ipw_calculated = l_ipw;
	goto injection;
	
skip_calculations:
	if ((afr_correction_flags & 0x80)
	&& (run_state_extended_flags & 0x01)
	&& !hot_cranking_injection_restriction_decay
	&& !(camshaft_sync_flags & 0x02)) {
		l_injection_mode = 0;
	} else {
		l_injection_mode = 2;
	}
	l_ipw = ipw_calculated;

injection:

#if 0
	if (r9 && r10) {
		l_ipw = mid16(get_injector_duty_latency_compensated(r10), 65240, flash_injector_min_ulse_zero_at_rpm < engine_rpm_8kmax ? 0 : flash_injector_min_pulse_width * 32);
		mut_ipw = /**/l_ipw;
		uint16_t l_mask;

		switch (r9) {
		case 1:
			if () {
				l_mask = ...;
			} else if (..) {
				l_mask = cylindermask_from_index(cylinder_active2 + 1);
				...
			} else {
				l_mask = flash_cylinder_direct_mask[cylinder_active2 + 1]
				if ()
					l_mask |= flash_cylinder_direct_mask[cylinder_active2];
			}
			break;
		case 3:
			if () {
			}
			l_mask = 0x0f;
			...
			break;
		default:
			l_mask = 0x0f;
			if ()
			...
		}
		if (() && !p0) {
			deferred_injectors_update_duty_extra(l_ipw, mask);
		} else {
			injectors_update_duty_extra(l_ipw, mask);
			l_check_injectors = 1;
		}
		//ipw_sum_int = ...;
	} else {
		//..
	}
#endif
	if (l_check_injectors)
		injectors_fault_detection();
//   263b2:	d0 53       	mov.l	0x26500,r0	! ffff6b4e	#-
//   263b4:	60 01       	mov.w	@r0,r0				#-
//   263b6:	c8 80       	tst	#-128,r0			#-
//   263b8:	89 0e       	bt	0x263d8				#-
//   263ba:	d0 52       	mov.l	0x26504,r0	! ffff6b4a	#-
//   263bc:	60 01       	mov.w	@r0,r0				#-
//   263be:	c8 01       	tst	#1,r0				#-
//   263c0:	89 0a       	bt	0x263d8				#-
//   263c2:	da 51       	mov.l	0x26508,r10	! ffff6bc6	#-
//   263c4:	6a a1       	mov.w	@r10,r10			#-
//   263c6:	2a a8       	tst	r10,r10				#-
//   263c8:	8b 03       	bf	0x263d2				#-
//   263ca:	d0 50       	mov.l	0x2650c,r0	! ffff701a	#-
//   263cc:	60 01       	mov.w	@r0,r0				#-
//   263ce:	c8 02       	tst	#2,r0				#-
//   263d0:	8b 02       	bf	0x263d8				#-
//   263d2:	e2 00       	mov	#0,r2				#-
//   263d4:	a0 01       	bra	0x263da				#-
//   263d6:	00 09       	nop					#-
//   263d8:	e2 02       	mov	#2,r2				#-
//   263da:	d8 4d       	mov.l	0x26510,r8	! ffff6b3e	#-
//   263dc:	68 81       	mov.w	@r8,r8				#-
//   263de:	62 2c       	extu.b	r2,r2				#-
//   263e0:	22 28       	tst	r2,r2				#-
//   263e2:	8b 01       	bf	0x263e8				#-
//   263e4:	a1 31       	bra	0x2664a				#-
//   263e6:	00 09       	nop					#-
//   263e8:	68 8d       	extu.w	r8,r8				#-
//   263ea:	28 88       	tst	r8,r8				#-
//   263ec:	8b 01       	bf	0x263f2				#-
//   263ee:	a1 2c       	bra	0x2664a				#-
//   263f0:	00 09       	nop					#-
//   263f2:	e9 00       	mov	#0,r9				#-
//   263f4:	da 48       	mov.l	0x26518,r10	! ffff6a34	#-
//   263f6:	6a a1       	mov.w	@r10,r10			#-
//   263f8:	db 46       	mov.l	0x26514,r11	! 1508		#-
//   263fa:	6b b1       	mov.w	@r11,r11			#-
//   263fc:	3a b6       	cmp/hi	r11,r10				#-
//   263fe:	89 04       	bt	0x2640a				#-
//   26400:	d9 46       	mov.l	0x2651c,r9	! 1504		#-
//   26402:	69 91       	mov.w	@r9,r9				#-
//   26404:	49 08       	shll2	r9				#-
//   26406:	49 08       	shll2	r9				#-
//   26408:	49 00       	shll	r9				#-
//   2640a:	69 9d       	extu.w	r9,r9				# r9 = flash_injector_min_pulse_zero_at_rpm < engine_rpm_8kmax ? 0 : flash_injector_min_pulse_width * 32;
//   2640c:	64 8d       	extu.w	r8,r4				#-
//   2640e:	b1 97       	bsr	0x26740				#-
//   26410:	00 09       	nop					#-
//   26412:	64 0d       	extu.w	r0,r4				#-
//   26414:	d5 47       	mov.l	0x26534,r5	! fde8		#-
//   26416:	66 93       	mov	r9,r6				#-
//   26418:	da 45       	mov.l	0x26530,r10	! 5a8		#-
//   2641a:	4a 0b       	jsr	@r10				#-
//   2641c:	00 09       	nop					#-
//   2641e:	68 03       	mov	r0,r8				# r8 = mid16(get_injector_duty_latency_compensated(r8), 65000, r9);
//   26420:	da 42       	mov.l	0x2652c,r10	! ffff6b44	#-
//   26422:	2a 01       	mov.w	r0,@r10				# ram6b44_u16 = r8;
//   26424:	da 40       	mov.l	0x26528,r10	! ffff6b40	#-
//   26426:	2a 01       	mov.w	r0,@r10				# ram6b40_u16 = 0;
//   26428:	64 0d       	extu.w	r0,r4				#-
//   2642a:	e5 08       	mov	#8,r5				#-
//   2642c:	da 44       	mov.l	0x26540,r10	! ed8		#-
//   2642e:	4a 0b       	jsr	@r10				#-
//   26430:	00 09       	nop					#-
//   26432:	db 3c       	mov.l	0x26524,r11	! ffff7a84	#-
//   26434:	2b 01       	mov.w	r0,@r11				#-
//   26436:	d0 3a       	mov.l	0x26520,r0	! ffff6ac8	#-
//   26438:	60 01       	mov.w	@r0,r0				#-
//   2643a:	c8 04       	tst	#4,r0				#-
//   2643c:	89 0b       	bt	0x26456				#-
//   2643e:	d0 3e       	mov.l	0x26538,r0	! ffff738a	#-
//   26440:	60 01       	mov.w	@r0,r0				#-
//   26442:	88 06       	cmp/eq	#6,r0				#-
//   26444:	89 03       	bt	0x2644e				#-
//   26446:	d0 3c       	mov.l	0x26538,r0	! ffff738a	#-
//   26448:	60 01       	mov.w	@r0,r0				#-
//   2644a:	88 09       	cmp/eq	#9,r0				#-
//   2644c:	8b 03       	bf	0x26456				#-
//   2644e:	da 3a       	mov.l	0x26538,r10	! ffff738a	#-
//   26450:	60 a1       	mov.w	@r10,r0				#-
//   26452:	70 01       	add	#1,r0				#-
//   26454:	2a 01       	mov.w	r0,@r10				#-
//   26456:	da 3b       	mov.l	0x26544,r10	! ffff6b42	#-
//   26458:	2a 81       	mov.w	r8,@r10				#-
//   2645a:	64 8d       	extu.w	r8,r4				#-
//   2645c:	e5 08       	mov	#8,r5				#-
//   2645e:	da 38       	mov.l	0x26540,r10	! ed8		#-
//   26460:	4a 0b       	jsr	@r10				#-
//   26462:	00 09       	nop					#-
//   26464:	db 35       	mov.l	0x2653c,r11	! ffff7a86	#-
//   26466:	2b 01       	mov.w	r0,@r11				#-
//   26468:	60 2c       	extu.b	r2,r0				#-
//   2646a:	88 01       	cmp/eq	#1,r0				#-
//   2646c:	89 01       	bt	0x26472				#-
//   2646e:	a0 8d       	bra	0x2658c				#-
//   26470:	00 09       	nop					#-
//   26472:	d0 80       	mov.l	0x26674,r0	! ffff6c3e	#-
//   26474:	60 01       	mov.w	@r0,r0				#-
//   26476:	c8 80       	tst	#-128,r0			#-
//   26478:	8b 01       	bf	0x2647e				#-
//   2647a:	a0 73       	bra	0x26564				#-
//   2647c:	00 09       	nop					#-
//   2647e:	d0 7d       	mov.l	0x26674,r0	! ffff6c3e	#-
//   26480:	60 01       	mov.w	@r0,r0				#-
//   26482:	c8 40       	tst	#64,r0				#-
//   26484:	89 02       	bt	0x2648c				#-
//   26486:	e2 00       	mov	#0,r2				#-
//   26488:	a0 a2       	bra	0x265d0				#-
//   2648a:	00 09       	nop					#-
//   2648c:	ed 03       	mov	#3,r13				#-
//   2648e:	da 7b       	mov.l	0x2667c,r10	! ffff7014	#-
//   26490:	6a a1       	mov.w	@r10,r10			#-
//   26492:	2a a8       	tst	r10,r10				#-
//   26494:	89 07       	bt	0x264a6				#-
//   26496:	d4 79       	mov.l	0x2667c,r4	! ffff7014	#-
//   26498:	64 41       	mov.w	@r4,r4				#-
//   2649a:	64 4d       	extu.w	r4,r4				#-
//   2649c:	e5 01       	mov	#1,r5				#-
//   2649e:	da 2a       	mov.l	0x26548,r10	! f0c		#-
//   264a0:	4a 0b       	jsr	@r10				#-
//   264a2:	00 09       	nop					#-
//   264a4:	6d 0d       	extu.w	r0,r13				#-
//   264a6:	d0 29       	mov.l	0x2654c,r0	! ffff6ae4	#-
//   264a8:	60 01       	mov.w	@r0,r0				#-
//   264aa:	c8 01       	tst	#1,r0				#-
//   264ac:	89 52       	bt	0x26554				#-
//   264ae:	d0 28       	mov.l	0x26550,r0	! ffff6b38	#-
//   264b0:	60 01       	mov.w	@r0,r0				#-
//   264b2:	c8 80       	tst	#-128,r0			#-
//   264b4:	89 4e       	bt	0x26554				#-
//   264b6:	d0 6f       	mov.l	0x26674,r0	! ffff6c3e	#-
//   264b8:	60 01       	mov.w	@r0,r0				#-
//   264ba:	c8 20       	tst	#32,r0				#-
//   264bc:	8b 4a       	bf	0x26554				#-
//   264be:	d0 6c       	mov.l	0x26670,r0	! ffff6ae2	#-
//   264c0:	60 01       	mov.w	@r0,r0				#-
//   264c2:	40 19       	shlr8	r0				#-
//   264c4:	c8 04       	tst	#4,r0				#-
//   264c6:	8b 45       	bf	0x26554				#-
//   264c8:	d0 69       	mov.l	0x26670,r0	! ffff6ae2	#-
//   264ca:	60 01       	mov.w	@r0,r0				#-
//   264cc:	40 19       	shlr8	r0				#-
//   264ce:	c8 08       	tst	#8,r0				#-
//   264d0:	8b 40       	bf	0x26554				#-
//   264d2:	da 67       	mov.l	0x26670,r10	! ffff6ae2	#-
//   264d4:	60 a1       	mov.w	@r10,r0				#-
//   264d6:	9b 07       	mov.w	0x264e8,r11	! 800		#-
//   264d8:	20 bb       	or	r11,r0				#-
//   264da:	2a 01       	mov.w	r0,@r10				#-
//   264dc:	6d dd       	extu.w	r13,r13				#-
//   264de:	4d 00       	shll	r13				#-
//   264e0:	d0 65       	mov.l	0x26678,r0	! 9a54		#-
//   264e2:	02 dd       	mov.w	@(r0,r13),r2			#-
//   264e4:	a0 74       	bra	0x265d0				#-
//   264e6:	00 09       	nop					#-
//   264e8:	08 00       	.word 0x0800				#-
//   264ea:	ff ff       	.word 0xffff				#-
//   264ec:	ff ff       	.word 0xffff				#-
//   264ee:	70 20       	add	#32,r0				#-
//   264f0:	ff ff       	.word 0xffff				#-
//   264f2:	6c 9e       	exts.b	r9,r12				#-
//   264f4:	ff ff       	.word 0xffff				#-
//   264f6:	6c 9a       	negc	r9,r12				#-
//   264f8:	00 00       	.word 0x0000				#-
//   264fa:	df ff       	mov.l	0x268f8,r15	! d0066001	#-
//   264fc:	00 00       	.word 0x0000				#-
//   264fe:	08 c4       	mov.b	r12,@(r0,r8)			#-
//   26500:	ff ff       	.word 0xffff				#-
//   26502:	6b 4e       	exts.b	r4,r11				#-
//   26504:	ff ff       	.word 0xffff				#-
//   26506:	6b 4a       	negc	r4,r11				#-
//   26508:	ff ff       	.word 0xffff				#-
//   2650a:	6b c6       	mov.l	@r12+,r11			#-
//   2650c:	ff ff       	.word 0xffff				#-
//   2650e:	70 1a       	add	#26,r0				#-
//   26510:	ff ff       	.word 0xffff				#-
//   26512:	6b 3e       	exts.b	r3,r11				#-
//   26514:	00 00       	.word 0x0000				#-
//   26516:	15 08       	mov.l	r0,@(32,r5)			#-
//   26518:	ff ff       	.word 0xffff				#-
//   2651a:	6a 34       	mov.b	@r3+,r10			#-
//   2651c:	00 00       	.word 0x0000				#-
//   2651e:	15 04       	mov.l	r0,@(16,r5)			#-
//   26520:	ff ff       	.word 0xffff				#-
//   26522:	6a c8       	swap.b	r12,r10				#-
//   26524:	ff ff       	.word 0xffff				#-
//   26526:	7a 84       	add	#-124,r10			#-
//   26528:	ff ff       	.word 0xffff				#-
//   2652a:	6b 40       	mov.b	@r4,r11				#-
//   2652c:	ff ff       	.word 0xffff				#-
//   2652e:	6b 44       	mov.b	@r4+,r11			#-
//   26530:	00 00       	.word 0x0000				#-
//   26532:	05 a8       	.word 0x05a8				#-
//   26534:	00 00       	.word 0x0000				#-
//   26536:	fd e8       	.word 0xfde8				#-
//   26538:	ff ff       	.word 0xffff				#-
//   2653a:	73 8a       	add	#-118,r3			#-
//   2653c:	ff ff       	.word 0xffff				#-
//   2653e:	7a 86       	add	#-122,r10			#-
//   26540:	00 00       	.word 0x0000				#-
//   26542:	0e d8       	.word 0x0ed8				#-
//   26544:	ff ff       	.word 0xffff				#-
//   26546:	6b 42       	mov.l	@r4,r11				#-
//   26548:	00 00       	.word 0x0000				#-
//   2654a:	0f 0c       	mov.b	@(r0,r0),r15			#-
//   2654c:	ff ff       	.word 0xffff				#-
//   2654e:	6a e4       	mov.b	@r14+,r10			#-
//   26550:	ff ff       	.word 0xffff				#-
//   26552:	6b 38       	swap.b	r3,r11				#-
//   26554:	da 49       	mov.l	0x2667c,r10	! ffff7014	#-
//   26556:	6a a1       	mov.w	@r10,r10			#-
//   26558:	6a ad       	extu.w	r10,r10				#-
//   2655a:	4a 00       	shll	r10				#-
//   2655c:	d0 46       	mov.l	0x26678,r0	! 9a54		#-
//   2655e:	02 ad       	mov.w	@(r0,r10),r2			#-
//   26560:	a0 36       	bra	0x265d0				#-
//   26562:	00 09       	nop					#-
//   26564:	da 45       	mov.l	0x2667c,r10	! ffff7014	#-
//   26566:	6a a1       	mov.w	@r10,r10			#-
//   26568:	6a ad       	extu.w	r10,r10				#-
//   2656a:	4a 00       	shll	r10				#-
//   2656c:	7a 02       	add	#2,r10				#-
//   2656e:	d0 42       	mov.l	0x26678,r0	! 9a54		#-
//   26570:	02 ad       	mov.w	@(r0,r10),r2			#-
//   26572:	d0 40       	mov.l	0x26674,r0	! ffff6c3e	#-
//   26574:	60 01       	mov.w	@r0,r0				#-
//   26576:	c8 40       	tst	#64,r0				#-
//   26578:	89 2a       	bt	0x265d0				#-
//   2657a:	da 40       	mov.l	0x2667c,r10	! ffff7014	#-
//   2657c:	6a a1       	mov.w	@r10,r10			#-
//   2657e:	6a ad       	extu.w	r10,r10				#-
//   26580:	4a 00       	shll	r10				#-
//   26582:	d0 3d       	mov.l	0x26678,r0	! 9a54		#-
//   26584:	0b ad       	mov.w	@(r0,r10),r11			#-
//   26586:	22 bb       	or	r11,r2				#-
//   26588:	a0 22       	bra	0x265d0				#-
//   2658a:	00 09       	nop					#-
//   2658c:	60 2c       	extu.b	r2,r0				#-
//   2658e:	88 03       	cmp/eq	#3,r0				#-
//   26590:	8b 1d       	bf	0x265ce				#-
//   26592:	d0 3b       	mov.l	0x26680,r0	! ffff6afe	#-
//   26594:	60 01       	mov.w	@r0,r0				#-
//   26596:	c8 40       	tst	#64,r0				#-
//   26598:	8b 0d       	bf	0x265b6				#-
//   2659a:	d0 35       	mov.l	0x26670,r0	! ffff6ae2	#-
//   2659c:	60 01       	mov.w	@r0,r0				#-
//   2659e:	40 19       	shlr8	r0				#-
//   265a0:	c8 04       	tst	#4,r0				#-
//   265a2:	8b 08       	bf	0x265b6				#-
//   265a4:	da 32       	mov.l	0x26670,r10	! ffff6ae2	#-
//   265a6:	60 a1       	mov.w	@r10,r0				#-
//   265a8:	9b 60       	mov.w	0x2666c,r11	! 400		#-
//   265aa:	20 bb       	or	r11,r0				#-
//   265ac:	2a 01       	mov.w	r0,@r10				#-
//   265ae:	da 9d       	mov.l	0x26824,r10	! ffff7018	#-
//   265b0:	60 a1       	mov.w	@r10,r0				#-
//   265b2:	ca 01       	xor	#1,r0				#-
//   265b4:	2a 01       	mov.w	r0,@r10				#-
//   265b6:	da 9b       	mov.l	0x26824,r10	! ffff7018	#-
//   265b8:	6a a1       	mov.w	@r10,r10			#-
//   265ba:	6a ad       	extu.w	r10,r10				#-
//   265bc:	4a 00       	shll	r10				#-
//   265be:	d0 98       	mov.l	0x26820,r0	! 9a66		#-
//   265c0:	02 ad       	mov.w	@(r0,r10),r2			#-
//   265c2:	da 98       	mov.l	0x26824,r10	! ffff7018	#-
//   265c4:	60 a1       	mov.w	@r10,r0				#-
//   265c6:	ca 01       	xor	#1,r0				#-
//   265c8:	2a 01       	mov.w	r0,@r10				#-
//   265ca:	a0 01       	bra	0x265d0				#-
//   265cc:	00 09       	nop					#-
//   265ce:	e2 0f       	mov	#15,r2				#-
//   265d0:	da 28       	mov.l	0x26674,r10	! ffff6c3e	#-
//   265d2:	60 a1       	mov.w	@r10,r0				#-
//   265d4:	db 95       	mov.l	0x2682c,r11	! ffbf		#-
//   265d6:	20 b9       	and	r11,r0				#-
//   265d8:	2a 01       	mov.w	r0,@r10				#-
//   265da:	d0 93       	mov.l	0x26828,r0	! ffff6b38	#-
//   265dc:	60 01       	mov.w	@r0,r0				#-
//   265de:	c8 80       	tst	#-128,r0			#-
//   265e0:	89 0a       	bt	0x265f8				#-
//   265e2:	61 1d       	extu.w	r1,r1				#-
//   265e4:	21 18       	tst	r1,r1				#-
//   265e6:	8b 07       	bf	0x265f8				#-
//   265e8:	6a 2d       	extu.w	r2,r10				#-
//   265ea:	64 8d       	extu.w	r8,r4				#-
//   265ec:	65 a3       	mov	r10,r5				#-
//   265ee:	b0 f9       	bsr	0x267e4				#-
//   265f0:	00 09       	nop					#-
//   265f2:	e9 00       	mov	#0,r9				#-
//   265f4:	a0 06       	bra	0x26604				#-
//   265f6:	00 09       	nop					#-
//   265f8:	6a 2d       	extu.w	r2,r10				#-
//   265fa:	64 8d       	extu.w	r8,r4				#-
//   265fc:	65 a3       	mov	r10,r5				#-
//   265fe:	b0 ca       	bsr	0x26796				#-
//   26600:	00 09       	nop					#-
//   26602:	e9 01       	mov	#1,r9				#-
//   26604:	e8 00       	mov	#0,r8				#-
//   26606:	e1 00       	mov	#0,r1				#-
//   26608:	6a 1e       	exts.b	r1,r10				#-
//   2660a:	e4 01       	mov	#1,r4				#-
//   2660c:	65 a3       	mov	r10,r5				#-
//   2660e:	db 89       	mov.l	0x26834,r11	! 3531c		#-
//   26610:	4b 0b       	jsr	@r11				#-
//   26612:	00 09       	nop					#-
//   26614:	6a 2d       	extu.w	r2,r10				#-
//   26616:	20 a8       	tst	r10,r0				#-
//   26618:	89 00       	bt	0x2661c				#-
//   2661a:	78 01       	add	#1,r8				#-
//   2661c:	71 01       	add	#1,r1				#-
//   2661e:	ea 04       	mov	#4,r10				#-
//   26620:	31 a2       	cmp/hs	r10,r1				#-
//   26622:	8b f1       	bf	0x26608				#-
//   26624:	da 87       	mov.l	0x26844,r10	! ffff6b3e	#-
//   26626:	6a a1       	mov.w	@r10,r10			#-
//   26628:	6a ad       	extu.w	r10,r10				#-
//   2662a:	64 8d       	extu.w	r8,r4				#-
//   2662c:	65 a3       	mov	r10,r5				#-
//   2662e:	da 84       	mov.l	0x26840,r10	! eee		#-
//   26630:	4a 0b       	jsr	@r10				#-
//   26632:	00 09       	nop					#-
//   26634:	40 00       	shll	r0				#-
//   26636:	d4 81       	mov.l	0x2683c,r4	! ffff6c58	#-
//   26638:	64 42       	mov.l	@r4,r4				#-
//   2663a:	65 03       	mov	r0,r5				#-
//   2663c:	da 7e       	mov.l	0x26838,r10	! 51c		#-
//   2663e:	4a 0b       	jsr	@r10				#-
//   26640:	00 09       	nop					#-
//   26642:	db 7e       	mov.l	0x2683c,r11	! ffff6c58	#-
//   26644:	2b 02       	mov.l	r0,@r11				#-
//   26646:	a0 03       	bra	0x26650				#-
//   26648:	00 09       	nop					#-
//   2664a:	ea 00       	mov	#0,r10				#-
//   2664c:	db 7e       	mov.l	0x26848,r11	! ffff6b44	#-
//   2664e:	2b a1       	mov.w	r10,@r11			#-
//   26650:	69 9d       	extu.w	r9,r9				#-
//   26652:	29 98       	tst	r9,r9				#-
//   26654:	89 01       	bt	0x2665a				#-
//   26656:	b1 21       	bsr	0x2689c				#-
//   26658:	00 09       	nop					#-
//   2665a:	69 f6       	mov.l	@r15+,r9			#-
//   2665c:	68 f6       	mov.l	@r15+,r8			#-
//   2665e:	62 f6       	mov.l	@r15+,r2			#-
//   26660:	61 f6       	mov.l	@r15+,r1			#-
//   26662:	6f e3       	mov	r14,r15				#-
//   26664:	6e f6       	mov.l	@r15+,r14			#-
//   26666:	4f 26       	lds.l	@r15+,pr			#-
//   26668:	00 0b       	rts					#-
//   2666a:	00 09       	nop	
}
#endif
