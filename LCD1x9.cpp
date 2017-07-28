/**********************************************************************
*
*    Author:		shondll (shondll_yahoo.com)
*    Company:		Olimex Ltd.
*    Date:			07/02/2011
*    File Version:	1.00
*    Description:	LCD 1x9 drtiver
*
**********************************************************************/
#include <cc430x513x.h>
//#include "GenericTypeDefs.h"
#include "LCD1x9.h"
#include "LCD1x9_mapping.h"
#include <string.h>

/* DEFINE LOCAL TYPES HERE */

/* DEFINE LOCAL CONSTANTS HERE */
//#define LCD1x9_SCL_TRIS TRISCbits.TRISC3
#define LCD1x9_SCL_DIR_OUT     P3DIR |= (0x40);
#define LCD1x9_SCL_DIR_IN      P3DIR &= (~0x40);
//#define LCD1x9_SCL_LAT  LATCbits.LATC3
#define LCD1x9_SCL_OUT_HIGH    P3OUT |= (0x40);
#define LCD1x9_SCL_OUT_LOW     P3OUT &= (~0x40);
//#define LCD1x9_SCL_PORT PORTCbits.RC3
#define LCD1x9_SCL_PORT        (P3IN & 0x40)

//#define LCD1x9_SDA_TRIS TRISCbits.TRISC4
#define LCD1x9_SDA_DIR_OUT    P3DIR |= (0x80);
#define LCD1x9_SDA_DIR_IN     P3DIR &= (~0x80);
//#define LCD1x9_SDA_LAT  LATCbits.LATC4
#define LCD1x9_SDA_OUT_HIGH   P3OUT |= (0x80);
#define LCD1x9_SDA_OUT_LOW    P3OUT &= (~0x80);
//#define LCD1x9_SDA_PORT PORTCbits.RC4
#define LCD1x9_SDA_PORT       (P3IN & 0x80)

#define LCD1x9_SLAVE_ADDR       0x70


#define ACK 0
#define NACK 1

/* DECLARE EXTERNAL VARIABLES HERE */

/* DEFINE LOCAL MACROS HERE */

/* DEFINE LOCAL VARIABLES HERE */
static BYTE lcdBitmap[20]; // 40segments * 4 = 160px, 160 / 8 = 20bytes

/* DECLARE EXTERNAL VARIABLES HERE */

/* DECLARE LOCAL FUNCTIONS HERE */
static void local_I2C_Delay(void);
static void local_I2C_Start(void);
static void local_I2C_Stop(void);
static char local_I2C_WriteByte(BYTE data); // returns ack state

/* DEFINE FUNCTIONS HERE */

/******************************************************************************
* Description: LCD1x9_Initialize(..) - initializes pins and registers of the LCD1x9
*				Also lights up all segments
* Input: 	none
* Output: 	none
* Return:	0 if sucessfully initialized, -1 if error occured
*******************************************************************************/
signed char LCD1x9_Initialize(void)
{
	char result = 0, i;

	// the idea is to toggle pins as inputs/outputs to emulate I2C open drain mode of operation!
	//LCD1x9_SDA_TRIS = 1;
        LCD1x9_SDA_DIR_IN;
	//LCD1x9_SCL_TRIS = 1;
        LCD1x9_SCL_DIR_IN;

	//LCD1x9_SDA_LAT = 0;
        LCD1x9_SDA_OUT_LOW;
	//LCD1x9_SCL_LAT = 0;
        LCD1x9_SCL_OUT_LOW;

	local_I2C_Delay();
	if( !(LCD1x9_SCL_PORT && LCD1x9_SDA_PORT) )
		return -1;

	local_I2C_Start();
	result |= local_I2C_WriteByte(LCD1x9_SLAVE_ADDR | 0x00);
	result |= local_I2C_WriteByte(0xC8); // mode register
	result |= local_I2C_WriteByte(0xF0); // blink register
	result |= local_I2C_WriteByte(0xE0); // device select register
	result |= local_I2C_WriteByte(0x00); // pointer register

	// light up all the segments, initialize the local display buffer as well
	for(i = 0; i < 20; i++) {
		result |= local_I2C_WriteByte(0xFF);
		lcdBitmap[i] = 0xFF;
	}

	local_I2C_Stop();

	return (result ? -1 : 0);
}


