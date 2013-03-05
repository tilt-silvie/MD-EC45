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
void	driveBridgeOff		( unsigned char num_of_bridge );
void	driveBridgeHighSide	( unsigned char num_of_bridge );
void	driveBridgeLowSide	( unsigned char num_of_bridge );
/**************************************/




/**************************************/
#ifdef	DO_TEST

#endif
/**************************************/

#endif	/*_BRIDGE_H_*/
