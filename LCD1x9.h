/**********************************************************************
*
*    Author:		shondll (shondll_yahoo.com)
*    Company:		Olimex Ltd.
*    Date:			07/02/2011
*    File Version:	1.00
*    Description:	LCD 1x9 drtiver
*
**********************************************************************/
#include <stdint.h>

#ifndef _LCD1x9_DRIVER_H
#define _LCD1x9_DRIVER_H

#define BYTE        uint8_t
//#define BYTE        unsigned char
#define WORD        int16_t
//#define WORD        int
#define ROM         const

/******************************************************************************
* Description: LCD1x9_Initialize(..) - initializes pins and registers of the LCD1x9
*				Also lights up all segments
* Input: 	none
* Output: 	none
* Return:	0 if sucessfully initialized, -1 if error occured
*******************************************************************************/
signed char LCD1x9_Initialize(void);

/******************************************************************************
* Description: LCD1x9_enableSegment(..) - enables a segment in the display buffer
*		Note: Does not actually light up the segment, have to call the 'LCD1x9_Update(..)'
* Input: 	comIndex - backplate index
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_enableSegment(BYTE comIndex, BYTE bitIndex);

/******************************************************************************
* Description: LCD1x9_disableSegment(..) - disables a segment in the display buffer
*		Note: Does not actually lights off the segment, have to call the 'LCD1x9_Update(..)'
* Input: 	comIndex - backplate index
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_disableSegment(BYTE comIndex, BYTE bitIndex);

/******************************************************************************
* Description: LCD1x9_Update(..) - disables a segment in the display buffer
*		Note: Does not actually lights off the segment, have to call the 'LCD1x9_Update(..)'
* Input: 	comIndex - backplate index
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_Update(void);

/******************************************************************************
* Description: LCD1x9_Write(..) - writes a string to the display
* Input: 	string - the string to write, no more than 9 characters
*			bitIndex - segment index
* Output: 	none
* Return:	none
*******************************************************************************/
void LCD1x9_Write(char *string);
void LCD1x9_WriteROM(ROM char* string); // same thing but with ROM string


#endif // _LCD1x9_DRIVER_H


