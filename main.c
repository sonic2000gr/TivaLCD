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

/*
 *
 * Pin Connections:
 * PE4 [pin 5]  -> RS
 * PE5 [pin 6]  -> EN
 * PD0 [pin 23] -> D4
 * PD1 [pin 24] -> D5
 * PD2 [pin 25] -> D6
 * PD3 [pin 26] -> D7
 *
 * pin number in [] indicates
 * energia pin reference!
 *
 */

#include "display.h"
#include "driverlib/rom_map.h"

int main()
{
    SysCtlClockSet(SYSCTL_SYSDIV_8|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    initLCD();
	while(1) {
		printLCD("Tiva / Stellaris");
		setCursorPositionLCD(1,0);
		printLCD("LCD Display");
		SysCtlDelay(10000000);
		clearLCD();
		printLCD("16 characters");
		setCursorPositionLCD(1,0);
		printLCD("2 lines");
		SysCtlDelay(10000000);
		clearLCD();
	}
}
