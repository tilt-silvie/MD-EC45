/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#include	<xc.h>
#include	<pwm12.h>
#include	"peripheral_pin.h"
#include	"bridge.h"
#include	"../../pin_assign.h"

/*#define	_DEBUG*/
#ifdef	_DEBUG
#include	"../../assert/assert.h"
#endif



/**************************************/
static void	initializePWM( void );
static unsigned int	calculatePTPER( unsigned int duty_int );
/**************************************/

/**************************************/
#ifdef	_DEBUG
static void	test_calculatePTPER( void );
#endif
/**************************************/



/**************************************/
static unsigned int	G_max_pr2 = 1600;
/**************************************/


/**************************************/
void	initializeBridge( void )
{
	initializePWM();

#ifdef	_DEBUG
	test_calculatePTPER();
#endif
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
extern void	driveBridge( unsigned char phase )
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

	return	0;
}



extern void	setDutyBridge( unsigned int duty_int )
{
	/*
	 *Dutyを設定する関数
	 *    duty_int	: 0	~ 0xFFFF
	 *    PWM Duty	: 0 ~ 100	[%]
	 */

	unsigned int	calculated_ptper;

	calculated_ptper	= calculatePTPER( duty_int );

	SetDCMCPWM1( 1, calculated_ptper, 0);
	SetDCMCPWM1( 2, calculated_ptper, 0);
	SetDCMCPWM1( 3, calculated_ptper, 0);
}



static unsigned int	calculatePTPER( unsigned int duty_int )
{
	const unsigned int	MAX_PTPER_ = 1600, LIMIT_PTPER_ = 1520;
    unsigned int    calculated_ptper;

    calculated_ptper	= (unsigned long)duty_int * MAX_PTPER_ / 0xFFFF;
	if( calculated_ptper >= LIMIT_PTPER_ ){
		calculated_ptper	= LIMIT_PTPER_;
	}

	return	calculated_ptper;
}


/**************************************/



/**************************************/
/*テストケース*/
#ifdef	_DEBUG


static void	test_calculatePTPER( void )
{
	unsigned int	i;
	for( i=0; i<0xFFFF; i++ );

	ASSERT( calculatePTPER( 0		)	== 0	);
	ASSERT( calculatePTPER( 0xFFFF	)	== 1520	);
	ASSERT( calculatePTPER( 32768	)	== 800	);
}

#endif



/**************************************/

