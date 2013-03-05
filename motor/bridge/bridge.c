/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#include	<xc.h>
#include	<timer.h>
#include	<outcompare.h>
#include	"peripheral_pin.h"
#include	"bridge.h"
#include	"../../pin_assign.h"

#ifdef	DO_TEST
#include	<stdio.h>
#endif


/**************************************/
static unsigned int	G_max_pr2 = 800;
/**************************************/



/**************************************/
void	initializeBridge( void )
{
	initializePWM();
}


static void	initializePWM( void )
{
	OpenTimer2( T2_ON & T2_IDLE_STOP & T2_GATE_OFF & T2_PS_1_1 & T2_SOURCE_INT,  800 - 1 ); /* 50kHz */ 
	OpenOC1( OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE, 0, 0 );
}


/**************************************/
static unsigned int	calculatePR( unsigned long duty_percent )
{
    unsigned int    calculated_pr;

    calculated_pr   = duty_percent * G_max_pr2 / 100;
	if( calculated_pr >= G_max_pr2 ){
		calculated_pr	= G_max_pr2 - 5;
	}

	return	calculated_pr;
}


/**************************************/

static void	driveBridgeOff		( unsigned char num_of_bridge )
{
	switch( num_of_bridge ){
	case	BRIDGE_1:
		ENABLE_1	= 0;
		PWM_MODE_1	= RP_NULL;
		PWM_1		= 0;
		break;

	case	BRIDGE_2:
		ENABLE_2	= 0;
		PWM_MODE_2	= RP_NULL;
		PWM_2		= 0;
		break;

	case	BRIDGE_3:
		ENABLE_3	= 0;
		PWM_MODE_3	= RP_NULL;
		PWM_3		= 0;
		break;

	default:
		ENABLE_1	= 0;
		ENABLE_2	= 0;
		ENABLE_3	= 0;
		break;
	}
}


static void	driveBridgeHighSide	( unsigned char num_of_bridge )
{
	switch( num_of_bridge ){
	case	BRIDGE_1:
		PWM_MODE_1	= RP_OC1;
		ENABLE_1	= 1;
		break;

	case	BRIDGE_2:
		PWM_MODE_2	= RP_OC1;
		ENABLE_2	= 1;
		break;

	case	BRIDGE_3:
		PWM_MODE_3	= RP_OC1;
		ENABLE_3	= 1;
		break;

	default:
		ENABLE_1	= 0;
		ENABLE_2	= 0;
		ENABLE_3	= 0;
		break;
	}
}
	

static void	driveBridgeLowSide	( unsigned char num_of_bridge )
{
	switch( num_of_bridge ){
	case	BRIDGE_1:
		PWM_MODE_1	= RP_NULL;
		PWM_1		= 0;
		ENABLE_1	= 1;
		break;

	case	BRIDGE_2:
		PWM_MODE_2	= RP_NULL;
		PWM_2		= 0;
		ENABLE_2	= 1;
		break;

	case	BRIDGE_3:
		PWM_MODE_3	= RP_NULL;
		PWM_3		= 0;
		ENABLE_3	= 1;
		break;

	default:
		ENABLE_1	= 0;
		ENABLE_2	= 0;
		ENABLE_3	= 0;
		break;
	}
}


/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST

void	Test_pinAssign( void ){
	unsigned long	i;

	while( 1 ){
		ENABLE_1	= 1;	ENABLE_2 = 1;	ENABLE_3 = 1;
		PWM_1		= 0;	PWM_2	= 0;	PWM_3 = 0;
		for( i = 0; i < 1000000; i++ );
		ENABLE_1	= 0;	ENABLE_2 = 0;	ENABLE_3 = 0;
		PWM_1		= 1;	PWM_2	= 1;	PWM_3 = 1;
		for( i = 0; i < 1000000; i++ );
	}
}


void	Test_driveBridgeOff( void )
{
	driveBridgeOff( BRIDGE_1 );
	driveBridgeOff( BRIDGE_2 );
	driveBridgeOff( BRIDGE_3 );
}


void	Test_driveBridgeHighSide( void )
{
	driveBridgeHighSide( BRIDGE_1 );
	driveBridgeHighSide( BRIDGE_2 );
	driveBridgeHighSide( BRIDGE_3 );
}


void	Test_driveBridgeLowSide( void )
{
	driveBridgeLowSide( BRIDGE_1 );
	driveBridgeLowSide( BRIDGE_2 );
	driveBridgeLowSide( BRIDGE_3 );
}


void	Test_calculatePR( void )
{
	unsigned long	duty, i;
	unsigned int	pr;

	for( i = 0; i < 10000; i++ );
	printf("**Test_calculatePR**\n\n");

	for( i = 0; i < 10000; i++ );

	for( duty = 0; duty <= 101; duty ++ ){
		pr	= calculatePR( duty );
		printf("duty = %3ld : pr = %3d\n", duty, pr );
		for( i = 0; i < 10000; i++ );
	}
}


#endif