/******************************************************************************
* Description: LCD1x9_enableSegment(..) - enables a segment in the display buffer
*		Note: Does not actually light up the segment, have to call the 'LCD1x9_Update(..)'
* Input: 	comIndex - backplate index
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_enableSegment(BYTE comIndex, BYTE bitIndex)
{
	if(bitIndex >= 40)
		return;

	comIndex &= 0x3;

	if(bitIndex & 0x1)
		comIndex |= 0x4;

	bitIndex >>= 1;

	lcdBitmap[bitIndex] |= 0x80 >> comIndex;
}

/******************************************************************************
* Description: LCD1x9_disableSegment(..) - disables a segment in the display buffer
*		Note: Does not actually lights off the segment, have to call the 'LCD1x9_Update(..)'
* Input: 	comIndex - backplate index
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_disableSegment(BYTE comIndex, BYTE bitIndex)
{
	if(bitIndex >= 40)
		return;

	comIndex &= 0x3;

	if(bitIndex & 0x1)
		comIndex |= 0x4;

	bitIndex >>= 1;

	lcdBitmap[bitIndex] &= ~(0x80 >> comIndex);
}

/******************************************************************************
* Description: LCD1x9_Update(..) - disables a segment in the display buffer
*		Note: Does not actually lights off the segment, have to call the 'LCD1x9_Update(..)'
* Input: 	comIndex - backplate index
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_Update(void)
{
	BYTE i;

	local_I2C_Start();
	local_I2C_WriteByte(LCD1x9_SLAVE_ADDR | 0x00);
	local_I2C_WriteByte(0xE0); // device select register
	local_I2C_WriteByte(0x00); // pointer register

	// send the local buffer to the device
	for(i = 0; i < 20; i++)
		local_I2C_WriteByte(lcdBitmap[i]);

	local_I2C_Stop();
}

/******************************************************************************
* Description: LCD1x9_Write(..) - writes a string to the display
* Input: 	string - the string to write, no more than 9 characters
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_Write(char *string)
{
	BYTE data, length, index, i;
	WORD bitfield;
	BYTE com, bit;

	length = strlen(string);
	if(length > 9)
		return;

	index  = 0;
	/* fill out all characters on display */
	for (index = 0; index < 9; index++) {
		if (index < length) {
			data = (BYTE)string[index];
		} else {
			data = 0x20; // fill with spaces if string is shorter than display
		}

		data -= 0x20;
		bitfield = LCDAlphabet[data];

		for (i = 0; i < 16; i++) {
			bit = LCD1x9.Text[index].bit[i];
			com = LCD1x9.Text[index].com[i];

			if (bitfield & ((WORD)1 << i)) {
				LCD1x9_enableSegment(com, bit);
			} else {
				LCD1x9_disableSegment(com, bit);
			}
		}
	}

	LCD1x9_Update();
}

/******************************************************************************
* Description: LCD1x9_Write(..) - writes a string to the display
* Input: 	string - the string to write, no more than 9 characters
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_WriteROM(ROM char* string)
{
	BYTE data, length, index, i;
	WORD bitfield;
	BYTE com, bit;

	length = (BYTE)strlen(string);

	index  = 0;
	/* fill out all characters on display */
	for (index = 0; index < 9; index++) {
		if (index < length) {
			data = (BYTE)string[index];
		} else {
			data = 0x20; // fill with spaces if string is shorter than display
		}

		data -= 0x20;
		bitfield = LCDAlphabet[data];

		for (i = 0; i < 16; i++) {
			bit = LCD1x9.Text[index].bit[i];
			com = LCD1x9.Text[index].com[i];

			if (bitfield & ((WORD)1 << i)) {
				LCD1x9_enableSegment(com, bit);
			} else {
				LCD1x9_disableSegment(com, bit);
			}
		}
	}

	LCD1x9_Update();
}

/* local functions */

static void local_I2C_Delay(void)
{
	BYTE d = 10;
	while(d--) {
		asm("NOP");
	}
}

static void local_I2C_Start(void)
{
	//LCD1x9_SDA_TRIS = 0;
        LCD1x9_SDA_DIR_OUT;
        LCD1x9_SDA_OUT_LOW;
	local_I2C_Delay();
	//LCD1x9_SCL_TRIS = 0;
        LCD1x9_SCL_DIR_OUT;
        LCD1x9_SCL_OUT_LOW;
	local_I2C_Delay();

}

static void local_I2C_Stop(void)
{
	//LCD1x9_SDA_TRIS = 0;
        LCD1x9_SDA_DIR_OUT;
        LCD1x9_SDA_OUT_LOW;
	local_I2C_Delay();
	//LCD1x9_SCL_TRIS = 1;
        LCD1x9_SCL_DIR_IN;
	local_I2C_Delay();
	//LCD1x9_SDA_TRIS = 1;
        LCD1x9_SDA_DIR_IN;
	local_I2C_Delay();
}

// returns ack state, 0 means acknowledged
static char local_I2C_WriteByte(BYTE data)
{
	char i;

	// send the 8 bits
	for(i = 0; i < 8; i++) {
	  //LCD1x9_SDA_TRIS = (data & 0x80) ? 1 : 0;
          if(data & 0x80){  LCD1x9_SDA_DIR_IN;  }
          else{             LCD1x9_SDA_DIR_OUT; }
	  data <<= 1;
	  local_I2C_Delay();
	  //LCD1x9_SCL_TRIS = 1;
          LCD1x9_SCL_DIR_IN;
	  local_I2C_Delay();
	  //LCD1x9_SCL_TRIS = 0;
          LCD1x9_SCL_DIR_OUT;
          LCD1x9_SCL_OUT_LOW;
	}

	// read the ack
	//LCD1x9_SDA_TRIS = 1;
        LCD1x9_SDA_DIR_IN;
	local_I2C_Delay();
	//LCD1x9_SCL_TRIS = 1;
        LCD1x9_SCL_DIR_IN;
	local_I2C_Delay();
	i = LCD1x9_SDA_PORT;
	//LCD1x9_SCL_TRIS = 0;
        LCD1x9_SCL_DIR_OUT;
        LCD1x9_SCL_OUT_LOW;
	local_I2C_Delay();

	return i;
}

