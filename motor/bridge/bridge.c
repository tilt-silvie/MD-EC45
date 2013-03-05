/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#include	<xc.h>
#include	"peripheral_pin.h"
#include	"bridge.h"
#include	"../../pin_assign.h"

#ifdef	DO_TEST
#include	<stdio.h>
#endif

/**************************************/
void	driveBridgeOff		( unsigned char num_of_bridge )
{
	switch( num_of_bridge ){
	case	BRIDGE_1:
		ENABLE_1	= 0;
		break;

	case	BRIDGE_2:
		ENABLE_2	= 0;
		break;

	case	BRIDGE_3:
		ENABLE_3	= 0;
		break;

	default:
		ENABLE_1	= 0;
		ENABLE_2	= 0;
		ENABLE_3	= 0;
		break;
	}
}


void	driveBridgeHighSide	( unsigned char num_of_bridge )
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
	

void	driveBridgeLowSide	( unsigned char num_of_bridge )
{
	switch( num_of_bridge ){
	case	BRIDGE_1:
		PWM_MODE_1	= RP_NULL;
		PWM_1		= 0;
		ENABLE_1	= 1;
		break;

	case	BRIDGE_2:
		PWM_MODE_2	= RP_NULL;
		PWM_3		= 0;
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


#endif
