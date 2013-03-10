/****************************************/
/*motor.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	<xc.h>
#include	<stdlib.h>
#include	<math.h>
#include	"motor.h"
#include	"../pin_assign.h"
#include	"hall/hall.h"
#include	"bridge/bridge.h"

#define	FCY	39613750
#include	<libpic30.h>

/**************************************/
#define	SUPPLY_VOLTAGE_IS_UNDER_THE_GND	0xFFFF
/**************************************/


/****************************************/
#define	_DEBUG
#include	"../assert/assert.h"
/****************************************/
/**************************************/
/*グローバル変数*/
static unsigned char	G_direction_rotation = BRAKE;
static unsigned long	G_duty = 50;
/**************************************/


/**************************************/
static void	exciteWinding( unsigned char direction_rotation, unsigned long duty );
static unsigned char	getDirection( signed int voltage );
static unsigned long	getDuty( signed int target_voltage, signed int supply_voltage );
static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase );
static unsigned char	getFowardExcitationPhase( unsigned char hall_phase ); 
/**************************************/


/**************************************/
void	initializeMotor( void )
{
	initializeHall();
	initializeBridge();
	G_direction_rotation	= BRAKE;
	G_duty	= 0;
	exciteWinding( G_direction_rotation, G_duty );

#ifdef	_DEBUG
	Test_getFowardExcitationPhase();
	Test_getBackwardExcitationPhase();
	Test_getDicretion();
	Test_getDuty();
	Test_driveMotor();
#endif

}
/**************************************/


/**************************************/
unsigned char	driveMotor( signed int motor_millivolt )
{
	/*TODO : supply_voltage はAD変換で随時取得するように*/

	signed int	supply_voltage = 12000;

	G_direction_rotation	= getDirection( motor_millivolt );
	G_duty	= getDuty( motor_millivolt, supply_voltage );
	exciteWinding( G_direction_rotation, G_duty );

	return	0;
}


static unsigned char	getDirection( signed int voltage )
{
	return	(voltage < 0) ? CCW : CW;
}


static unsigned long	getDuty( signed int target_voltage, signed int supply_voltage )
{
	unsigned long	target_voltage_l; /* int型のままだとオーバーフローするので */ 

	target_voltage_l	= abs( target_voltage );

	if( supply_voltage <= 0 ){
		return	SUPPLY_VOLTAGE_IS_UNDER_THE_GND;
	}
	if( target_voltage > supply_voltage ){
		return	100;
	}
	
	return	target_voltage_l * 100 / supply_voltage;
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
		next_phase	= EXCITATION_BRAKE;
		break;
	default:
		next_phase	= EXCITATION_BRAKE;
		break;
	}

	driveBridge( next_phase, duty );

}
/**************************************/



/**************************************/
void _ISR	_CNInterrupt( void )
{
	/*
	 *NOTE : DEBUG出力なし時の動作時間計測結果
	 *2013/03/06 21:32 16[us]程度
	 */

	_CNIF	= 0;

	LED_1	= 1; /*動作時間計測用*/ 

	exciteWinding( G_direction_rotation, G_duty );

	LED_1	= 0; /*動作時間計測用*/ 
}


static unsigned char	getFowardExcitationPhase( unsigned char hall_phase )
{
	switch( hall_phase ){
	case	HALL_PHASE_1:
		return	EXCITATION_1_2;

	case	HALL_PHASE_2:
		return	EXCITATION_1_3;

	case	HALL_PHASE_3:
		return	EXCITATION_2_3;

	case	HALL_PHASE_4:
		return	EXCITATION_2_1;

	case	HALL_PHASE_5:
		return	EXCITATION_3_1;

	case	HALL_PHASE_6:
		return	EXCITATION_3_2;

	default:
		return	EXCITATION_BRAKE;
	}
}


