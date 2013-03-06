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
static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase );
static unsigned char	getFowardExcitationPhase( unsigned char hall_phase ); 
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


static unsigned char	getFowardExcitationPhase( unsigned char hall_phase )
{
	switch( hall_phase ){
	case	HALL_PHASE_1:
		return	EXCITATION_PHASE_2;

	case	HALL_PHASE_2:
		return	EXCITATION_PHASE_3;

	case	HALL_PHASE_3:
		return	EXCITATION_PHASE_4;

	case	HALL_PHASE_4:
		return	EXCITATION_PHASE_5;

	case	HALL_PHASE_5:
		return	EXCITATION_PHASE_6;

	case	HALL_PHASE_6:
		return	EXCITATION_PHASE_1;

	default:
		return	EXCITATION_PHASE_BRAKE;
	}
}


static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase )
{
	switch( hall_phase ){
	case	HALL_PHASE_1:
		return	EXCITATION_PHASE_6;

	case	HALL_PHASE_2:
		return	EXCITATION_PHASE_5;

	case	HALL_PHASE_3:
		return	EXCITATION_PHASE_4;

	case	HALL_PHASE_4:
		return	EXCITATION_PHASE_3;

	case	HALL_PHASE_5:
		return	EXCITATION_PHASE_2;

	case	HALL_PHASE_6:
		return	EXCITATION_PHASE_1;

	default:
		return	EXCITATION_PHASE_BRAKE;
	}
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST
#endif
