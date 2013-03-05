#ifndef	_PIN_ASSIGN_H_
#define	_PIN_ASSIGN_H_

/*---------------------------------*/

#define	LED_1	_LATB2

/*---------------------------------*/
/*hall.c*/
#define HALL_1  _RB4
#define HALL_2  _RA3
#define HALL_3  _RA2
#define INITIALIZE_HALL_1 \
	    _TRISB4 = 1;    _CN1IE  = 1;    _CN1PUE = 1;
#define INITIALIZE_HALL_2 \
	    _TRISA3 = 1;    _CN29IE = 1;    _CN29PUE    = 1;
#define INITIALIZE_HALL_3 \
	    _TRISA2 = 1;    _CN30IE = 1;    _CN30PUE    = 1;
/*---------------------------------*/




#endif	/*_PIN_ASSIGN_H_*/

