/*
 * File:   main.c
 * Author: Master
 *
 * Created on 2012/07/20, 18:13
 */

#define	FCY	39613750

#include	<xc.h>
#include	<libpic30.h>
#include	"uart_dsPIC33F/uart_dsPIC33F.h"
#include	"main.h"
#include	"pin_assign.h"

#include	"motor/hall/hall.h"

/********************************************************/

int main(void) 
{
	initialize( );

	initializeUart( 9, 8, FCY*2, 9600);
	Test_getPhase();

	while( 1 );
	
	return	0;
}



/********************************************************/



/********************************************************/
void	initialize( void )
{
	initializeOsc( );
	initializeIO( );
}


void	initializeOsc( void )
{
	RCONbits.SWDTEN	= 0;

	_PLLPOST	= 0b00; /* N2: PLL出力分周 = 2 */ 
	_PLLPRE	= 0b0000;  /* N1:PLL入力プリスケーラ = 2*/  
	PLLFBD	= 0x0029; /* M : PLL倍率 = 43 */ 

	while( !OSCCONbits.LOCK ); /* waiting PLL Lock */ 
}


void	initializeIO( void )
{
	PORTA	= 0x0000;
	TRISA	= 0x0000;

	PORTB	= 0x0000;
	TRISB	= 0x0000;
}


/********************************************************/
