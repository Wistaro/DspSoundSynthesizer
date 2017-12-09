/*
 * uart.c
 *
 *  Created on: 7 déc. 2017
 *      Author: Wistaro
 */
#include "ezdsp5535.h"
#include "csl_gpio.h"
#include "ezdsp5535_gpio.h"
#include "ezdsp5535_uart.h"
#include "stdio.h"

void uartPutString(const char* msg, Uint16 ret);
void uartPutVar(char var);

char uartListen(){
	 char rx;

	    /* Enable UART to FTDI chip (115200 bauds)*/
	    EZDSP5535_GPIO_init();
	    EZDSP5535_GPIO_setDirection( 15, GPIO_OUT );
	    EZDSP5535_GPIO_setOutput( 15, 0 );

	    printf("	Waiting for a new letter...\n");

	    /* Open Uart Handle */
	    EZDSP5535_UART_open( );

	    while(1)
	    {
	        /* Waiting for RX */
	        EVM5515_UART_getChar( &rx );   // Read 1 byte

	        /* Send message */
	        uartPutString("OK, you pressed ",0);
	        uartPutVar(rx);
	        uartPutString("",1);

	        if(rx != 0){ //if a key is pressed, we return to the main and play a tone
	        	return rx;
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
		EVM5515_UART_putChar( 10 );   // Write LF
		
	}


}

void uartPutVar(char var){
	EVM5515_UART_putChar(var);
}

