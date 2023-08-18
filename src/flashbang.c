typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef signed short int16_t;
#define FSTAT ((volatile uint8_t *)0x8007e1)
#define FCNT1 ((volatile uint8_t *)0x8007e2)
#define FCNT2 ((volatile uint8_t *)0x8007e3)
#define FCNT4 ((volatile uint8_t *)0x8007e5)
#define P4DATA ((volatile uint8_t *)0x800704)
#define TMS1CT ((volatile uint16_t *)0x8003d0)
#define FLASH_COMMAND_REGISTER ((volatile uint16_t *)0x0)

uint16_t heartbeat_deadline = 1;

const struct { uint32_t start; uint32_t end; } flash_block_edges[] = {
	{ 0x00000, 0x03ffe },
	{ 0x04000, 0x05ffe },
	{ 0x06000, 0x07ffe },
	{ 0x08000, 0x0fffe },
	{ 0x10000, 0x1fffe },
	{ 0x20000, 0x2fffe },
	{ 0x30000, 0x3fffe },
	{ 0x40000, 0x4fffe },
	{ 0x50000, 0x5fffe },
	{ 0x60000, 0x6fffe },
	{ 0x70000, 0x7fffe },
	//{ 0x80000, 0x8fffe },
	//{ 0x90000, 0x9fffe },
	//{ 0xa0000, 0xafffe },
	//{ 0xb0000, 0xbfffe }
};

#define itemsof(x) (sizeof(x) / sizeof(x[0]))

//typedef void (*heartbeat_prototype)();


//#define bootloader_heartbeat ((heartbeat_prototype*)(0x805000 - 0x320 + 0x974))

void heartbeat()
{
	*P4DATA ^= 0x01;
	heartbeat_deadline += 1250;
}

void check_heartbeat()
{
	int diff = heartbeat_deadline;
	diff -= *TMS1CT;
	if (diff > 0) return;
	heartbeat();
}

void init_heartbeat()
{
	heartbeat_deadline = *TMS1CT;
	heartbeat();
}


int erase_block_memfun(volatile uint16_t *p_block_end)
{
	int ret = 0;
	volatile unsigned timeout;

	*p_block_end = 0x2020;//block erase;
	*p_block_end = 0xd0d0;
	timeout = 50;
	while (--timeout);
	timeout = 600 * 40000;//601us - that should millisecond
	while (!(*FSTAT & 0x01)) {//FBUSY
		check_heartbeat();
		if (!--timeout) {
			ret = -1;
			goto exit;
		}
	}
	ret = 1;
exit:
	return ret;
}

void flashing_init()
{
	*FCNT1 &= ~0x10;
	*FCNT1 |= 0x10;
	volatile int i;
	for (i = 0; i < 15; ++i);

	*FCNT4 = 1;
	*FCNT4 = 0;
}

void flashing_deinit()
{
	*FLASH_COMMAND_REGISTER = 0x5050;
	*FLASH_COMMAND_REGISTER = 0xffff;	
	(void)*FLASH_COMMAND_REGISTER;
	*FCNT1 &= ~0x10;
}

void flashbang()
{
	unsigned i;
	init_heartbeat();
	flashing_init();
	*FCNT2 = 0;
	*FCNT2 = 1;
	for (i = 0; i < itemsof(flash_block_edges); ++i) {
		if (erase_block_memfun((uint16_t *)(flash_block_edges[i].end)) != 1) {
			break;
		}
	}
	flashing_deinit();
	while (1);
}
