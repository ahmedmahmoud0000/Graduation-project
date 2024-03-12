
#include "CytronMotorDriver.h"
// Configure the motor driver.
CytronMD motor_left(PWM_PWM, 8,9);   // PWM 1A = Pin 10, PWM 1B = Pin 11.
CytronMD motor_right(PWM_PWM, 10, 11);   // PWM 2A = Pin 8, PWM 2B = Pin 9.

//****** Left Motor Encoder Pins **********
#define ENCLA 18 // YELLOW
#define ENCLB 19 // WHITE

//****** Right Motor Encoder Pins **********
#define ENCRA 3 // YELLOW
#define ENCRB 2 // WHITE


//float linear_velocity=0.0 ;
//float angular_velocity=0.0;

float target_RPM_left ; // RPM for left motor
float target_RPM_right;// RPM for right motor

float kp_lm = .307;// <======== set propotional gain for left motor
float ki_lm = 0.0001; // <======== set integral gain for left motor

float kp_rm = .3;// <======== set propotional gain for right motor
float ki_rm = 0.0001;// <======== set integral gain for right motor

float count_per_rev_lm = 148;// <======== set this number according to your motor (count per rev) for left motor

float count_per_rev_rm = 225;// <======== set this number according to your motor (count per rev) for right motor


float MAX_RPM_lm = 290; // <======== set this number according to your motor maximum RPM

float MAX_RPM_rm = 290; // <======== set this number according to your motor maximum RPM

float WheelRadious = 0.0325;  //meter
float WheelDist = 0.25;     //meter


// ISR function variables for left motor
long prevT_i_lm = 0;
volatile float vel_i_lm = 0;
volatile int posi_lm = 0;
float count_lm = 0;

// ISR function variables for right motor
long prevT_i_rm = 0;
volatile float vel_i_rm = 0;
volatile int posi_rm = 0;
float count_rm = 0;
