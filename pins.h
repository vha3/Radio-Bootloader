/**
 * Copyright (c) 2015 panStamp <contact@panstamp.com>
 *
 * This file is part of the panStamp project.
 *
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 *
 * Author: Daniel Berenguer
 * Creation date: 06/17/2015
 */

/* OLIMEX BOARD */

#ifndef _PINS_H
#define _PINS_H

#include <stdint.h>

#define __OLIMEX__  1

// Enable pseudo-pin interrupts on P3
#define __ENABLE_P3_PIN_INTERRUPTS__  1

// UART
#define pinUARTmap()      P1MAP6 = PM_UCA0TXD; P1MAP5 = PM_UCA0RXD
#define pinUARTconfig()   P1SEL |= BIT6 | BIT5      // Set P1.6 and P1.5 to USCI Mode
// I2C
#define pinI2Cmap()       P2MAP0 = PM_UCB0SCL; P2MAP1 = PM_UCB0SDA
#define pinI2Cconfig()    P2SEL |= BIT3 | BIT4      // Set P2.0 and P2.1 to I2C function
// SPI
#define pinSPImap()       P1MAP3 = PM_UCB0SIMO; P1MAP2 = PM_UCB0SOMI; P1MAP4 = PM_UCB0CLK
#define pinSPIconfig()    P1SEL |= BIT3 | BIT2 | BIT4  // Set P1.0, P1.1 and P1.2 to USCI function

#define NOT_A_PORT 0
#define NOT_A_PIN 0
#define NOT_ON_TIMER 0
#define NOT_ON_ADC 0xFF

// REMOVE THESE, FOR PANSTAMP LDO BOARD
#define HGM     20
#define LNA_EN  19
#define PA_EN   18

// Ports
enum{
  P1 = 1,
  P2,
  P3,
  PJ
};

// Timers
enum{
  T0A0,
  T0A1,
  T0A2,
  T0A3,
  T0A4,
  T1A0,
  T1A1,
  T1A2
};

// ADC channels
static const uint8_t A0 = 13;
static const uint8_t A1 = 12;
static const uint8_t A2 = 11;
static const uint8_t A3 = 10;
static const uint8_t A4 = 9;
static const uint8_t A5 = 8;
static const uint8_t A10 = 128 + 10; // special. This is the internal temp sensor
static const uint8_t A11 = 128 + 11; // special. This is Vcc/2

// On-board LED
#define ONBOARD_LED_1 26
#define ONBOARD_LED_2 16
#define BUTTON_ONE 27
#define BUTTON_TWO 17
#define LED_1 ONBOARD_LED_1
#define LED_2 ONBOARD_LED_2
#define INIT_ONBOARD_LED()    P1DIR |= BIT0; P1OUT &= ~BIT0

// ADC resolution
#define ADC_RESOLUTION  0xFFF


const uint16_t digital_pin_to_pmap[] = {
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	(uint16_t) &P2MAP5,
	(uint16_t) &P2MAP4,
    (uint16_t) &P2MAP3,
    (uint16_t) &P2MAP2,
    (uint16_t) &P2MAP1,
    (uint16_t) &P2MAP0,
    (uint16_t) &P1MAP7,
    (uint16_t) &P1MAP6,
	(uint16_t) &P2MAP6, //On-board LED 2
    (uint16_t) &P2MAP7, //Button 2
    (uint16_t) &P3MAP0,
    (uint16_t) &P3MAP1,
    (uint16_t) &P3MAP2,
    (uint16_t) &P3MAP3,
    (uint16_t) &P3MAP4,
    (uint16_t) &P3MAP5,
	(uint16_t) &P3MAP6,
    (uint16_t) &P3MAP7,
    (uint16_t) &P1MAP0, //On-board LED 1
    (uint16_t) &P1MAP1, //Button 1
    (uint16_t) &P1MAP2,
    (uint16_t) &P1MAP3,
    (uint16_t) &P1MAP4,
    (uint16_t) &P1MAP5
};

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
	(uint16_t) &P3IN,
	(uint16_t) &PJIN
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
	(uint16_t) &P3OUT,
	(uint16_t) &PJOUT
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
	(uint16_t) &P3DIR,
	(uint16_t) &PJDIR
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
	(uint16_t) &P3REN,
	(uint16_t) NOT_A_PORT  //No PJREN
};

const uint16_t port_to_sel[] = {
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
	(uint16_t) &P3SEL,
	(uint16_t) NOT_A_PORT  // No PJSEL,
};

