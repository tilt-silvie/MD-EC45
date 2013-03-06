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
void _ISR	_CNInterrupt( void )
{
	_CNIF	= 0;

	unsigned char	phase;
	phase = getPhaseHall( HALL_1, HALL_2, HALL_3 );
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST
#endif
