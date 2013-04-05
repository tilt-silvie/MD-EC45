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
#include	"servo/servo.h"

#include	"assert/assert.h"
#include	"comm/uart/uart_dsPIC33F.h"


#include	"xprintf/xprintf.h"
/********************************************************/


/********************************************************/
static void	executeOrder( Order order );
static void	driveMotorSinWave( Order order );
static void	driveMotorBangbang( Order order );
static signed long	transSpeedCharToLong( signed char speed );
/********************************************************/

int main(void) 
{
	initialize( );
	initializeComm();
	initializeMotor();
	initializeServo();

	xdev_out( putcUart );

	Order	order;

	while( 1 ){
		order	= fetchOrder();
		executeOrder( order );
	}
}



/********************************************************/


/********************************************************/
static void	executeOrder( Order order )
{
	switch( order.command ){
	case	COMMAND_TEST_SINWAVE:
		driveMotorSinWave(order);
		break;

	case	COMMAND_TEST_BANGBANG:
		driveMotorBangbang(order);
		break;

	case	COMMAND_SPEED_PID:
		setReferenceServo( transSpeedCharToLong(order.data[0]) );
		break;

	default:
		break;
	}

}
/********************************************************/
static void	driveMotorSinWave( Order order )
{
	signed int		voltage		= order.data[0]	* 12000 / 128;
	unsigned char	num_loop	= order.data[1];
	unsigned long	period_ms	= order.data[2] * 1000;

	Test_driveMotor_sinWave( voltage, num_loop, period_ms );
}


static void	driveMotorBangbang( Order order )
{

	signed int		voltage		= order.data[0];
	unsigned char	num_loop	= order.data[1];
	unsigned long	period_ms	= order.data[2] * 1000;

	Test_driveMotor_bangbang( voltage*100, num_loop, period_ms );
}

static signed long	transSpeedCharToLong( signed char speed )
{
	signed long	speed_long;

	speed_long	= speed;
	speed_long	= 36000 * speed / 128;

	return	speed_long;
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



