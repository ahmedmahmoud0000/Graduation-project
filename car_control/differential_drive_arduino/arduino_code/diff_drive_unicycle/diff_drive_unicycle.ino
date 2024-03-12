/**
   arduino ROS node that convert "linear & angular" vel
   to "Vl &Vr" to control Two motors and send the feedback
   filterd velocity form encoder after converting it to odometry data.
   @author Kyrillos Fekry(KroNton)
   @see {@link https://github.com/KroNton/differential_drive_arduino}
*/


#include "MotorSpeedControl.h"
#include "UnicycleKinematics.h"
#include "RosNode.h"
#include "Configure.h"



//  motor objects from the  "MOTORCONTROL" class

MOTORSPEEDCONTROL LeftMotor;
MOTORSPEEDCONTROL RightMotor;

UnicycleKinematics MotorsKinematics;

void setup() {

  //  Serial.begin(57600);
  pinMode(ENCLA, INPUT);
  pinMode(ENCLB, INPUT);
  pinMode(ENCRA, INPUT);
  pinMode(ENCRB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCLA), readEncoder_left, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCRA), readEncoder_right, RISING);
  ROSsetup();

}

void loop() {


  MotorsKinematics.setParams(WheelRadious, WheelDist , linear_velocity, angular_velocity);

  MotorsKinematics.MotorKinematicsCalculation();


  target_RPM_left = MotorsKinematics.get_LeftWheelRPM();
  target_RPM_right = MotorsKinematics.get_RightWheelRPM();

  LeftMotor.setParams(count_per_rev_lm, posi_lm , vel_i_lm , target_RPM_left, MAX_RPM_lm, kp_lm, ki_lm );

  RightMotor.setParams( count_per_rev_lm, posi_rm , vel_i_rm , target_RPM_right, MAX_RPM_rm, kp_rm, ki_rm );

  LeftMotor.motor_control();
  RightMotor.motor_control();



  MotorsKinematics.MotorFeedBackCalculation(LeftMotor.get_FeedbackSpeed(), RightMotor.get_FeedbackSpeed());

  motor_left.setSpeed(LeftMotor.get_GainSpeed());

  motor_right.setSpeed(RightMotor.get_GainSpeed());

  ROSloop( MotorsKinematics.get_RobotPose_x(), MotorsKinematics.get_RobotPose_y(),
           MotorsKinematics.get_RobotPose_theta(), MotorsKinematics.get_RobotLinearVel(), MotorsKinematics.get_RobotAngularVel());

//      Serial.print(LeftMotor.get_FeedbackSpeed());
//      Serial.print(" ");
//      Serial.print(RightMotor.get_FeedbackSpeed());
//      Serial.println();

//  delay(10);

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


}