const uint16_t port_to_pmap[] = {
	NOT_A_PORT,	/* PMAP starts at port P1 */
	(uint16_t) &P1MAP0,
	(uint16_t) &P2MAP0,
	(uint16_t) &P3MAP0,
	NOT_A_PORT  // No PJMAP0
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* P2.5 */
	NOT_ON_TIMER, /* P2.4 */
	NOT_ON_TIMER, /* P2.3 */
	NOT_ON_TIMER, /* P2.2 */
	NOT_ON_TIMER, /* P2.1 */
	NOT_ON_TIMER, /* P2.0 */
	NOT_ON_TIMER, /* P1.7 */
	NOT_ON_TIMER, /* P1.6 */
	NOT_ON_TIMER, /* P2.6 LED */
	NOT_ON_TIMER, /* P2.7 Button 2*/
	NOT_ON_TIMER, /* P3.0 */
	T1A0,         /* P3.1 - note: A0 output cannot be used with analogWrite */
	T1A1,         /* P3.2 */
	T1A2,         /* P3.3 */
	NOT_ON_TIMER, /* P3.4 */
	NOT_ON_TIMER, /* P3.5 */
	NOT_ON_TIMER, /* P3.6 */
	NOT_ON_TIMER, /* P3.7*/
	T0A0,         /* P1.0 LED note: A0 output cannot be used with analogWrite */
	T0A1,         /* P1.1 Button 1*/
	T0A2,         /* P1.2 */
	T0A3,         /* P1.3 */
	T0A4,         /* P1.4 */
	NOT_ON_TIMER  /* P1.5 */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	P2,           /* P2.5 (8) */
	P2,           /* P2.4 (9) */
	P2,           /* P2.3 (10) */
	P2,           /* P2.2 (11) */
	P2,           /* P2.1 (12) */
	P2,           /* P2.0 (13) */
	P1,           /* P1.7 (14) */
	P1,           /* P1.6 (15) */
	P2,           /* P2.6 (16) LED */
	P2,           /* P2.7 (17) Button 1 */
	P3,           /* P3.0 (18) */
	P3,           /* P3.1 (19) */
	P3,           /* P3.2 (20) */
    P3,           /* P3.3 (21) */
    P3,           /* P3.4 (22) */
    P3,           /* P3.5 (23) */
    P3,           /* P3.6 (24) */
	P3,           /* P3.7 (25) */
	P1,           /* P1.0 (26) LED */
	P1,           /* P1.1 (27) Button 2 */
	P1,           /* P1.2 (28) */
	P1,           /* P1.3 (29) */
	P1,           /* P1.4 (30) */
	P1            /* P1.5 (31) */
};

const uint8_t digital_pin_to_bit_mask[] = {
		NOT_A_PORT,
		NOT_A_PORT,
		NOT_A_PORT,
		NOT_A_PORT,
		NOT_A_PORT,
		NOT_A_PORT,
		NOT_A_PORT,
		NOT_A_PORT,
		BIT5,           /* P2.5 */
		BIT4,           /* P2.4 */
		BIT3,           /* P2.3 */
		BIT2,           /* P2.2 */
		BIT1,           /* P2.1 */
		BIT0,           /* P2.0 */
		BIT7,           /* P1.7 */
		BIT6,           /* P1.6 */
		BIT6,           /* P2.6 LED */
		BIT7,           /* P2.7 Button 1 */
		BIT0,           /* P3.0 */
		BIT1,           /* P3.1 */
		BIT2,           /* P3.2 */
	    BIT3,           /* P3.3 */
	    BIT4,           /* P3.4 */
	    BIT5,           /* P3.5 */
	    BIT6,           /* P3.6 */
		BIT7,           /* P3.7 */
		BIT0,           /* P1.0 LED */
		BIT1,           /* P1.1 Button 2 */
		BIT2,           /* P1.2 */
		BIT3,           /* P1.3 */
		BIT4,           /* P1.4 */
		BIT5            /* P1.5 */
};

const uint16_t digital_pin_to_analog_in[] = {
	NOT_ON_ADC,
	NOT_ON_ADC,
	NOT_ON_ADC,
	NOT_ON_ADC,
	NOT_ON_ADC,
	NOT_ON_ADC,
	NOT_ON_ADC,
	NOT_ON_ADC,
	5,            /* P2.5 (8)*/
	4,            /* P2.4 (9)*/
	3,            /* P2.3 (10)*/
	2,            /* P2.2 (11)*/
	1,            /* P2.1 (12)*/
	0,            /* P2.0 (13)*/
	NOT_ON_ADC,   /* P1.7 (14)*/
	NOT_ON_ADC,   /* P1.6 (15)*/
	NOT_ON_ADC,   /* P2.6 LED (16) */
	NOT_ON_ADC,   /* P2.7 Button 1 (17) */
	NOT_ON_ADC,   /* P3.0 (18)*/
	NOT_ON_ADC,   /* P3.1 (19)*/
	NOT_ON_ADC,   /* P3.2 (20)*/
	NOT_ON_ADC,   /* P3.3 (21)*/
	NOT_ON_ADC,   /* P3.4 (22)*/
	NOT_ON_ADC,   /* P3.5 (23)*/
	NOT_ON_ADC,   /* P3.6 (24)*/
	NOT_ON_ADC,   /* P3.7 (25)*/
	NOT_ON_ADC,   /* P1.0 LED (26)*/
	NOT_ON_ADC,   /* P1.1 Button 2 (27)*/
    NOT_ON_ADC,   /* P1.2 (28)*/
    NOT_ON_ADC,   /* P1.3 (29)*/
	NOT_ON_ADC,   /* P1.4 (30)*/
	NOT_ON_ADC    /* P1.5 (31)*/
};

#endif
