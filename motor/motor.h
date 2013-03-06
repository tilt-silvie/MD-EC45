/****************************************/
/*motor.h*/
/*Author	: Makito Ishikura*/
/****************************************/

#ifndef	_MOTOR_H_
#define	_MOTOR_H_


/****************************************/
/*#define	_DEBUG*/
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
#ifdef	_DEBUG
void	Test_driveMotor( void );
void	Test_getFowardExcitationPhase( void );
void	Test_getBackwardExcitationPhase( void );
void	Test_getDicretion( void );
void	Test_getDuty( void );
#endif

#endif	/*_MOTOR_H_*/