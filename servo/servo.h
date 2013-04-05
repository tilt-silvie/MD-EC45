/*
 * File:   servo.h
 * Author: Master
 *
 * Created on 2013/04/04 20:27
 */

#ifndef	_SERVO_H_
#define	_SERVO_H_

/*******************************************/
extern void	initializeServo( void );
extern signed long	setReferenceServo( signed long deg_per_sec );
extern void	setGainServo( float kp, float ki, float kd );
/*******************************************/

#endif	/*_SERVO_H_*/