static unsigned char	getBackwardExcitationPhase( unsigned char hall_phase )
{
	switch( hall_phase ){
	case	HALL_PHASE_1:
		return	EXCITATION_2_1;

	case	HALL_PHASE_2:
		return	EXCITATION_3_1;

	case	HALL_PHASE_3:
		return	EXCITATION_3_2;

	case	HALL_PHASE_4:
		return	EXCITATION_1_2;

	case	HALL_PHASE_5:
		return	EXCITATION_1_3;

	case	HALL_PHASE_6:
		return	EXCITATION_2_3;

	default:
		return	EXCITATION_BRAKE;
	}
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
void	Test_driveMotor_sinWave( signed int max_voltage, unsigned char num_loop, unsigned long period_ms )
{
/*
 *    [>モータをサイン関数に法って動かす関数<]
 *    const double	PI_2_ = 6.28, STEP_ = 0.0628;
 *
 *    unsigned char	i;
 *    unsigned long	delay;
 *    signed int	voltage;
 *
 *    [>周期が短すぎると危険なため，制限をかける(500ms)<]
 *    if( period_ms < 500 ){
 *        period_ms	= 500;
 *    }
 *    delay	= period_ms / 100;
 *
 *    for( i = 0; i < num_loop; i++ ){
 *        double	rad;
 *
 *        for( rad = 0.0; rad < PI_2_; rad+= STEP_ ){
 *            voltage	= max_voltage * sin( rad );
 *            driveMotor( voltage );
 *            __delay_ms( delay );
 *        }
 *    }
 */
}


void	Test_driveMotor_bangbang( signed int voltage, unsigned char num_loop, unsigned long period_ms )
{
	/*モータのCW/CCWを切り替える実験*/

	unsigned char	i;
	unsigned long	delay;

	/*周期が短すぎると危険なため，制限をかける(500ms)*/
	if( period_ms < 500 ){
		period_ms	= 500;
	}
	delay	= period_ms / 2;

	for( i = 0; i < num_loop; i++ ){
		driveMotor( voltage );
		__delay_ms( delay );
		driveMotor( -voltage );
		__delay_ms( delay );
	}

	driveMotor( 0.0 );
}
#ifdef	_DEBUG

void	Test_driveMotor( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	puts("**Test_driveMotor**");

	/* **** */

	/* **** */

}


void	Test_getFowardExcitationPhase( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	puts("**Test_getFowardExcitationPhase**");

	/* **** */
	ASSERT( getFowardExcitationPhase( HALL_PHASE_1 ) == EXCITATION_1_2 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_2 ) == EXCITATION_1_3 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_3 ) == EXCITATION_2_3 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_4 ) == EXCITATION_2_1 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_5 ) == EXCITATION_3_1 )
	ASSERT( getFowardExcitationPhase( HALL_PHASE_6 ) == EXCITATION_3_2 )
	ASSERT( getFowardExcitationPhase( 255 ) == EXCITATION_BRAKE )
	/* **** */

}


void	Test_getBackwardExcitationPhase( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	puts("**Test_getBackwardExcitationPhase**");

	/* **** */
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_1 ) == EXCITATION_2_1 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_2 ) == EXCITATION_3_1 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_3 ) == EXCITATION_3_2 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_4 ) == EXCITATION_1_2 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_5 ) == EXCITATION_1_3 )
	ASSERT( getBackwardExcitationPhase( HALL_PHASE_6 ) == EXCITATION_2_3 )
	ASSERT( getBackwardExcitationPhase( 255 ) == EXCITATION_BRAKE )
	/* **** */

}


void	Test_getDicretion( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	puts("**Test_getDicretion**");

	/* **** */
	ASSERT( getDirection( 12.0 ) == CW )
	ASSERT( getDirection( -12.0 ) == CCW )
	ASSERT( getDirection( 10 ) == CW )
	ASSERT( getDirection( -10 ) == CCW )
	ASSERT( getDirection( 0.0 ) == CW )
	ASSERT( getDirection( 0 ) == CW )
	/* **** */

}


void	Test_getDuty( void )
{
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	puts("**Test_getDuty**");

	/* **** */
	ASSERT( getDuty( 10, 10 ) == 100 )
	ASSERT( getDuty( -10, 10 ) == 100 )
	ASSERT( getDuty( 0, 10 ) == 0 )
	ASSERT( getDuty( 10, 5 ) == 100 )
	ASSERT( getDuty( 5, 10 ) == 50 )
	ASSERT( getDuty( 5, 15 ) == 33 )
	ASSERT( getDuty( 10, 0 ) == SUPPLY_VOLTAGE_IS_UNDER_THE_GND )
	/* **** */

}

#endif
