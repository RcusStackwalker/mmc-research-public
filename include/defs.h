#ifndef MMC_DEFS_H
#define MMC_DEFS_H


#define ZS16_SIGN(var) (var >= 0x8000 ? (var > 0x8000 ? 1 : 0) : -1)

#define S_TO_ZS16(var) (0x7fff < var ? 0xffff : (var >= -32768 ? var + 0x8000 : 0))

#define S32_ADD(l, r) ({ uint32_t result = l + r; result < l ? 0xffffffff : result; })
#define S16_ADD(l, r) (l < 0xffff - r ? l + r : 0xffff)
#define S32_SUB(l, r) (-r < -l ? 0 : l - r)
#define S16_DIVU(l, r) (0xffff * r < l ? 0xffff : l / r )

#define S32_MUL(l, r) (0xffffffff / r < l ? 0xffffffff : l * r)

#define S_DEC(var) do { unsigned l_value = var; if (l_value) var = l_value - 1; } while (0)

#define itemsof(x) (sizeof(x) / sizeof(x[0]))

#define MAX16(_x,_y) ({ uint_fast16_t x = (_x); uint_fast16_t y = (_y); \
	x < y ? y : x; })

#define MIN16(_x,_y) ({ uint_fast16_t x = (_x); uint_fast16_t y = (_y); \
	x < y ? x : y; })

#define HYSTERESIS_FLAG(flag_var, _bit_mask, condition_var, off_value, on_value)	\
do {											\
	uint_fast16_t flag_value = flag_var;						\
	const uint_fast16_t bit_mask = _bit_mask;					\
	uint_fast16_t covar = condition_var;						\
	if (flag_value & bit_mask) {							\
		if (off_value >= covar) flag_var = flag_value & ~bit_mask;		\
	} else {									\
		if (on_value < covar) flag_var = flag_value | bit_mask;			\
	}										\
} while (0)

#define HYSTERESIS_FLAG_CCONDA(flag_var, _bit_mask, condition_var, conditions) \
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

#define BIT_SET_CONDITION(var, bit_mask, condition) do { \
	if (condition) { \
		var |= bit_mask; \
	} else { \
		var &= ~(bit_mask); \
	} \
} while (0)

#define IS_BIT_SWITCHON(old_var, var, bit_mask) \
((old_var ^ var) & var & (bit_mask))


#endif /*MMC_DEFS_H*/
