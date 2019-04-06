/*
 * uart.c
 *
 *  Created on: 7 déc. 2017
 *      Author: Willliam
 */
#include "ezdsp5535.h"
#include "csl_gpio.h"
#include "ezdsp5535_gpio.h"
#include "ezdsp5535_uart.h"
#include "stdio.h"

void uartPutString(const char* msg, Uint16 ret);
void uartPutVar(char var);

char uartListen(){
	 char rx = ' ';
	 char buffRx = ' ';

	    /* Enable UART to FTDI chip */
	    EZDSP5535_GPIO_init();
	    EZDSP5535_GPIO_setDirection( 15, GPIO_OUT );
	    EZDSP5535_GPIO_setOutput( 15, 0 );

	    printf("	Waiting for a new letter...\n");

	    /* Open Uart Handle */
	    EZDSP5535_UART_open( );
	    printf("ENTER THE MATRIX \n");

	    /* UART Test */
	    while(1)
	    {
	        /* Waitin for RX */
	        EVM5515_UART_getChar( &rx );   // Read 1 byte
	        buffRx = rx;
	        /* TX Message */
	        uartPutString("OK, you pressed ",0);
	        uartPutVar(buffRx);
	        uartPutString("",1);

	        if(buffRx != 0){
	        	uartPutString("AHEM ",0);
	        	generateSound(buffRx,100,1);
	        	//EZDSP5535_LED_toggle(0);
	        	//EZDSP5535_LED_toggle(3);
	        	buffRx = 0;

	        }
	    }

}

void uartPutString(const char* msg, Uint16 ret){

	Uint16 i = 0;
	Uint16 lg = strlen(msg);

	for(i = 0;i<=lg;i++){
		EVM5515_UART_putChar(msg[i]);
	}
	if(ret == 1){
		EVM5515_UART_putChar( 13 );   // Write CR
		EVM5515_UART_putChar( 10 );   // Write LF*/
	}


}

void uartPutVar(char var){
	EVM5515_UART_putChar(var);
}

