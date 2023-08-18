#include "asc_to_dash_rx.h"

#include <can.h>

void update_asc_to_dash_rx()
{
	unsigned ret = can0_slot_rx_get_data(ASC_TO_DASH_RX_SLOT_INDEX, can_rx_buffer_main);
	if (!(ret & 0x0400)) {
		return;
	}
	asc_off_prev = asc_off;
	asc_off = !!(can_rx_buffer_main[0] & 0x40);
}
