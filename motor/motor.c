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
/*グローバル変数*/
static unsigned char	G_direction_rotation = BRAKE;
/**************************************/


/**************************************/
static unsigned char	getNexPhase( unsigned char now_phase, unsigned char direction_rotation );
/**************************************/


/**************************************/
void	initializeMotor( void )
{
	initializeHall();
	initializeBridge();
	G_direction_rotation	= BRAKE;
}
/**************************************/


/**************************************/
void _ISR	_CNInterrupt( void )
{
	_CNIF	= 0;

	unsigned char	now_phase, next_phase;

	now_phase = getPhaseHall( HALL_1, HALL_2, HALL_3 );

	driveBridge( next_phase, 20 );

#ifdef	DO_TEST
	printf("now phase = %d : next phase = %d\n", now_phase, next_phase );
#endif
}


static unsigned char	getNexPhase( unsigned char now_phase, unsigned char direction_rotation )
{
	switch( direction_rotation ){
	case	CW:
		return	getFowardPhaseHall( now_phase );
	case	CCW:
		return	getBackwardPhaseHall( now_phase );
	case	BRAKE:
		return	PHASE_BRAKE;
	default:
		return	PHASE_BRAKE;
	}
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST
#endif
