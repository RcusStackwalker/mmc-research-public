#ifndef COLANCER_MEMACCESS_H
#define COLANCER_MEMACCESS_H

#define TO_FULL_POINTER(ram_ptr) (0x808000 + ram_ptr)

void pushi();
void popi();

#error "M32R Assembly in common file"
static inline unsigned readu16(const signed offset)
{
	unsigned ret;
	__asm__ __volatile__("lduh %0, @(#%1,fp)" : "=&r"(ret) : "r"(offset) : "memory");
	return ret;
}

#define _readu16(offset) ({unsigned read_var; __asm__ __volatile__("lduh %0,@(" #offset",fp)" : "=&r"(read_var) : : "memory"); read_var;})
#define _writeu16(val, offset) do { unsigned write_var = val; __asm__ __volatile__("sth %0,@(" #offset",fp)" : : "r"(write_var) : "memory"); } while (0)
#define _read_low_ofu16(offset) ({unsigned read_var; __asm__ __volatile__("ldub %0,@(" #offset",fp)" : "=&r"(read_var) : : "memory"); read_var;})
#define read_low_ofu16(offset) _read_low_ofu16(offset + 1)

//turn into fp,#offset later
#define _BIT_SET(var, mask) 			\
do {						\
	writeu16(readu16(var) | mask, var);	\
} while (0);

//turn into fp,#offset later
#define _BIT_CLEAR(var, mask) 			\
do {						\
	writeu16(readu16(var) & ~mask, var);	\
} while (0);

#define readu16(offset) _readu16(offset)
#define writeu16(val, offset) _writeu16((val), offset)

#define BIT_SET(var, mask) _BIT_SET((var), (mask))
#define BIT_SET16 BIT_SET
#define BIT_CLEAR(var, mask) _BIT_CLEAR((var), (mask))
#define BIT_CLEAR16 BIT_CLEAR
#define IS_BIT_SET(var, mask) (readu16(var) & mask)
#define IS_BIT_SET8(var, mask) (readu8(var) & mask)
#define IS_BIT_SET16(var, mask) (readu16(var) & mask)

#define _readu8(offset) ({unsigned read_var; __asm__ __volatile__("ldub %0,@(" #offset",fp)" : "=&r"(read_var) : : "memory"); read_var;})
#define _writeu8(val, offset) do { unsigned write_var = val; __asm__ __volatile__("stb %0,@(" #offset",fp)" : : "r"(write_var) : "memory"); } while (0)
//turn into fp,#offset later
#define _BIT_SET8(var, mask) 			\
do {						\
	writeu8(readu8(var) | mask, var);	\
} while (0);

//turn into fp,#offset later
#define _BIT_CLEAR8(var, mask) 			\
do {						\
	writeu8(readu8(var) & ~mask, var);	\
} while (0);

#define readu8(offset) _readu8(offset)
#define writeu8(val, offset) _writeu8((val), offset)

#define BIT_SET8(var, mask) _BIT_SET8((var), (mask))
#define BIT_CLEAR8(var, mask) _BIT_CLEAR8((var), (mask))

#define HYSTERESIS_FLAG(flag_var, _bit_mask, condition_var, off_value, on_value) \
do {									\
	uint_fast16_t var = readu16(flag_var);				\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = readu16(condition_var);			\
	if (var & bit_mask) {						\
		if (off_value >= covar) writeu16(var & ~bit_mask, flag_var);	\
	} else {							\
		if (on_value < covar) writeu16(var | bit_mask, flag_var);		\
	}								\
} while (0)

#define HYSTERESIS_FLAG_LOCAL(flag_var, _bit_mask, condition_var, off_value, on_value) \
do {									\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = readu16(condition_var);			\
	if (flag_var & bit_mask) {						\
		if (off_value >= covar) flag_var &= ~bit_mask;		\
	} else {							\
		if (on_value < covar) flag_var |= bit_mask;		\
	}								\
} while (0)

#define HYSTERESIS_FLAG_THRESHOLD_HYSTOFF(flag_var, _bit_mask, condition_var, _on_value, off_hysteresis) \
do {									\
	uint_fast16_t var = readu16(flag_var);				\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = readu16(condition_var);			\
	uint_fast16_t on_value = _on_value;				\
	uint_fast16_t off_value = s_sub16(on_value, off_hysteresis);	\
	if (var & bit_mask) {						\
		if (off_value >= covar) writeu16(var & ~bit_mask, flag_var);	\
	} else {							\
		if (on_value < covar) writeu16(var | bit_mask, flag_var);		\
	}								\
} while (0)

#define HYSTERESIS_FLAG_THRESHOLD_HYSTON(flag_var, _bit_mask, condition_var, _off_value, on_hysteresis) \
do {									\
	uint_fast16_t var = readu16(flag_var);				\
	const uint_fast16_t bit_mask = _bit_mask;			\
	uint_fast16_t covar = readu16(condition_var);			\
	uint_fast16_t off_value = _off_value;				\
	uint_fast16_t on_value = s_add16(off_value, on_hysteresis);	\
	if (var & bit_mask) {						\
		if (off_value >= covar) writeu16(var & ~bit_mask, flag_var);	\
	} else {							\
		if (on_value < covar) writeu16(var | bit_mask, flag_var);		\
	}								\
} while (0)

#define INJECTION_MARKER_RESET(name)	\
	const unsigned  __attribute__((section("inj_r_" #name))) flash_reset_##name##_injected_instruction = (unsigned)name;

#define INJECTION_MARKER(name)	\
	const unsigned __attribute__((section("inj_" #name))) flash_##name##_injected_instruction = (unsigned)name;

#define MUT_INJECTION_MARKER_LOWU16(name) \
	const unsigned __attribute__((section("mutinj_" #name))) flash_##name##_injected_instruction = (unsigned)(0x808001 + name);

#define ADDRESS_INJECTION_MARKER(name) \
	const unsigned __attribute__((section("ainj_" #name))) flash_##name##_injected_instruction = (unsigned)name;

#define ROM_SECTION(x) __attribute__((section(x)))


#define MAX16(_x,_y) ({ uint_fast16_t x = (_x); uint_fast16_t y = (_y); \
	x < y ? y : x; })

#define MIN16(_x,_y) ({ uint_fast16_t x = (_x); uint_fast16_t y = (_y); \
	x < y ? x : y; })

#endif /*COLANT_MEMACCESS_H*/
