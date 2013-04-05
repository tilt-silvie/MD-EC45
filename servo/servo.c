/*
 * File:   servo.c
 * Author: Master
 *
 * Created on 2013/04/04 20:27
 */


/*
 *MEMO
 *fractional型は，signed int に対応してる
 *Fract2Float( 1.0 ) -> 32767
 *Fract2Float( -1.0 ) -> -32768
 *Fract2Float( 1.5 ) -> 32767
 *Fract2Float( -1.5 ) -> -32768
 */

#include	<timer.h>
#include	<dsp.h>
#include	"servo.h"
#include	"encorder/encorder.h"
#include	"../motor/motor.h"

#define	_DEBUG
#include	"../assert/assert.h"
#include	"../xprintf/xprintf.h"


/*******************************************/
static tPID	G_s_pid;
fractional G_abcCoefficient[3]	__attribute__ ((section (".xbss, bss, xmemory")));
fractional G_controlHistory[3]	__attribute__ ((section (".ybss, bss, ymemory")));
fractional	G_pid_gain_coeff[3] = {0,0,0};
/*******************************************/


/*******************************************/
static void	initializeTimer( void );
static void	initializePID( void );
/*******************************************/

/*******************************************/

extern void	initializeServo( void )
{
	initializeEncorder();
	resetCountEncorder();

	initializePID();
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


static void	initializePID( void )
{
	const float	KP_ = 1.0, KI_ = 0.0, KD_ = 0.0;

	G_s_pid.abcCoefficients	= &G_abcCoefficient[0];
	G_s_pid.controlHistory	= &G_controlHistory[0];

	PIDInit( &G_s_pid );
	G_s_pid.controlReference	= 0;

	G_pid_gain_coeff[0]	= Float2Fract( KP_ );
	G_pid_gain_coeff[1]	= Float2Fract( KI_ );
	G_pid_gain_coeff[2]	= Float2Fract( KD_ );
	PIDCoeffCalc( &G_pid_gain_coeff[0], &G_s_pid );
}
/*******************************************/


/*******************************************/
extern signed long	setReferenceServo( signed long deg_per_sec )
{
	signed long	measured_deg_per_sec;
	signed int	pulse_per_2ms;

	pulse_per_2ms	= deg_per_sec / 125;
	G_s_pid.controlReference	= pulse_per_2ms;

	measured_deg_per_sec	= G_s_pid.measuredOutput;
	measured_deg_per_sec	= measured_deg_per_sec * 125;
	return	measured_deg_per_sec;
}
/*******************************************/




/*******************************************/
extern void	setGainServo( float kp, float ki, float kd )
{
	G_pid_gain_coeff[0]	= Float2Fract( kp );
	G_pid_gain_coeff[1]	= Float2Fract( ki );
	G_pid_gain_coeff[2]	= Float2Fract( kd );
	PIDCoeffCalc( &G_pid_gain_coeff[0], &G_s_pid );
}
/*******************************************/



/*******************************************/
void _ISR	_T1Interrupt( void )
{
	static signed long	output;
	signed long			count_enc, speed;
	signed int	output_limited;


	_T1IF	= 0;

	count_enc	= readCountEncorder();
	speed	= count_enc - 32768;
	resetCountEncorder();

	G_s_pid.measuredOutput	= (int)(speed);

	PID( &G_s_pid );

	output	+= G_s_pid.controlOutput;

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

/*******************************************/
#define	NUM_BUF 150
#define	TEST_CYCLE 200
#define	STEP_SPEED 18000

	static signed int buf[2][NUM_BUF];
	static unsigned int i,cycle;

	if( cycle < TEST_CYCLE ){
		cycle	++;
	}else{
		cycle	= 0;

		xprintf("%5d|%5d|%5d|%5d\n",
				G_s_pid.controlReference,
				G_s_pid.measuredOutput,
				G_s_pid.controlOutput,
				output_limited);

/*
 *        if( i < (NUM_BUF/3) ){
 *            setReferenceServo( 0 );
 *        }else if( i < (NUM_BUF/3*2) ){
 *            setReferenceServo( STEP_SPEED );
 *        }else{
 *            setReferenceServo( 0 );
 *        }
 *
 *        if( i < NUM_BUF ){
 *            buf[0][i]	= G_s_pid.controlReference;
 *            buf[1][i]	= G_s_pid.measuredOutput;
 *            i++;
 *        }else if(i == NUM_BUF ){
 *            unsigned int j;
 *            xprintf("t[ms],Ref[-],Mes[-]\n"); 
 *            for( j = 0; j < NUM_BUF; j++ ){
 *                xprintf("%d,%d,%d\n", j*2*TEST_CYCLE, buf[0][j], buf[1][j] );
 *            }
 *            i++;
 *        }
 */
	}

/*******************************************/
}
/*******************************************/
