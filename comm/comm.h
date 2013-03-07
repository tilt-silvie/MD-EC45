/****************************************/
/*comm.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_COMM_H_
#define	_COMM_H_


/****************************************/
/*#define	_DEBUG*/
/****************************************/

/****************************************/
#define	MAX_NUM_OF_DATA	10

#define	COMMAND_TEST_SINWAVE	0x01
#define	COMMAND_TEST_BANGBANG	0x02

typedef struct	Order{
	unsigned char	command;
	unsigned char 	data[MAX_NUM_OF_DATA];
}Order;
/****************************************/


/****************************************/
void	initializeComm( void );
Order	fetchOrder( void );
/****************************************/

#endif	/*_COMM_H_*/
