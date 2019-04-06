/*
 * main.c
 */

/*global inclusion*/
#include "ezdsp5535.h"
#include "ezdsp5535_led.h" //for leds
#include"ezdsp5535_lcd.h" //for the lcd
#include "ezdsp5535_gpio.h" //gpio
#include "ezdsp5535_i2c.h" //i2c
#include "ezdsp5535_i2s.h"
#include "csl_i2s.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "sound.h"
#include "uart.h"
#include "wavetable.h"

/*define */


/*prog start here*/


void main() {
	
	char i;

	/*DISPLAY TIPLANET*/

	EZDSP5535_OSD9616_init( );
	EZDSP5535_LED_init( );
	//EZDSP5535_LED_setall(0xff);

	for(i=0;i<22;i++){
		    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces
	}
	EZDSP5535_OSD9616_printLetter(0xff,0x81,0x81,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0x00,0x7F,0x00,0x00);  // I
	EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01); //T
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0xff,0xff,0xff);  //
	EZDSP5535_OSD9616_printLetter(0xff,0x81,0x81,0xff);  //

	 /* Initialize BSL */
	 EZDSP5535_init( );

	while(1){
		i = uartListen();
		EZDSP5535_LED_toggle(2);
		EZDSP5535_waitusec(1000);
		if(i != 0){
			generateSound(i,100,1);
			EZDSP5535_LED_toggle(0);
			EZDSP5535_LED_toggle(3);
			i = 0;
		}
	}


		/* Initialize OLED display */
	    EZDSP5535_OSD9616_init( );

	    EZDSP5535_OSD9616_send(0x00,0x2e);  // Deactivate Scrolling

	    Uint16 cmd[10];    // For multibyte commands
	    /* Fill page 0 */
	    EZDSP5535_OSD9616_send(0x00,0x00);   // Set low column address
	    EZDSP5535_OSD9616_send(0x00,0x10);   // Set high column address
	    EZDSP5535_OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
	    for(i=0;i<128;i++)
	    {
	    	EZDSP5535_OSD9616_send(0x40,0xff);
	    }
	    /* Write to page 0 */
	    EZDSP5535_OSD9616_send(0x00,0x00);   // Set low column address
	    EZDSP5535_OSD9616_send(0x00,0x10);   // Set high column address
	    EZDSP5535_OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
	    for(i=0;i<22;i++)
	    {
	    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces
	    }
	    EZDSP5535_OSD9616_printLetter(0x32,0x49,0x49,0x26);  // S
	    EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01);  // T
	    EZDSP5535_OSD9616_printLetter(0x7F,0x30,0x0E,0x7F);  // N
	    EZDSP5535_OSD9616_printLetter(0x41,0x49,0x49,0x7F);  // E
	    EZDSP5535_OSD9616_printLetter(0x7F,0x06,0x06,0x7F);  // M
	    EZDSP5535_OSD9616_printLetter(0x3F,0x40,0x40,0x3F);  // U
	    EZDSP5535_OSD9616_printLetter(0x46,0x29,0x19,0x7F);  // R
	    EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01);  // T
	    EZDSP5535_OSD9616_printLetter(0x32,0x49,0x49,0x26);  // S
	    EZDSP5535_OSD9616_printLetter(0x7F,0x30,0x0E,0x7F);  // N
	    EZDSP5535_OSD9616_printLetter(0x00,0x7F,0x00,0x00);  // I

	    cmd[0] = 0x00;
	        cmd[1] = 0x29;  // Vertical and Right Horizontal Scroll
	        cmd[2] = 0x00;  // Dummy byte
	        cmd[3] = 0x00;  // Define start page address
	        cmd[4] = 0x03;  // Set time interval between each scroll step
	        cmd[5] = 0x01;  // Define end page address
	        cmd[6] = 0x01;  // Vertical scrolling offset
	        EZDSP5535_OSD9616_multiSend( cmd, 7 );
	        EZDSP5535_OSD9616_send(0x00,0x2f);

	/*EZDSP5535_LED_init( );
	EZDSP5535_LED_setall( 0x00 );

	EZDSP5535_LED_toggle( 0 );
	EZDSP5535_waitusec( 100000 );
	EZDSP5535_LED_toggle( 1 );
	EZDSP5535_waitusec( 100000 );
	EZDSP5535_LED_toggle( 2 );
	EZDSP5535_waitusec( 100000 );
	EZDSP5535_LED_toggle( 3 );
	EZDSP5535_waitusec( 100000 );
	*/




}
