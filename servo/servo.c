/*
 * File:   servo.c
 * Author: Master
 *
 * Created on 2013/04/04 20:27
 */


#include	<timer.h>
#include	"servo.h"
#include	"encorder/encorder.h"
#include	"../motor/motor.h"

#define	_DEBUG
#include	"../assert/assert.h"
#include	"../xprintf/xprintf.h"
#include	"../pin_assign.h"


/*******************************************/
static void	initializeTimer( void );
static void	initializePID( void );
static signed int pid( signed int reference_input, signed int mesured_output );
/*******************************************/


/*******************************************/
static signed int	G_reference_deg_per_sec;
/*******************************************/


/*******************************************/

extern void	initializeServo( void )
{
	initializeEncorder();
	initializeTimer();
}


static void	initializeTimer( void )
{
	unsigned int	config;

	config	=	T1_ON & T1_IDLE_STOP & T1_GATE_OFF & T1_PS_1_8 & 
				T1_SYNC_EXT_OFF & T1_SOURCE_INT;

	OpenTimer1( config, 10000 );
	ConfigIntTimer1( T1_INT_PRIOR_3 & T1_INT_ON );
}
/*******************************************/


/*******************************************/
extern signed long	setReferenceServo( signed long deg_per_sec )
{
	signed long	measured_deg_per_sec;
	signed int	pulse_per_2ms;

	pulse_per_2ms			= deg_per_sec / 125;
	G_reference_deg_per_sec	= pulse_per_2ms;

	return	0;
}
/*******************************************/




/*******************************************/
extern void	setGainServo( float kp, float ki, float kd )
{
}
/*******************************************/


static signed int pid( signed int reference_input, signed int mesured_output )
{
	/*const unsigned int	KP_ = 3, KI_ = 0, KD_ = 0;*/
	const float	KP_ = 0.5, KI_ = 0.0, KD_ = 0.0;
	static signed long	err[3];
	static float	control_output[2];

	float delta_control_output;

	/*偏差履歴を更新*/
	err[2]	= err[1];
	err[1]	= err[0];
	err[0]	= reference_input - mesured_output;

	delta_control_output	 = KP_ * (err[0] - err[1]);
	delta_control_output	+= KI_ *  err[0];
	delta_control_output	+= KD_ * (err[0] - (2*err[1]) + err[2]);

	control_output[1]	= control_output[0];
	control_output[0]	= control_output[1] + delta_control_output;

	if( control_output[0] > 32767.0 ){
		control_output[0]	= 32767.0;
	}else if( control_output[0] < -32768.0 ){
		control_output[0]	= -32768.0;
	}

	return	(signed int)control_output[0];
}


/*******************************************/
void _ISR	_T1Interrupt( void )
{
	static signed long	output;
	signed int	count_enc, speed;
	signed int	output_limited;


	_T1IF	= 0;

	count_enc	= readCountEncorder();
	setCountEncorder(0);

	output	+= pid( G_reference_deg_per_sec, count_enc );

	if( output > 32767 ){
		output_limited	= 32767;
		output			= 32767;
	}else if( output < -32768 ){
		output_limited	= -32768;
		output			= -32768;
	}else{
		output_limited	= output;
	}
	driveMotor( output_limited );

}
/*******************************************/
