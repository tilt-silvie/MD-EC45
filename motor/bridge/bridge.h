/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#ifndef	_BRIDGE_H_
#define	_BRIDGE_H_


/**************************************/
/*#define	DO_TEST*/
/**************************************/



/**************************************/
#define	BRIDGE_1	1
#define	BRIDGE_2	2
#define	BRIDGE_3	3
/**************************************/


/**************************************/
void	initializeBridge( void );
unsigned char	driveBridge( unsigned char phase, unsigned long duty_percent );
/**************************************/


/**************************************/
#ifdef	DO_TEST

void	Test_pinAssign( void );
void	Test_calculatePR( void );
void	Test_driveBridge( void );

#endif
/**************************************/

#endif	/*_BRIDGE_H_*/
