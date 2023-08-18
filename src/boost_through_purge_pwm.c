#include <stdint.h>

extern uint16_t gpio2;
extern uint16_t wastegate_solenoid_duty;

extern void update_purge_control_solenoid_duty(uint_fast16_t duty, uint_fast16_t tmax, uint_fast16_t valmax);

void update_boost_pwm()
{
	gpio2 &= ~0x8000;

#if !defined(WASTEGATE_SOLENOID_DUTY_MAX)
#error "WASTEGATE_SOLENOID_DUTY_MAX undefined, go to the hell"
#endif
	update_purge_control_solenoid_duty(wastegate_solenoid_duty, 25000, WASTEGATE_SOLENOID_DUTY_MAX);
}
