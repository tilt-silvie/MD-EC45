/****************************************/
/*comm.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_COMM_H_
#define	_COMM_H_


/****************************************/
#define	_DEBUG
/****************************************/


/****************************************/
#define	UART_BAUDRATE	57600
/****************************************/

/****************************************/
#define	MAX_DATA	10

#define	COMMAND_NULL			0x00
#define	COMMAND_TEST_SINWAVE	0x01
#define	COMMAND_TEST_BANGBANG	0x02
#define	COMMAND_SPEED_OPENLOOP	0x03

typedef struct	Order{
	unsigned char	command;
	char 	data[MAX_DATA];
}Order;
/****************************************/


/****************************************/
void	initializeComm( void );
Order	fetchOrder( void );
/****************************************/



/****************************************/
/*テストコード*/
#ifdef	_DEBUG
void	Test_fetchOrder( void );
#endif
/****************************************/

#endif	/*_COMM_H_*/
