#ifndef	_PIN_ASSIGN_H_
#define	_PIN_ASSIGN_H_

/*---------------------------------*/

#define	LED_1	_LATB2

/*---------------------------------*/
/*bridge.c*/
#define	ENABLE_1	_LATB10
#define	ENABLE_2	_LATB12
#define	ENABLE_3	_LATB14
#define	PWM_1	_LATB11
#define	PWM_2	_LATB13
#define	PWM_3	_LATB15
#define	PWM_MODE_1	_RP11R	
#define	PWM_MODE_2	_RP13R	
#define	PWM_MODE_3	_RP15R
/*---------------------------------*/



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

