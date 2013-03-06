/****************************************/
/*motor.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	<xc.h>
#include	"motor.h"
#include	"../pin_assign.h"
#include	"hall/hall.h"
#include	"bridge/bridge.h"

#ifdef	DO_TEST
#include	<stdio.h>
#endif

/**************************************/
void	initializeMotor( void )
{
	initializeHall();
	initializeBridge();
}
/**************************************/


/**************************************/
void _ISR	_CNInterrupt( void )
{
	_CNIF	= 0;

	unsigned char	now_phase, next_phase;

	now_phase = getPhaseHall( HALL_1, HALL_2, HALL_3 );
	next_phase	= getFowardPhaseHall( now_phase );

	driveBridge( next_phase, 20 );

#ifdef	DO_TEST
	printf("now phase = %d : next phase = %d\n", now_phase, next_phase );
#endif
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST
#endif
