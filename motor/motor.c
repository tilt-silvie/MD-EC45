/****************************************/
/*motor.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	<xc.h>
#include	<math.h>
#include	"motor.h"
#include	"../pin_assign.h"
#include	"hall/hall.h"
#include	"bridge/bridge.h"
#include	"../assert/assert.h"


/**************************************/
#define	TARGET_VOLTAGE_TOO_HIGH	0xFFFF
/**************************************/


/**************************************/
/*グローバル変数*/
static unsigned char	G_direction_rotation = BRAKE;
static unsigned long	G_duty = 50;
/**************************************/


/**************************************/
static void	exciteWinding( unsigned char direction_rotation, unsigned long duty );
static unsigned char	getDirection( double voltage );
static unsigned long	getDuty( double target_voltage, double supply_voltage );
static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase );
static unsigned char	getFowardExcitationPhase( unsigned char hall_phase ); 
/**************************************/


/**************************************/
void	initializeMotor( void )
{
	initializeHall();
	initializeBridge();
	G_direction_rotation	= CCW;

#ifdef	_DEBUG
	/*Test_getFowardExcitationPhase();*/
	/*Test_getBackwardExcitationPhase();*/
	/*Test_getDicretion();*/
	/*Test_getDuty();*/
	Test_driveMotor();
#endif

}
/**************************************/


/**************************************/
unsigned char	driveMotor( double voltage )
{
	/*TODO : supply_voltage はAD変換で随時取得するように*/

	double	supply_voltage = 12.0;

	G_direction_rotation	= getDirection( voltage );
	G_duty	= getDuty( voltage, supply_voltage );
	exciteWinding( G_direction_rotation, G_duty );

	return	0;
}


static unsigned char	getDirection( double voltage )
{
	return	(voltage < 0) ? CCW : CW;
}


static unsigned long	getDuty( double target_voltage, double supply_voltage )
{
	target_voltage	= fabs( target_voltage );

	if( supply_voltage < 0 ){
		return	TARGET_VOLTAGE_TOO_HIGH;
	}

	if( target_voltage > supply_voltage ){
		return	TARGET_VOLTAGE_TOO_HIGH;
	}
	
	return	target_voltage / supply_voltage * 100;
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

void	Test_driveMotor( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_driveMotor**\n");
	printf("--Test start!--\n");

	/* **** */
	ASSERT( driveMotor( 12.0 ) == 0 )
	ASSERT( driveMotor( 6 ) == 0 )
	/* **** */

	printf("-- Test Passed! --\n");
}


void	Test_getFowardExcitationPhase( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getFowardExcitationPhase**\n");
	printf("--Test start!--\n");

	/* **** */
	ASSERT( getFowardExcitationPhase( HALL_PHASE_1 ) == EXCITATION_PHASE_2 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_2 ) == EXCITATION_PHASE_3 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_3 ) == EXCITATION_PHASE_4 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_4 ) == EXCITATION_PHASE_5 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_5 ) == EXCITATION_PHASE_6 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_6 ) == EXCITATION_PHASE_1 )
	ASSERT( getFowardExcitationPhase( 255 ) == EXCITATION_PHASE_BRAKE )
	/* **** */

	printf("-- Test Passed! --\n");
}


void	Test_getBackwardExcitationPhase( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getBackwardExcitationPhase**\n");
	printf("--Test start!--\n");

	/* **** */
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_1 ) == EXCITATION_PHASE_6 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_2 ) == EXCITATION_PHASE_1 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_3 ) == EXCITATION_PHASE_2 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_4 ) == EXCITATION_PHASE_3 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_5 ) == EXCITATION_PHASE_4 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_6 ) == EXCITATION_PHASE_5 )
	ASSERT( getBackwardExcitationPhase( 255 ) == EXCITATION_PHASE_BRAKE )
	/* **** */

	printf("-- Test Passed! --\n");
}


void	Test_getDicretion( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getDicretion**\n");
	printf("--Test start!--\n");

	/* **** */
	ASSERT( getDirection( 12.0 ) == CW )
	ASSERT( getDirection( -12.0 ) == CCW )
	ASSERT( getDirection( 10 ) == CW )
	ASSERT( getDirection( -10 ) == CCW )
	ASSERT( getDirection( 0.0 ) == CW )
	ASSERT( getDirection( 0 ) == CW )
	/* **** */

	printf("-- Test Passed! --\n");
}


void	Test_getDuty( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("\n\n**Test_getDuty**\n");
	printf("--Test start!--\n");

	/* **** */
	ASSERT( getDuty( 10, 10 ) == 100 )
	ASSERT( getDuty( -10, 10 ) == 100 )
	ASSERT( getDuty( 0, 10 ) == 0 )
	ASSERT( getDuty( 10, 5 ) == TARGET_VOLTAGE_TOO_HIGH )
	ASSERT( getDuty( 10, 0 ) == TARGET_VOLTAGE_TOO_HIGH )
	/* **** */

	printf("-- Test Passed! --\n");
}

#endif
