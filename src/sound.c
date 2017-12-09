/*
 * sound.c
 *
 *  Created on: 7 déc. 2017
 *      Author: Willliam
 */

#include "ezdsp5535_i2c.h" //i2c
#include "ezdsp5535_i2s.h"
#include "csl_i2s.h"
#include "ezdsp5535.h"
#include "math.h"
#define AIC3204_I2C_ADDR 0x18


Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint16 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = regval;                // 8-bit Register Data

    EZDSP5535_waitusec( 300 );

    return EZDSP5535_I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}

void generateSound(Uint16 freq, Uint16 duration, float volume){

		EZDSP5535_I2C_init( );

		/*STARTING GENERATING SIGNAL*/
		 /* Pre-generated sine wave data, 16-bit signed samples */
		    Int16 sinetable[48] = {
		        0x0000, 0x10b4, 0x2120, 0x30fb, 0x3fff, 0x4dea, 0x5a81, 0x658b,
		        0x6ed8, 0x763f, 0x7ba1, 0x7ee5, 0x7ffd, 0x7ee5, 0x7ba1, 0x76ef,
		        0x6ed8, 0x658b, 0x5a81, 0x4dea, 0x3fff, 0x30fb, 0x2120, 0x10b4,
		        0x0000, 0xef4c, 0xdee0, 0xcf06, 0xc002, 0xb216, 0xa57f, 0x9a75,
		        0x9128, 0x89c1, 0x845f, 0x811b, 0x8002, 0x811b, 0x845f, 0x89c1,
		        0x9128, 0x9a76, 0xa57f, 0xb216, 0xc002, 0xcf06, 0xdee0, 0xef4c
		    };
			
		    Int16 sec, msec;
		    Int16 sample;

		    /* Configure AIC3204 */
		    AIC3204_rset( 0,  0x00 );  // Select page 0
		    AIC3204_rset( 1,  0x01 );  // Reset codec
		    EZDSP5535_waitusec(1000);  // Wait 1ms after reset
		    AIC3204_rset( 0,  0x01 );  // Select page 1
		    AIC3204_rset( 1,  0x08 );  // Disable crude AVDD generation from DVDD
		    AIC3204_rset( 2,  0x01 );  // Enable Analog Blocks, use LDO power
		    AIC3204_rset( 123,0x05 );  // Force reference to power up in 40ms
		    EZDSP5535_waitusec(50000); // Wait at least 40ms
		    AIC3204_rset( 0,  0x00 );  // Select page 0

		    /* PLL and Clocks config and Power Up  */
		    AIC3204_rset( 27, 0x0d );  // BCLK and WCLK are set as o/p; AIC3204(Master)
		    AIC3204_rset( 28, 0x00 );  // Data ofset = 0
		    AIC3204_rset( 4,  0x03 );  // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
		    AIC3204_rset( 6,  0x07 );  // PLL setting: J=7
		    AIC3204_rset( 7,  0x06 );  // PLL setting: HI_BYTE(D=1680)
		    AIC3204_rset( 8,  0x90 );  // PLL setting: LO_BYTE(D=1680)
		    AIC3204_rset( 30, 0x88 );  // For 32 bit clocks per frame in Master mode ONLY
		                               // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
		    AIC3204_rset( 5,  0x91 );  // PLL setting: Power up PLL, P=1 and R=1
		    EZDSP5535_waitusec(10000); // Wait for PLL to come up
		    AIC3204_rset( 13, 0x00 );  // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
		    AIC3204_rset( 14, 0x80 );  // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
		    AIC3204_rset( 20, 0x80 );  // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
		    AIC3204_rset( 11, 0x82 );  // Power up NDAC and set NDAC value to 2
		    AIC3204_rset( 12, 0x87 );  // Power up MDAC and set MDAC value to 7
		    AIC3204_rset( 18, 0x87 );  // Power up NADC and set NADC value to 7
		    AIC3204_rset( 19, 0x82 );  // Power up MADC and set MADC value to 2

		    /* DAC ROUTING and Power Up */
		    AIC3204_rset( 0,  0x01 );  // Select page 1
		    AIC3204_rset( 12, 0x08 );  // LDAC AFIR routed to HPL
		    AIC3204_rset( 13, 0x08 );  // RDAC AFIR routed to HPR
		    AIC3204_rset( 0,  0x00 );  // Select page 0
		    AIC3204_rset( 64, 0x02 );  // Left vol=right vol
		    AIC3204_rset( 65, 0x00 );  // Left DAC gain to 0dB VOL; Right tracks Left
		    AIC3204_rset( 63, 0xd4 );  // Power up left,right data paths and set channel
		    AIC3204_rset( 0,  0x01 );  // Select page 1
		    AIC3204_rset( 16, 0x00 );  // Unmute HPL , 0dB gain
		    AIC3204_rset( 17, 0x00 );  // Unmute HPR , 0dB gain
		    AIC3204_rset( 9 , 0x30 );  // Power up HPL,HPR
		    EZDSP5535_waitusec(100 );  // Wait

		    /* ADC ROUTING and Power Up */
		    AIC3204_rset( 0,  0x01 );  // Select page 1
		    AIC3204_rset( 52, 0x30 );  // STEREO 1 Jack
		                               // IN2_L to LADC_P through 40 kohm
		    AIC3204_rset( 55, 0x30 );  // IN2_R to RADC_P through 40 kohmm
		    AIC3204_rset( 54, 0x03 );  // CM_1 (common mode) to LADC_M through 40 kohm
		    AIC3204_rset( 57, 0xc0 );  // CM_1 (common mode) to RADC_M through 40 kohm
		    AIC3204_rset( 59, 0x00 );  // MIC_PGA_L unmute
		    AIC3204_rset( 60, 0x00 );  // MIC_PGA_R unmute
		    AIC3204_rset( 0,  0x00 );  // Select page 0
		    AIC3204_rset( 81, 0xc0 );  // Powerup Left and Right ADC
		    AIC3204_rset( 82, 0x00 );  // Unmute Left and Right ADC
		    AIC3204_rset( 0,  0x00 );  // Select page 0
		    EZDSP5535_waitusec(100 );  // Wait

		    /* Initialize I2S */
		    EZDSP5535_I2S_init();

		    /* Play Tone for 5 seconds*/
		    for ( sec = 0 ; sec < 1 ; sec++ )
		    {
		        for ( msec = 0 ; msec < freq ; msec++ )
		        {
		            for ( sample = 0 ; sample < freq ; sample++ )
		            {
		                /* Write 16-bit left channel Data */
		                EZDSP5535_I2S_writeLeft( sinetable[sample]);

		                /* Write 16-bit right channel Data */
		                EZDSP5535_I2S_writeRight(sinetable[sample]);
		            }
		        }
		    }
		    EZDSP5535_I2S_close();    // Disble I2S
		    AIC3204_rset( 0,  0x00 );  // Select page 0
		    AIC3204_rset( 1,  0x01 );  // Reset codec
}





