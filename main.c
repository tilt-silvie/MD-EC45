/*
 * File:   main.c
 * Author: Master
 *
 * Created on 2012/07/20, 18:13
 */

#define	FCY	39613750

#include	<xc.h>
#include	<libpic30.h>

#include	"main.h"
#include	"pin_assign.h"
#include	"motor/motor.h"
#include	"comm/comm.h"

#include	"assert/assert.h"
/********************************************************/


/********************************************************/
static void	driveMotorSinWave( Order order );
/********************************************************/

int main(void) 
{
	initialize( );
	initializeComm();
	initializeMotor();

	while( 1 );
	return	0;
}



/********************************************************/


/********************************************************/
static void	driveMotorSinWave( Order order )
{
	double			voltage		= 12.0 / 256 * order.data[0];
	unsigned char	num_loop	= order.data[1];
	unsigned long	period_ms	= order.data[2] * 1000;

	printf("num_loop = %3d\n", num_loop);
	Test_driveMotor_sinWave( voltage, num_loop, period_ms );
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



/********************************************************/
/*テストコード*/
#ifdef	_DEBUG
#endif


/********************************************************/



