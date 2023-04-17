/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   This file modified 2023-03-02 by Andrej Miladinovic and Seolli Kim

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "snake.h"  /* Declatations for these snake game */
#include <stdio.h>
#include <stdlib.h>

//game state
int state = 1;

int main(void) { // taken from lab
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	
	display_init();
	display_pixel();
	
	
	
	labinit(); /* Do any lab-specific initialization */

	//Written by Seolli and Andrej below

	void start_Screen(){ //the first screen that is shown 
		clear_display();

		display_string(1, "Welcome to Snake");
		display_string(2, "SW 3: Start");
		display_string(3, "");

		int sw = getsw();

		if (sw == 0x4) { //sw3
			clear_display();
			state = 2;
		}
		

		display_update();
	}

	void end() { //game over screen
		char score = (char)pointscounter;
		clear_display();

		display_string(0, " GAME OVER ");
		display_string(1, "Score:");
		display_string(2, itoaconv(pointscounter)); //converting to string
		display_string(3, "Play again? SW2 ");
		
		int sw = getsw();

		if(sw == 0x2){ // sw2
			clear_display();
			state = 2;
		}

		display_update();

	}

	while( 1 )
	{
		if (state == 1) {
			start_Screen();
		} else if(state == 2) {
	  	labinit(); /* Do lab-specific things again and again */
	  	while(state == 2) {
		labwork();
		//display_image(96, icon);
	  }
		}else if(state == 4) {
			end();
		}

	}

	return 0;
}
