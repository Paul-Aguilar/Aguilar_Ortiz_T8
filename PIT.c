/*
 * PIT.c
 *
 *  Created on: 23 feb. 2020
 *      Author: Mike Ortiz
 */

#include "MK64F12.h"
#include "PIT.h"
#include "Bits.h"

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay)
{
	PIT->CHANNEL[pit_timer]->LDVAL =system_clock/delay;
	PIT->CHANNEL[pit_timer]->TCTRL |= PIT_TCTRL_TEN_MASK;
}


void PIT_clock_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

uint8_t PIT_get_interrupt_flag_status(void){
	PIT->CHANNEL[0]->TFLG |= PIT_TFLG_TIF_MASK;
}

void PIT_clear_interrupt_flag(void);

void PIT_enable(void){
	PIT->MCR = PIT_MCR_FRZ_SHIFT;
}

void PIT_enable_interrupt(PIT_timer_t pit);

