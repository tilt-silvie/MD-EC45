/*
 * File:   main.h
 * Author: Master
 *
 * Created on 2012/07/20 18:16
 */


#ifndef	_MAIN_H_
#define	_MAIN_H_

#include	"config33f.h"


/********************************************************/
#define	LED_1	_LATB2
#define	BUTTON_1	_RB6
/********************************************************/


/********************************************************/
void	initialize( void );
void	initializeOsc( void );
void	initializeIO( void );
void	initializeTimer1( void );
/********************************************************/


#endif
