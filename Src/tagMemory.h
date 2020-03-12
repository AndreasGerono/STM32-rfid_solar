//
// tagMemory.h
// Created by Andreas Gerono on 10/03/2020.

#ifndef _tagMemory_h_
#define _tagMemory_h_

#include "stdint.h"




void tagMemory_init();
void tagMemory_erase();
void tag_store(uint8_t *tag);

uint32_t readFromEEPROM (uint32_t address);
void writeToEEPROM (uint32_t address, uint32_t value);


#endif
