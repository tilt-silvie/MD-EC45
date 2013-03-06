/****************************************/
/*motor.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_MOTOR_H_
#define	_MOTOR_H_

/****************************************/
#define	DO_TEST
/****************************************/


/****************************************/
#define	CW		0
#define	CCW		1
#define	BRAKE	2
/****************************************/



/****************************************/
void	initializeMotor( void );
unsigned char	driveMotor( double voltage );
/****************************************/

/**************************************/
/*テストコード*/
/**************************************/
#ifdef	DO_TEST
void	Test_getFowardExcitationPhase( void );
void	Test_getBackwardExcitationPhase( void );
#endif

#endif	/*_MOTOR_H_*/
