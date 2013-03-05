/**************************************/
/*bridge.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#ifndef	_HALL_H_
#define	_HALL_H_


/**************************************/
/*#define	DO_TEST*/
/**************************************/

/**************************************/

/**************************************/
#define	NUM_PHASE	6
/**************************************/



/**************************************/
#define	PHASE_1	0
#define	PHASE_2	1
#define	PHASE_3	2
#define	PHASE_4	3
#define	PHASE_5	4
#define	PHASE_6	5
/**************************************/

/**************************************/
void	initializeHall( void );

unsigned char	getPhase( unsigned char hall_1, unsigned char hall_2, unsigned char hall_3 );

unsigned char	getFowardPhase( unsigned char phase );
unsigned char	getBackwardPhase( unsigned char phase );

/**************************************/



/**************************************/
#ifdef	DO_TEST

void	Test_getPhase( void );
void	Test_getFowardPhase( void );
void	Test_getBackwardPhase( void );

#endif
/**************************************/

#endif	/*_HALL_H_*/
