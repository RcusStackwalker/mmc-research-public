rx11 - meter related dash ecu
rx7 - speed source
rx10 - maybe a/c control?

//0x20 rx slot timeout
#define CAN0_DEFAULT_FAULT_0400		0x0400
//0x10 rx slot timeout
#define CAN0_DEFAULT_FAULT_0800		0x0800
//slot 10 timeout
#define CAN0_DEFAULT_FAULT_1000		0x1000
//reset unconditionally
#define CAN0_DEFAULT_FAULT_2000_UNUSED	0x2000
//slot 7 and 9 timeouts, presumably abs-asc
#define CAN0_DEFAULT_FAULT_4000		0x4000
//reset unconditionally
#define CAN0_DEFAULT_FAULT_8000_UNUSED	0x8000
