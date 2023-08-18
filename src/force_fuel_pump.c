#include <stdint.h>

extern uint16_t age_x1_ignition;
extern uint16_t gpio1;
extern uint16_t is_fuel_pump_active();

const uint16_t flash_fuel_pump_active_time_after_ignition = 40 * 2;

uint16_t new_is_fuel_pump_active()
{
	return (age_x1_ignition < flash_fuel_pump_active_time_after_ignition) || is_fuel_pump_active();
}

void new_fuel_pump_control()
{
	if (new_is_fuel_pump_active()) {
		gpio1 |= 0x80;
	} else {
		gpio1 &= ~0x80;
	}
}
