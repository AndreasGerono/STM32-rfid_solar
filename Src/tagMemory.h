//
// tagMemory.h
// Created by Andreas Gerono on 10/03/2020.

#ifndef _tagMemory_h_
#define _tagMemory_h_

#include "stdint.h"


void tag_init();
_Bool tag_is_key();
_Bool tag_find(uint8_t *key);
void tag_store(uint8_t *tag);
void tag_store_key(uint8_t *key);
_Bool tag_match_with_key(uint8_t *tag);
void tag_erase_all();


#endif
