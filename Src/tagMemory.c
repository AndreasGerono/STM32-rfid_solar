//
// tagMemory.c
// Created by Andreas Gerono on 10/03/2020.

#include "tagMemory.h"

#include "stm32l0xx_hal.h"
#include "eeprom.h"



#define TAG_SIZE 4
#define TAG_COUNT_ADDR 0
#define KEY_TAG_ADDR 1
#define TAG_START_ADDR 2
#define TIMEOUT HAL_MAX_DELAY


static uint32_t tag_count = 0;
static uint32_t key_tag;




static uint32_t tagToBits(uint8_t *tag){
	uint32_t tagUint32;
	for (uint8_t i=0;i<TAG_SIZE;i++) {
		tagUint32 |= tag[i] << i*8;
	}
	return tagUint32;
}

void tag_erase_all(){
	for (uint32_t addr = 0; addr < EEPROM_SIZE; addr++) {
		eeprom_erase(addr);
	}
}

void tag_init(){
	eeprom_init();
	key_tag = eeprom_read(KEY_TAG_ADDR);
	tag_count = eeprom_read(TAG_COUNT_ADDR);
}


_Bool tag_find(uint8_t *tag){
	uint32_t tagBits = tagToBits(tag);
	_Bool status = RESET;

	for (uint32_t addr = 0; addr < tag_count ; addr++) {
		if (tagBits == eeprom_read(addr+TAG_START_ADDR)) {
			status = SET;
			break;
		}
	}
	return status;
}

_Bool tag_match_with_key(uint8_t *tag){
	return key_tag == tagToBits(tag);
}


_Bool tag_store(uint8_t *tag){
	uint32_t tagBits = tagToBits(tag);
	if (tag_find(tagBits))
		return 0;

	eeprom_write(tag_count+TAG_START_ADDR, tagBits);
	tag_count++;
	return 1;
}





