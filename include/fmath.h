#ifndef MMC_FIXED_POINT_MATH_H
#define MMC_FIXED_POINT_MATH_H

#include <stdint.h>

#define MAP_AXIS_POINTER(x) (x)

#define PTL16(percentage) ((uint16_t)(percentage * 32 / 10))
#define RTR16(rpm)	((uint16_t)(rpm * 256 / 1000))
#define VSHIRES(kph)	((uint16_t)(kph * 4))

#if 0

#define HYSTERESIS_FLAG(flag_var, _bit_mask, condition_var, conditions) \
do {									\
	uint_fast16_t var = flag_var;				\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = condition_var;			\
	if (var & bit_mask) {						\
		if (conditions[0] >= covar) flag_var = var & ~bit_mask; \
	} else {							\
		if (conditions[1] < covar) flag_var = var | bit_mask;		\
	}								\
} while (0)

#endif



uint_fast16_t s_add16(uint_fast16_t l, uint_fast16_t r);
uint32_t add16(uint_fast16_t l, uint_fast16_t r);
uint32_t s_add32(uint32_t x, uint32_t y);
void memzero16(uint16_t *begin, uint16_t *end);
void s_dec_u16a_atomic(uint16_t *start, uint16_t *end);
void s_inc_u16a_atomic(uint16_t *start, uint16_t *end);
uint8_t s_16to8(uint16_t v);
uint16_t s_32to16(uint32_t v);
uint16_t mid16(uint16_t x, uint16_t y, uint16_t z);
uint32_t mid32(uint32_t x, uint32_t y, uint32_t z);
uint16_t s_mul_divu16(uint16_t x, uint16_t y, uint16_t z);
uint32_t s_mul32_16_divu16(uint32_t x, uint16_t y, uint16_t z);
uint16_t ps_mul_divu16(uint16_t x, uint16_t y, uint16_t z);
uint32_t ps_mul32_16_divu16(uint32_t x, uint16_t y, uint16_t z);
uint16_t s_scale_base128(uint16_t x, uint16_t y);
uint32_t s32_scale_base128(uint32_t x, uint32_t y);
uint16_t ps_scale_base128(uint16_t x, uint16_t y);
uint32_t ps32_scale_base128(uint32_t x, uint16_t y);
uint16_t s_scale_base256(uint16_t x, uint16_t y);
uint32_t s32_scale_base256(uint32_t x, uint16_t y);
uint16_t ps_scale_base256(uint16_t x, uint16_t y);
uint32_t ps_mul32_16(uint32_t x, uint16_t y);
uint8_t conv8f8_uint(uint16_t x);
uint16_t conv16f16_uint(uint32_t x);
uint16_t conv_u8_8f8(uint8_t x);
uint32_t conv_uint_16f16(uint32_t x);
uint8_t p_conv8f8_u8(uint16_t v);
uint16_t p_conv32_16(uint32_t v);
uint16_t swap_bytes16(uint16_t v);
uint16_t to_g16(uint8_t v);
uint16_t s_divu16(uint16_t l, uint16_t r);
uint16_t s16_divu32_16(uint32_t l, uint16_t r);
uint32_t s32_divu32_16(uint32_t l, uint16_t r);
uint16_t ps_divu16(uint16_t l, uint16_t r);
uint16_t ps16_divu32_16(uint32_t l, uint16_t r);
uint32_t prec_sat32_divu32_16(uint32_t l, uint16_t r);
uint16_t aprxu16_256(uint16_t p0, uint16_t p1, uint16_t rat256);//higher rate - more of p0
uint16_t aprxu32(uint32_t p0, uint32_t p1, uint16_t rat);
uint16_t aprxu16_255(uint16_t p0, uint16_t p1, uint16_t rat255);//higher rate - more of p0
uint32_t p_aprx16f16_255(uint32_t p0, uint32_t p1, uint16_t rat255);

//uint16_t map8u16(const struct map8_desc *ptr);
//uint16_t mapu16(const struct map16_desc *ptr);
//uint16_t multimap8u16(const struct map8_description **ptr);
//uint16_t multimapu16(const struct map16_description **ptr);

uint_fast16_t map8u16(const void *ptr);
uint_fast16_t mapu16(const void *ptr);
uint_fast16_t multimap8u16(const void *ptr);
uint_fast16_t multimapu16(const void *ptr);
uint8_t *multiu8a(uint8_t * const *ptr);
void *multivoidstar(void * const *ptr);
uint8_t multiu8(const uint8_t *ptr);
uint16_t multiu16(const uint16_t *ptr);
uint16_t p_aprxu16_255_2(uint16_t p0, uint16_t p1, uint16_t rate);

//void calc_axis(const struct axis_desc *ptr);

void calc_axis(const void *ptr);

uint16_t s_mul16(uint16_t l, uint16_t r);
uint32_t mul16(uint16_t l, uint16_t r);
uint32_t s_mul32(uint32_t l, uint32_t r);
uint_fast16_t s_sub16(uint_fast16_t l, uint_fast16_t r);
uint32_t s_sub32(uint32_t l, uint32_t r);

#define IN_BOUNDS16(var, low, high) \
((readu16(var) >= low) && (readu16(var) <= high))

extern uint16_t temp_axis_src;
extern uint16_t temp_axis_target_x;
extern uint16_t temp_axis_target_y;

#endif /*MMC_FIXED_POINT_MATH_H*/
