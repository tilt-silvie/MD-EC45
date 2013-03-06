/****************************************/
/*motor.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	<xc.h>
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
static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase );
static unsigned char	getFowardExcitationPhase( unsigned char hall_phase ); 
/**************************************/


/**************************************/
void	initializeMotor( void )
{
	initializeHall();
	initializeBridge();
	G_direction_rotation	= CCW;

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
	unsigned char	is_test_succeed = 0;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getFowardExcitationPhase**\n");

	/* **** */
	is_test_succeed	= ( getFowardExcitationPhase(HALL_PHASE_1) == EXCITATION_PHASE_2 ) ?1:0;
	is_test_succeed	= ( getFowardExcitationPhase(HALL_PHASE_2) == EXCITATION_PHASE_3 ) ?1:0;
	is_test_succeed	= ( getFowardExcitationPhase(HALL_PHASE_3) == EXCITATION_PHASE_4 ) ?1:0;
	is_test_succeed	= ( getFowardExcitationPhase(HALL_PHASE_4) == EXCITATION_PHASE_5 ) ?1:0;
	is_test_succeed	= ( getFowardExcitationPhase(HALL_PHASE_5) == EXCITATION_PHASE_6 ) ?1:0;
	is_test_succeed	= ( getFowardExcitationPhase(HALL_PHASE_6) == EXCITATION_PHASE_1 ) ?1:0;
	is_test_succeed	= ( getFowardExcitationPhase(0) == EXCITATION_PHASE_BRAKE ) ?1:0;
	/* **** */

	if( is_test_succeed ){
		printf( "Test Succeeded!\n");
	}else{
		printf( "Test Faild\n");
	}
}


void	Test_getBackwardExcitationPhase( void )
{
	unsigned long	i;
	unsigned char	is_test_succeed = 0;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getBackwardExcitationPhase**\n");

	/* **** */
	is_test_succeed	= ( getBackwardExcitationPhase(HALL_PHASE_1) == EXCITATION_PHASE_6 ) ?1:0;
	is_test_succeed	= ( getBackwardExcitationPhase(HALL_PHASE_2) == EXCITATION_PHASE_1 ) ?1:0;
	is_test_succeed	= ( getBackwardExcitationPhase(HALL_PHASE_3) == EXCITATION_PHASE_2 ) ?1:0;
	is_test_succeed	= ( getBackwardExcitationPhase(HALL_PHASE_4) == EXCITATION_PHASE_3 ) ?1:0;
	is_test_succeed	= ( getBackwardExcitationPhase(HALL_PHASE_5) == EXCITATION_PHASE_4 ) ?1:0;
	is_test_succeed	= ( getBackwardExcitationPhase(HALL_PHASE_6) == EXCITATION_PHASE_5 ) ?1:0;
	is_test_succeed	= ( getBackwardExcitationPhase(255) == EXCITATION_PHASE_BRAKE ) ?1:0;
	/* **** */

	if( is_test_succeed ){
		printf( "Test Succeeded!\n");
	}else{
		printf( "Test Faild\n");
	}
}
#endif
