/*
 * uart.c
 *
 *  Created on: 4 déc. 2017
 *      Author: Wistaro
 */
 
/*Needeed libs*/
#include "ezdsp5535.h"
#include "ezdsp5535_led.h" //for leds
#include"ezdsp5535_lcd.h" //for the lcd
#include "ezdsp5535_gpio.h" //gpio
#include "ezdsp5535_i2c.h" //i2c
#include "ezdsp5535_i2s.h"
#include "csl_i2s.h"
#include "stdio.h"
#include "sound.h"
#include "uart.h"

void main() {
	
	char i;

	 /* Initialize BSL, LCD screen and GPIO */
	
	EZDSP5535_init( );
	EZDSP5535_OSD9616_init( );
	EZDSP5535_LED_init( );

	/*Dsplay random things on the OSD LCD screen*/
	
	for(i=0;i<22;i++){
		    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces to center the text
	}
	EZDSP5535_OSD9616_printLetter(0xff,0x81,0x81,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0x00,0x7F,0x00,0x00);  // I
	EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01); //T
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0x81,0x81,0xff);  //

	/*Main loop*/ 
	while(1){
		i = uartListen();
		
		EZDSP5535_LED_toggle(2);
		EZDSP5535_waitusec(1000);
		
		if(i != 0){			
			generateSound(i,100,1);
			
			/*some random effects on LEDS, just for fun :) */
			EZDSP5535_LED_toggle(0);
			EZDSP5535_LED_toggle(3);
			i = 0;
		}
	}

}


