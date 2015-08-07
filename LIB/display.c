/*
 * LCD Library for Stellaris/Tiva launchpads
 * All rights reserved.
 * Distributed under the BSD License
 * Copyright (c) 2015, Manolis Kiagias
 *
 * Based on ideas and code of the MSP430 Launchpad LCD Library
 * published in Co-Random thoughts blog:
 * http://cacheattack.blogspot.gr/2011/06/quick-overview-on-interfacing-msp430.html
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
 /*******************************************************************************/


#include "display.h"

//
// Pulse the EN bit LOW - HIGH - LOW
// To signal the LCD to accept the data/cmd
//

void pulseLCD()
{
	// Go Low -> High -> Low
	GPIOPinWrite(CMD_PORT_BASE, EN, 0);
	GPIOPinWrite(CMD_PORT_BASE, EN, EN);
	GPIOPinWrite(CMD_PORT_BASE, EN, 0);
}

//
// Set the RS to LOW
// Indicating incoming command
//

void setCmd() {
	GPIOPinWrite(CMD_PORT_BASE, RS,0);
}

//
// Set the RS to HIGH
// Indicating incoming data
//

void setData() {
	GPIOPinWrite(CMD_PORT_BASE, RS,RS);
}

//
// Send data byte in 4 bit mode
// High nibble is sent first
//

void sendByte(char byteToSend, int isData)
{
	if (isData)
		setData();
	else
		setCmd();
	SysCtlDelay(400);
	GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, byteToSend >>4);
	pulseLCD();
	GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, byteToSend);
	pulseLCD();
}

//
// For 16 columns, 2 rows LCD
// Select row / column for next character output
// Initial values are 0,0
//

void setCursorPositionLCD(char row, char col)
{
	char address;

	if (row == 0)
		address = 0;
	else if (row==1)
		address = 0x40;
	else if (row==2)
		address = 0x14;
	else if (row==3)
		address = 0x54;
	else
		address = 0;

	address |= col;

	sendByte(0x80 | address, FALSE);
}

//
// Clear the LCD
// and return to home position (0,0)
//

void clearLCD(void)
{
	sendByte(0x01, FALSE); // Clear screen
	sendByte(0x02, FALSE); // Back to home
	SysCtlDelay(30000);
}

//
// Return to home position (0,0)
//

void homeLCD(void) {
	sendByte(0x02, FALSE);
	SysCtlDelay(30000);
}


//
// Make block cursor visible
//

void setBlockCursorLCD(void) {
	sendByte(0x0F, FALSE);
}

//
// Make line cursor visible
//

void setLineCursorLCD(void) {
	sendByte(0x0E, FALSE);
}

//
// Display cursor on screen
//

void cursorOnLCD(void) {
	sendByte(0x0E, FALSE);
}

//
// Hide cursor from screen
//

void cursorOffLCD(void) {
	sendByte(0x0C, FALSE);
}

//
// Turn off LCD
//

void displayOffLCD(void) {
	sendByte(0x08, FALSE);
}

//
// Turn on LCD
//

void displayOnLCD(void) {
	sendByte(0x0C, FALSE);
}

//
// Initialize the LCD
// Performs the following functions:
// Activates selected ports
// Designates ports as outputs
// Pulls all output pins to low
// Waits for LCD warmup
// Sets LCD for 4 pin communication
// Sets two lines display
// Hides the cursor
// Sets insert mode
// Clears the screen
//

void initLCD(void)
{
	//
	// set the MSP pin configurations
	// and bring them to low
	//
	SysCtlPeripheralEnable(DATA_PERIPH);
	SysCtlPeripheralEnable(CMD_PERIPH);
	GPIOPinTypeGPIOOutput(DATA_PORT_BASE,  ALLDATAPINS);
	GPIOPinTypeGPIOOutput(CMD_PORT_BASE, ALLCONTROLPINS);
	GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS ,0);
	GPIOPinWrite(CMD_PORT_BASE, ALLCONTROLPINS ,0);

	//
	// wait for the LCM to warm up and reach
	// active regions. Remember MSPs can power
	// up much faster than the LCM.
	//

	SysCtlDelay(10000);

	//
	// initialize the LCM module
	// Set 4-bit input
	//

	setCmd();
	SysCtlDelay(15000);
	GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, 0b0010);
	pulseLCD();
	GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, 0b0010);
	pulseLCD();
	sendByte(0x28,FALSE);  // Set two lines
	cursorOffLCD();       // Cursor invisible
	sendByte(0x06, FALSE); // Set insert mode
	clearLCD();
}

//
// Print the text
// on the screen
//

void printLCD(char *text)
{
	char *c;
	c = text;

	while ((c != 0) && (*c != 0))
	{
		sendByte(*c, TRUE);
		c++;
	}
}
