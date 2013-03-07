/****************************************/
/*comm.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	"comm.h"
#include	"uart/uart_dsPIC33F.h"
#include	"../assert/assert.h"

#define	FCY	39613750
#include	<libpic30.h>


void	initializeComm( void )
{
	initializeUart( 9, 8, FCY*2, 57600);
}


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
	/* **** */

	printf("-- Test Passed! --\n");
}

#endif
