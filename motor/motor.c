/****************************************/
/*motor.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	<xc.h>
#include	<stdlib.h>
#include	"motor.h"
#include	"../pin_assign.h"
#include	"hall/hall.h"
#include	"bridge/bridge.h"
#include	"../assert/assert.h"


/**************************************/
/*グローバル変数*/
static unsigned char	G_direction_rotation = BRAKE;
static unsigned long	G_duty = 50;
/**************************************/


/**************************************/
static void	exciteWinding( unsigned char direction_rotation, unsigned long duty );
static unsigned char	getDirection( double voltage );
static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase );
static unsigned char	getFowardExcitationPhase( unsigned char hall_phase ); 
/**************************************/


/**************************************/
void	initializeMotor( void )
{
	initializeHall();
	initializeBridge();
	G_direction_rotation	= CCW;

	Test_getFowardExcitationPhase();
	Test_getBackwardExcitationPhase();

}
/**************************************/


/**************************************/
unsigned char	driveMotor( double voltage )
{
	
	/*
	 *G_direction_rotation	= getDirection( voltage );
	 *G_duty	= getDuty( voltage, supply_voltage );
	 *exciteWinding( G_direction_rotation, G_duty );
	 */
}

static unsigned char	getDirection( double voltage )
{
	return	(voltage < 0) ? ? CCW : CW;
}

static void	exciteWinding( unsigned char direction_rotation, unsigned long duty )
{
	unsigned char	now_phase, next_phase;

	now_phase = getPhaseHall( HALL_1, HALL_2, HALL_3 );

	switch( direction_rotation ){
	case	CW:
		next_phase	= getFowardExcitationPhase( now_phase );
		break;
	case	CCW:
		next_phase	= getBackwardExcitationPhase( now_phase );
		break;
	case	BRAKE:
		next_phase	= EXCITATION_PHASE_BRAKE;
		break;
	default:
		next_phase	= EXCITATION_PHASE_BRAKE;
		break;
	}

	driveBridge( next_phase, duty );

#ifdef	_DEBUG
	printf("Direction = %d : now = %d, next  = %d\n", G_direction_rotation, now_phase, next_phase );
#endif
}
/**************************************/



/**************************************/
void _ISR	_CNInterrupt( void )
{
	_CNIF	= 0;
	exciteWinding( G_direction_rotation, G_duty );
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
		return	EXCITATION_PHASE_1;

	case	HALL_PHASE_3:
		return	EXCITATION_PHASE_2;

	case	HALL_PHASE_4:
		return	EXCITATION_PHASE_3;

	case	HALL_PHASE_5:
		return	EXCITATION_PHASE_4;

	case	HALL_PHASE_6:
		return	EXCITATION_PHASE_5;

	default:
		return	EXCITATION_PHASE_BRAKE;
	}
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	_DEBUG

void	Test_getFowardExcitationPhase( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getFowardExcitationPhase**\n");
	printf("\n--Test start!--\n");

	/* **** */
	ASSERT( getFowardExcitationPhase( HALL_PHASE_1 ) == EXCITATION_PHASE_2 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_2 ) == EXCITATION_PHASE_3 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_3 ) == EXCITATION_PHASE_4 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_4 ) == EXCITATION_PHASE_5 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_5 ) == EXCITATION_PHASE_6 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_6 ) == EXCITATION_PHASE_1 )
	ASSERT( getFowardExcitationPhase( 255 ) == EXCITATION_PHASE_BRAKE )
	/* **** */

	printf("\n-- Test Passed! --\n");
}


void	Test_getBackwardExcitationPhase( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getBackwardExcitationPhase**\n");
	printf("\n--Test start!--\n");

	/* **** */
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_1 ) == EXCITATION_PHASE_6 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_2 ) == EXCITATION_PHASE_1 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_3 ) == EXCITATION_PHASE_2 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_4 ) == EXCITATION_PHASE_3 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_5 ) == EXCITATION_PHASE_4 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_6 ) == EXCITATION_PHASE_5 )
	ASSERT( getBackwardExcitationPhase( 255 ) == EXCITATION_PHASE_BRAKE )
	/* **** */

	printf("\n-- Test Passed! --\n");
}


#endif
