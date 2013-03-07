/****************************************/
/*comm.c*/
/*Author	: Makito Ishikura*/
/****************************************/

#include	"comm.h"
#include	"uart/uart_dsPIC33F.h"
#include	"../assert/assert.h"

#define	FCY	39613750
#include	<libpic30.h>

/**************************************/
/*Packet_robo ライブラリ使用のため*/
#include	"packet_robo/packet_robo.h"

extern void	send1byte( unsigned char data )
{
	putcUart( data );
}

extern unsigned char	get1byte( unsigned char* data )
{
	return	( getcUart(data) == 0 ) ? BUF_NOT_EMPTY : BUF_EMPTY;
}

/**************************************/
void	initializeComm( void )
{
	initializeUart( 9, 8, FCY*2, 57600);
}
/**************************************/


/**************************************/
Order	fetchOrder( void )
{
	unsigned char	num_of_data = 5;
	unsigned char	buffer[0]={0}, i;
	Order	order;
	
	while( receivePacket(buffer) == 0 );

	order.command	= buffer[0];
	for( i = 0; i < num_of_data; i++ ){
		order.data[i]	= buffer[i+1];
	}

	return	order;
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
	/* **** */

	printf("-- Test Passed! --\n");
}

#endif
