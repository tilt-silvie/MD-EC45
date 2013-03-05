/**************************************/
/*hall.c*/
/*Author	: Makito Ishikura*/
/**************************************/

#include	"hall.h"

/**************************************/
unsigned char	getPhase( unsigned char hall_1, unsigned char hall_2, unsigned char hall_3 )
{
	unsigned char	phase_conbined;

	phase_conbined	= (hall_1 << 2) | (hall_2 << 1) | (hall_3 << 0);

	switch( phase_conbined ){
	case	0b001:
		return	PHASE_1;

	case	0b101:
		return	PHASE_2;

	case	0b100:
		return	PHASE_3;

	case	0b110:
		return	PHASE_4;

	case	0b010:
		return	PHASE_5;

	case	0b011:
		return	PHASE_6;

	default:
		return	0xFF;
	}
}

/**************************************/
