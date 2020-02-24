/*
 * PIT.c
 *
 *  Created on: 23 feb. 2020
 *      Author: Mike Ortiz
 */

#include "MK64F12.h"
#include "PIT.h"
#include "Bits.h"

uint8_t flag_interrupt = 0x00;
uint32_t dummyRead = 0;

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay)
{
	/*initialize the value of the timer*/
	PIT->CHANNEL[pit_timer].LDVAL = system_clock/delay;
	/*timer is enable*/
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN_MASK;
}


void PIT_clock_gating(void)
{
	/*Initialize the clock of the PIT*/
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

uint8_t PIT_get_interrupt_flag_status(void)
{
	return flag_interrupt;
}

void PIT_clear_interrupt_flag(void)
{
	flag_interrupt |= 0x00;
}

void PIT_enable(void)
{
	/*enables the PIT*/
	PIT->MCR |= PIT_MCR_FRZ_SHIFT;
}

void PIT_enable_interrupt(PIT_timer_t pit)
{
	/*Clears the flag*/
	PIT->CHANNEL[pit].TFLG |= PIT_TFLG_TIF_MASK;
	/*Enables the interrupt*/
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK;
}

void PIT0_IRQHandler(void)
{
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	flag_interrupt |= 0x08;
	dummyRead = PIT->CHANNEL[0].TCTRL;
}

void PIT1_IRQHandler(void)
{
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	flag_interrupt |= 0x02;
	dummyRead = PIT->CHANNEL[1].TCTRL;
}

void PIT2_IRQHandler(void)
{
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
	flag_interrupt |= 0x04;
	dummyRead = PIT->CHANNEL[2].TCTRL;
}

void PIT3_IRQHandler(void)
{
	PIT->CHANNEL[3].TFLG |= PIT_TFLG_TIF_MASK;
	flag_interrupt |= 0x08;
	dummyRead = PIT->CHANNEL[3].TCTRL;
}



