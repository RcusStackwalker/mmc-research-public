#ifndef MMC_EEPROM_H
#define MMC_EEPROM_H

#define EEPROM_FLAGS0_I2C_FAILURE		0x01
#define EEPROM_FLAGS0_DATA1_RAM_MISMATCH	0x02
#define EEPROM_FLAGS0_AREA0_CRC_MISMATCH	0x04
#define EEPROM_FLAGS0_AREA1_CRC_MISMATCH	0x08

#define EEPROM_FLAGS0_DATA1_CRC_FAILURE		0x80
#define EEPROM_FLAGS0_EEPROM_INTACT		0x0100

#define EEPROM_FLAGS0_HEADER_DATA_VALID		0x8000

#define EEPROM_FLAGS1_DO_UPDATE			0x01

struct eeprom_data_map {
	/*0-144*/
	uint32_t eeprom_sequence_index;

	/*64 - +14*2* - dtc*/

	/*144-176 -- doubled*/
	/*176-208 - ?*/
	/*208-252 - data*/
};
#endif /*MMC_EEPROM_H*/
