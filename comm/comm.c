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
	initializeUart( 9, 8, FCY*2, UART_BAUDRATE);

#ifdef	_DEBUG
	Test_fetchOrder();
#endif
}
/**************************************/


/**************************************/
Order	fetchOrder( void )
{
	unsigned char	num_of_data = 5;
	unsigned char	i, data_update = 0;
	char	buffer[MAX_NUM_OF_DATA];

	Order	order;
	
	order.command	= COMMAND_NULL;

	if( receivePacket(buffer) == DATA_IS_UPDATED ){
		order.command	= buffer[0];

		for( i = 0; i < num_of_data; i++ ){
			order.data[i]	= buffer[i+1];
		}
	}else{
		order.command	= COMMAND_NULL;
	}

	return	order;
}
/**************************************/



/**************************************/
/*テストコード*/
/**************************************/
#ifdef	_DEBUG

void	Test_fetchOrder( void )
{
	__delay_ms(100);

	printf("\n\n**Test_fetchOrder**\n");
	printf("--Test start!--\n");

	/* **** */

	Order	order;
	while( 1 ) {
		order	= fetchOrder();

		switch( order.command ){
		case	COMMAND_TEST_SINWAVE:
			printf("Rcvd:TEST_SINWAVE\n");
			break;
		case	COMMAND_TEST_BANGBANG:
			printf("Rcvd:TEST_BANGBANG\n");
			break;

		default:
			break;
		}

		__delay_ms( 500 );
	}

	/* **** */

	printf("-- Test Passed! --\n");
}

#endif
