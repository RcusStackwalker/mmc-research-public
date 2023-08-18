#ifndef MMC_CAN_H
#define MMC_CAN_H

void can0_slot_tx_update(uint8_t p_slot_index,
	uint8_t data0,
	uint8_t data1,
	uint8_t data2,
	uint8_t data3,
	uint8_t data4,
	uint8_t data5,
	uint8_t data6,
	uint8_t data7);

unsigned can0_slot_rx_get_data(uint8_t p_slot_index, uint8_t *p_buffer);

extern uint8_t can_rx_buffer[8];
extern uint8_t can_rx_buffer_main[8];


extern uint16_t can0_flags;
#define CAN0_FLAGS_TRANSMISSION_SUPPRESSED 0x0400

#endif /*MMC_CAN_H*/
