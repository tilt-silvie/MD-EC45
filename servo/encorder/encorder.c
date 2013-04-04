/*
 * File:   encorder.c
 * Author: Master
 *
 * Created on 2013/04/04 19:28
 */

#include	"encorder.h"
#include	<qei.h>

/****************************************/
extern void	initializeEncorder( void )
{
	unsigned int	config_1, config_2;

	config_1 =	QEI_DIR_SEL_QEB	& QEI_INT_CLK & QEI_INDEX_RESET_DISABLE &
				QEI_CLK_PRESCALE_1 & QEI_GATED_ACC_DISABLE &
				QEI_LOGIC_CONTROL_IO & QEI_INPUTS_NOSWAP & QEI_MODE_x4_MATCH &
				QEI_UP_COUNT & QEI_IDLE_STOP;
				 
	config_2 =	MATCH_INDEX_PHASEA_LOW & MATCH_INDEX_PHASEB_LOW & 
				POS_CNT_ERR_INT_DISABLE & QEI_QE_CLK_DIVIDE_1_128 & QEI_QE_OUT_ENABLE;
	RPINR14 = 0b0000011100000110;   /* RP7 is QEB input and RP6 is QEA input */
	_TRISB6 = 1;    _TRISB7  = 1;

	OpenQEI( config_1, config_2 );
}
/****************************************/


/****************************************/
extern unsigned int	readCountEncorder( void )
{

	return	ReadQEI();
}


extern void	resetCountEncorder( void )
{
	POSCNT	= 32768;
}
/****************************************/
