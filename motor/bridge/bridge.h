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
#define	EXCITATION_BRAKE	0
#define	EXCITATION_3_2		32
#define	EXCITATION_1_2		12
#define	EXCITATION_1_3		13
#define	EXCITATION_2_3		23
#define	EXCITATION_2_1		21
#define	EXCITATION_3_1		31
/**************************************/



/**************************************/
#define	BRIDGE_1	1
#define	BRIDGE_2	2
#define	BRIDGE_3	3
/**************************************/


/**************************************/
void	initializeBridge( void );
unsigned char	driveBridge( unsigned char phase, unsigned long duty_percent );
extern void	setDutyBridge( unsigned int duty_int );
/**************************************/


/**************************************/
#ifdef	DO_TEST

void	Test_pinAssign( void );
void	Test_calculatePR( void );
void	Test_driveBridge( void );

#endif
/**************************************/

#endif	/*_BRIDGE_H_*/
