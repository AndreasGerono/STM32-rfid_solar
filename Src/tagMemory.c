//
// tagMemory.c
// Created by Andreas Gerono on 10/03/2020.

#include "tagMemory.h"

#include "stm32l0xx_hal.h"
#include "eeprom.h"



#define TAG_SIZE 4
#define IS_KEY_ADDR 0
#define TAG_COUNT_ADDR 1
#define KEY_TAG_ADDR 2
#define TAG_START_ADDR 3
#define TIMEOUT HAL_MAX_DELAY

#define PREVIEW_SIZE 20

uint32_t tag_count = 0;
uint32_t key_tag = 0;
uint32_t tag_preview[PREVIEW_SIZE];

static void update_preview(){
	for (uint32_t addr = 0; addr < PREVIEW_SIZE; addr++) {
		tag_preview[addr] = eeprom_read(addr);
	}
	HAL_Delay(1);
}

static uint32_t tagToBits(uint8_t *tag){
	uint32_t tagUint32 = 0;
	for (uint8_t i=0;i<TAG_SIZE;i++) {
		tagUint32 += tag[i] << i*8;
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
	tag_count = eeprom_read(TAG_COUNT_ADDR);
	key_tag = eeprom_read(KEY_TAG_ADDR);
	update_preview();
}


_Bool tag_is_key(){
	return eeprom_read(IS_KEY_ADDR) == 0xFF;
}

void tag_store_key(uint8_t *key){
	uint32_t tagBits = tagToBits(key);
	key_tag = tagBits;
	eeprom_write(KEY_TAG_ADDR, key_tag);
	eeprom_write(IS_KEY_ADDR, 0xff);
	update_preview();
}

//TODO look in preview -> faster
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


void tag_store(uint8_t *tag){
	uint32_t tagBits = tagToBits(tag);
	eeprom_write(tag_count+TAG_START_ADDR, tagBits);
	tag_count++;
	eeprom_write(TAG_COUNT_ADDR, tag_count);
	update_preview();
}





