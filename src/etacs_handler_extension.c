#include "stdint.h"

uint_fast16_t can0_slot_rx_get_data(uint_fast16_t p_slot, uint8_t *data);

extern uint8_t can_rx_buffer_main[8];

uint8_t position_lights = 0;

#define ETACS_DATA0_POSITION_LIGHTS 0x04
#define ETACS_DATA2_FOG_LIGHTS 0x10

void can_etacs_rx_update()
{
	uint_fast16_t ret = can0_slot_rx_get_data(CAN_ETACS_RX_SLOT, can_rx_buffer_main);
	if (ret & 0x0200) {
		/*lost*/
	}
	if (ret & 0x80) {
		/*error*/
	}
	if (ret & 0x0400) {
		/*ok*/
	}

	if (!(ret & 0x0400)) return;//no new message

	position_lights = can_rx_buffer_main[2] & ETACS_DATA2_FOG_LIGHTS ? 1 : 0;
}
