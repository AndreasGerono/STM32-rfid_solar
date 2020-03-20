/*
 * tagAction.c
 *
 *  Created on: 20 Mar 2020
 *      Author: macandreas
 */

#include "tagAction.h"
#include "tagMemory.h"
#include "rc522.h"
#include "gpio.h"


typedef enum{
	OK = 0,
	NO_MATCH,
	NO_CARD ,
	IS_CARD,
	IS_KEY,
	IS_NEW_CARD,
	CARD_EXIST,
} Status;




static uint8_t uid[MFRC522_MAX_LEN];
static uint8_t tag[MFRC522_MAX_LEN];
static Status status = NO_CARD;

//TODO add timeouts


static void error_handler(){
	LD2_GPIO_Port->BSRR = LD2_Pin;
	HAL_Delay(200);
	LD2_GPIO_Port->BRR = LD2_Pin;
}

static void open_gate_handler(){
	LD3_GPIO_Port->BSRR = LD3_Pin;
	HAL_Delay(200);
	LD3_GPIO_Port->BRR = LD3_Pin;
}


static void wait_for_release(){
	while (status != NO_CARD){
		HAL_Delay(50);
		if (MFRC522_Request(PICC_REQALL, tag) == MI_ERR)
			status = NO_CARD;
	}
}


void tag_wait_if_no_key(){
	while(!tag_is_key()){
		if(!MFRC522_Request(PICC_REQALL, tag)){
			status = IS_KEY;
			if (!MFRC522_Anticoll(uid))
				tag_store_key(uid);
		}
		HAL_Delay(200);
		LD3_GPIO_Port->ODR ^= LD3_Pin;
	}
	LD3_GPIO_Port->BRR = LD3_Pin;
	wait_for_release();
}


static void add_tag_handler(){
	LD3_GPIO_Port->BSRR = LD3_Pin;
	wait_for_release();
	while (status != OK){
		HAL_Delay(200);
		if(!MFRC522_Request(PICC_REQALL, tag)){
			status = IS_CARD;
			if (!MFRC522_Anticoll(uid)){
				if (tag_match_with_key(uid)){
					status = IS_KEY;
					error_handler();
				}
				else if (tag_find(tag)){
					status = CARD_EXIST;
					error_handler();
				}
				else{
					tag_store(uid);
					status = OK;
				}
			}
		}
	}
	LD3_GPIO_Port->BRR = LD3_Pin;
}







void tag_auth(){
	status = NO_CARD;
	if(!MFRC522_Request(PICC_REQALL, tag)){
		if (!MFRC522_Anticoll(uid)){
			if (tag_match_with_key(uid)) {
				status = IS_KEY;
				add_tag_handler();
			}
			else if (tag_find(uid)) {
				status = OK;
				open_gate_handler();
			}
			else{
				status = NO_MATCH;
				error_handler();
			}
		}
		wait_for_release();
	}
	HAL_Delay(10);
}
