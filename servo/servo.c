/*
 * File:   servo.c
 * Author: Master
 *
 * Created on 2013/04/04 20:27
 */

#include	<timer.h>
#include	"servo.h"
#include	"encorder/encorder.h"

/*******************************************/
static void	initializeTimer( void );
/*******************************************/

/*******************************************/

extern void	initializeServo( void )
{
	initializeEncorder();
	initializeTimer();
}


static void	initializeTimer( void )
{
	unsigned int	config;

	config	=	T1_ON & T1_IDLE_STOP & T1_GATE_OFF & T1_PS_1_8 & 
				T1_SYNC_EXT_OFF & T1_SOURCE_INT;

	OpenTimer1( config, 10000 );
	ConfigIntTimer1( T1_INT_PRIOR_3 & T1_INT_ON );
}
/*******************************************/



/*******************************************/
void _ISR	_T1Interrupt( void )
{
	signed long			count_enc, speed;
	static unsigned int	i;


	_T1IF	= 0;

	count_enc	= readCountEncorder();
	speed	= count_enc - 32768;
	resetCountEncorder();

	if( i < 50 ){
		i++;
	}else{
		i	= 0;
		printf("%ld\n",speed);
	}

}
/*******************************************/
