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
static unsigned long	G_duty = 50;
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

	if( G_direction_rotation == BRAKE ){
		driveBridge( EXCITATION_PHASE_BRAKE, 0 );

	}else{
		unsigned char	now_phase, next_phase;

		now_phase = getPhaseHall( HALL_1, HALL_2, HALL_3 );

		if( G_direction_rotation == CW ){
			next_phase	= getFowardExcitationPhase( now_phase );
		}else{
			next_phase	= getBackwardExcitationPhase( now_phase );
		}
		driveBridge( next_phase, G_duty );
	}

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
