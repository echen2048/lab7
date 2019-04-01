// IO.c
// This software configures the switch and LED
// You are allowed to use any switch and any LED, 
// although the Lab suggests the SW1 switch PF4 and Red LED PF1
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: March 30, 2018
// Last Modified:  change this or look silly
// Lab number: 7

#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "ST7735.h"
//------------IO_Init------------
// Initialize GPIO Port for a switch and an LED
// Input: none
// Output: none
void IO_Init(void) {
 // --UUU-- Code to initialize PF4 and PF2
	uint8_t i=0;
	SYSCTL_RCGCGPIO_R = 0x21;
	i++;
	i++;
	GPIO_PORTF_PUR_R |= 0x10;
	GPIO_PORTF_DIR_R &= ~0x10;
	GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_DEN_R |= 0x14; 
}

//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void) {
 // --UUU-- PF2 is heartbeat
	GPIO_PORTF_DATA_R ^=0x04;
	return;
}


//------------IO_Touch------------
// wait for release and press of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void) {
	uint8_t state;
	while(1){
		IO_HeartBeat();
		state = GPIO_PORTF_DATA_R;
		state &= 0x10;
		if(GPIO_PORTF_DATA_R == 0){
			Delay1ms(20);
			state = GPIO_PORTF_DATA_R;
			state &= 0x10;
			if(GPIO_PORTF_DATA_R==0x10){
				return;
			}
		}
	}
 // --UUU-- wait for release; delay for 20ms; and then wait for press
}  

