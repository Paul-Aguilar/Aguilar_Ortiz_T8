

#include "MK64F12.h"
#include "PIT.h"
#include "bits.h"

static volatile uint32_t dummyRead;

static uint8_t g_pit_intr_flag = 0;

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay)
{
	//initialize the value of the timer//
	PIT->CHANNEL[pit_timer]->LDVAL =system_clock/delay;
	//timer is enable//
	PIT->CHANNEL[pit_timer]->TCTRL |= PIT_TCTRL_TEN_MASK;
}


void PIT_clock_gating(void)
{
	//Initialize the clock of the PIT//
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

uint8_t PIT_get_interrupt_flag_status(void)
{
	return PIT->CHANNEL[0].TFLG;
}

void PIT_clear_interrupt_flag(void)
{
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[0].TCTRL; //read control register for clear PIT flag, this is silicon bug
}

void PIT_enable(void)
{
	//enables the PIT//
	PIT->MCR |= PIT_MCR_FRZ_SHIFT;
	PIT->MCR &= ~(PIT_MCR_FRZ_SHIFT);
}

void PIT_enable_interrupt(PIT_timer_t pit)
{
	/*It clear the flag*/
	PIT->CHANNEL[pit].TFLG |= PIT_TFLG_TIF_MASK;
	/*enables the interruption*/
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK;
}


