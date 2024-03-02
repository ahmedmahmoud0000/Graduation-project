/**
 * arduino code that control Two motors speed using PID control  
 * @author Kyrillos Fekry(KroNton)
 * @see {@link https://github.com/KroNton/differential_drive_arduino}
*/


#include "CytronMotorDriver.h"
#include "MotorSpeedControl.h"

// Configure the motor driver.
CytronMD motor_left(PWM_PWM, 10, 11);   // PWM 1A = Pin 10, PWM 1B = Pin 11.
CytronMD motor_right(PWM_PWM, 8, 9);   // PWM 2A = Pin 8, PWM 2B = Pin 9.

//****** Left Motor Encoder Pins **********
#define ENCLA 3 // YELLOW
#define ENCLB 2 // WHITE

//****** Right Motor Encoder Pins **********
#define ENCRA 18 // YELLOW
#define ENCRB 19 // WHITE


float target_RPM_left = 0; // <======== set this number according to required RPM for left motor
float target_RPM_right = 0;// <======== set this number according to required RPM for right motor

float kp_lm = 0.3;// <======== set propotional gain for left motor
float ki_lm = 3; // <======== set integral gain for left motor

float kp_rm = .3;// <======== set propotional gain for right motor
float ki_rm = 3;// <======== set integral gain for right motor

float count_per_rev_lm = 260;// <======== set this number according to your motor (count per rev) for left motor

float count_per_rev_rm = 260;// <======== set this number according to your motor (count per rev) for right motor


float MAX_RPM_lm = 290; // <======== set this number according to your motor maximum RPM

float MAX_RPM_rm = 290; // <======== set this number according to your motor maximum RPM



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


//  motor objects from the  "MOTORCONTROL" class

MOTORSPEEDCONTROL LeftMotor;
MOTORSPEEDCONTROL RightMotor;

void setup() {

  Serial.begin(9600);
  pinMode(ENCLA, INPUT);
  pinMode(ENCLB, INPUT);
  pinMode(ENCRA, INPUT);
  pinMode(ENCRB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCLA), readEncoder_left, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCRA), readEncoder_right, RISING);


}

void loop() {

  LeftMotor.setParams(count_per_rev_lm, posi_lm , vel_i_lm , target_RPM_left, MAX_RPM_lm, kp_lm, ki_lm );

  RightMotor.setParams( count_per_rev_lm, posi_rm , vel_i_rm , target_RPM_right, MAX_RPM_rm, kp_rm, ki_rm );

  LeftMotor.motor_control();
  Serial.print(" ");
  RightMotor.motor_control();
  Serial.println();

  motor_left.setSpeed(LeftMotor.get_speed());
  motor_right.setSpeed(RightMotor.get_speed());

}

void readEncoder_left() {
  int b = digitalRead(ENCLB);
  if (b > 0) {
    posi_lm ++;
    count_lm = 1;
  }
  else {
    posi_lm --;
    count_lm = -1;
  }
 
  //*************Velocity calculations method 2 left motor *************************
  long current_t = micros();
  float delta_t = ((float)(current_t - prevT_i_lm)) / 1.0e6;
  vel_i_lm = count_lm / delta_t;
  prevT_i_lm = current_t;
Serial.print(vel_i_lm);
}


void readEncoder_right() {
  int b = digitalRead(ENCRB);
  if (b > 0) {
    posi_rm ++;
    count_rm = 1;
  }
  else {
    posi_rm --;
    count_rm = -1;
  }

  

  //*************Velocity calculations method 2 right motor *************************
  long current_t = micros();
  float delta_t = ((float)(current_t - prevT_i_rm)) / 1.0e6;
  vel_i_rm = count_rm / delta_t;
  prevT_i_rm = current_t;
Serial.print(vel_i_rm);

}
