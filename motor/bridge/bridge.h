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
#define	OFF			0
#define	HIGH_SIDE	1
#define	LOW_SIDE	2
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
