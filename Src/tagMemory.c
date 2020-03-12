//
// tagMemory.c
// Created by Andreas Gerono on 10/03/2020.

#include "tagMemory.h"

#include "stm32l0xx_hal.h"




#define TAG_SIZE 4
#define POINTER_ADDR 0
#define KEY_TAG_ADDR 1
#define TIMEOUT HAL_MAX_DELAY
#define BUFFER_SIZE 100
#define UID_ADDR 1

#define EEPROM_START 0x08080000


static uint32_t mem_pointer = 0;
static uint32_t key_tag;
static uint32_t tag_buffer[100];

uint32_t readFromEEPROM (uint32_t address) {
	address += EEPROM_START;
	return (*(__IO uint32_t *)address);
}

void writeToEEPROM (uint32_t address, uint32_t value) {
	address += EEPROM_START;
	HAL_FLASHEx_DATAEEPROM_Program (FLASH_TYPEPROGRAMDATA_WORD, address, value);
}


static uint32_t tagToBits(uint8_t *tag){
	uint32_t tagUint32;
	for (uint8_t i=0;i<TAG_SIZE;i++) {
		tagUint32 |= tag[i] << i*8;
	}
	return tagUint32;
}


//void tagMemory_init(){
	//
	//	HAL_I2C_Mem_Read(&hi2c1, DEV_ADDR, POINTER_ADDR, I2C_MEMADD_SIZE_16BIT, &mem_pointer, 1, TIMEOUT);	//read pointer
//
//	HAL_I2C_Mem_Read(&hi2c1, DEV_ADDR, UID_ADDR, I2C_MEMADD_SIZE_16BIT, uid_tag, TAG_SIZE, TIMEOUT);	//read uid
//
//	HAL_I2C_Mem_Read(&hi2c1, DEV_ADDR, 6, I2C_MEMADD_SIZE_16BIT, tag_buffer, BUFFER_SIZE, TIMEOUT);		//read rest tags
//}
//
//void tag_store(uint8_t *tag){
//
//
//	HAL_I2C_Mem_Write(&hi2c1, DEV_ADDR, 0, I2C_MEMADD_SIZE_16BIT, tag, TAG_SIZE, TIMEOUT);
//	mem_pointer += TAG_SIZE;
//	HAL_I2C_Mem_Write(&hi2c1, DEV_ADDR, POINTER_ADDR, I2C_MEMADD_SIZE_16BIT, &mem_pointer, 1, TIMEOUT);	//write pointer
//	HAL_I2C_Mem_Read(&hi2c1, DEV_ADDR, 6, I2C_MEMADD_SIZE_16BIT, tag_buffer, BUFFER_SIZE, TIMEOUT);		//read rest tags
//}





void tagMemory_init(){
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram(); //??

}
