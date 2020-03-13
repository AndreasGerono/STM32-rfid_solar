//
// eeprom.h
// Created by Andreas Gerono on 11/03/2020.

#ifndef _eeprom_h_
#define _eeprom_h_

#include "stdint.h"

//SIZE IN WORDS!
//256 WORDS = 1024 BYTES

#define EEPROM_SIZE 256


uint32_t eeprom_read (uint32_t address);
void eeprom_write (uint32_t address, uint32_t value);
void eeprom_erase(uint32_t address);
void eeprom_init();


#endif
