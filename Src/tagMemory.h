//
// tagMemory.h
// Created by Andreas Gerono on 10/03/2020.

#ifndef _tagMemory_h_
#define _tagMemory_h_

#include "stdint.h"


void tag_init();
_Bool tag_store(uint8_t *tag);
_Bool tag_find(uint8_t *tag);
_Bool tag_match_with_key(uint8_t *tag);
void tag_erase_all();


#endif
