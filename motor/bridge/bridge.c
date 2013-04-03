/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#include	<xc.h>
#include	<pwm12.h>
#include	"peripheral_pin.h"
#include	"bridge.h"
#include	"../../pin_assign.h"

#ifdef	DO_TEST
#include	<stdio.h>
#endif

/**************************************/
static void	initializePWM( void );
static unsigned int	calculatePR( unsigned long duty_percent );
static void	driveBridgeOff		( unsigned char num_of_bridge );
static void	driveBridgeHighSide	( unsigned char num_of_bridge );
static void	driveBridgeLowSide	( unsigned char num_of_bridge );
/**************************************/



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
	unsigned int    period, sptime;
	unsigned int	config1, config2, config3;

	period  = 799;  /* (Fcy / (Fpwm*PreScale)) - 1 */
	sptime  = 0;    /* ?? */

	config1	= PWM1_EN & PWM1_IDLE_STOP & PWM1_OP_SCALE1 & PWM1_IPCLK_SCALE1 &
                PWM1_MOD_FREE;
	config2 = PWM1_MOD1_COMP & PWM1_PEN1H & PWM1_PEN1L
			& PWM1_MOD2_COMP & PWM1_PEN2H & PWM1_PEN2L
			& PWM1_MOD3_COMP & PWM1_PEN3H & PWM1_PEN3L;
	config3 = PWM1_SEVOPS1 & PWM1_OSYNC_TCY & PWM1_UEN;

	OpenMCPWM1( period, sptime, config1, config2, config3);


	SetMCPWM1DeadTimeGeneration( PWM1_DTAPS1 & PWM1_DTA10 ); /*Deadtime = 250ns*/ 
	P1DTCON2	= 0x0000;
}


/**************************************/
unsigned char	driveBridge( unsigned char phase, unsigned long duty_percent )
{
	switch( phase ){
	case	EXCITATION_3_2:
		OverrideMCPWM1( PWM1_POUT_2H & PWM1_POUT2H_INACT &
						PWM1_POUT_2L & PWM1_POUT2L_ACT	 &
						PWM1_POUT_1H & PWM1_POUT1H_INACT &
						PWM1_POUT_1L & PWM1_POUT1L_INACT );
		break;
			
	case	EXCITATION_1_2:
		OverrideMCPWM1( PWM1_POUT_2H & PWM1_POUT2H_INACT &
						PWM1_POUT_2L & PWM1_POUT2L_ACT	 &
						PWM1_POUT_3H & PWM1_POUT3H_INACT &
						PWM1_POUT_3L & PWM1_POUT3L_INACT );
		break;
			
	case	EXCITATION_1_3:
		OverrideMCPWM1( PWM1_POUT_3H & PWM1_POUT3H_INACT &
						PWM1_POUT_3L & PWM1_POUT3L_ACT	 &
						PWM1_POUT_2H & PWM1_POUT2H_INACT &
						PWM1_POUT_2L & PWM1_POUT2L_INACT );
		break;
			
	case	EXCITATION_2_3:
		OverrideMCPWM1( PWM1_POUT_3H & PWM1_POUT3H_INACT &
						PWM1_POUT_3L & PWM1_POUT3L_ACT	 &
						PWM1_POUT_1H & PWM1_POUT1H_INACT &
						PWM1_POUT_1L & PWM1_POUT1L_INACT );
		break;
			
	case	EXCITATION_2_1:
		OverrideMCPWM1( PWM1_POUT_1H & PWM1_POUT1H_INACT &
						PWM1_POUT_1L & PWM1_POUT1L_ACT	 &
						PWM1_POUT_3H & PWM1_POUT3H_INACT &
						PWM1_POUT_3L & PWM1_POUT3L_INACT );
		break;
			
	case	EXCITATION_3_1:
		OverrideMCPWM1( PWM1_POUT_1H & PWM1_POUT1H_INACT &
						PWM1_POUT_1L & PWM1_POUT1L_ACT	 &
						PWM1_POUT_2H & PWM1_POUT2H_INACT &
						PWM1_POUT_2L & PWM1_POUT2L_INACT );
		break;

	case	EXCITATION_BRAKE:
		OverrideMCPWM1( PWM1_POUT_1L & PWM1_POUT1L_ACT	&
						PWM1_POUT_2L & PWM1_POUT2L_ACT	&
						PWM1_POUT_3L & PWM1_POUT3L_ACT	);
		break;

	default:
		OverrideMCPWM1( PWM1_POUT_1L & PWM1_POUT1L_ACT	&
						PWM1_POUT_2L & PWM1_POUT2L_ACT	&
						PWM1_POUT_3L & PWM1_POUT3L_ACT	);
		break;
	}

	/*SetDCOC1PWM( calculatePR( duty_percent ) );*/

	return	0;
}



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
		OverrideMCPWM1( PWM1_POUT_1H & PWM1_POUT_1L 
						& PWM1_POUT1H_INACT & PWM1_POUT1L_INACT );
		break;

	case	BRIDGE_2:
		OverrideMCPWM1( PWM1_POUT_2H & PWM1_POUT_2L 
						& PWM1_POUT2H_INACT & PWM1_POUT2L_INACT );
		break;

	case	BRIDGE_3:
		OverrideMCPWM1( PWM1_POUT_3H & PWM1_POUT_3L 
						& PWM1_POUT3H_INACT & PWM1_POUT3L_INACT );
		break;

	default:
		OverrideMCPWM1( PWM1_POUT_1H & PWM1_POUT_1L 
						& PWM1_POUT_2H & PWM1_POUT_2L
						& PWM1_POUT_3H & PWM1_POUT_3L 
						& PWM1_POUT1H_INACT & PWM1_POUT1L_INACT 
						& PWM1_POUT2H_INACT & PWM1_POUT2L_INACT 
						& PWM1_POUT3H_INACT & PWM1_POUT3L_INACT );
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


void	Test_driveBridge( void )
{
	unsigned char	phase;
	unsigned long	i;

	for( i = 0; i < 1000000; i++ );
	printf("**Test_driveBridge**\n\n");
	for( i = 0; i < 5000000; i++ );

	for( phase = 1; phase <= 6; phase ++ ){
		driveBridge( phase, 50 );
		printf("phase = %d\n", phase );
		for( i = 0; i < 10000000; i++ );
	}
}



#endif
