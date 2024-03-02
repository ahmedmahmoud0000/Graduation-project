

class UnicycleKinematics {
  private:
    float V_rm , V_lm //right and left motor vel result in radians per second(r/s)
    , L
    , v
    , w, R;
    float feedbackLinearVel_x, feedbackLinearVel_y,feedbackAngularVel, RobotPose_x, RobotPose_y, RobotPose_theta;
    long last_time;
  public:

    void setParams(float R_In, float L_In , float v_In, float w_In) {
      R = R_In; L = L_In; v = v_In; w = w_In;

    }
    
//****************** SET MOTORS SPEED CALCULATIONS ***********************

    void MotorKinematicsCalculation() {
      V_rm = ((2 * v) + (w * L)) / (2 * R)*.55;
      V_lm = ((2 * v) - (w * L)) / (2 * R)*.55;

//      V_rm = ((v/R) + (w * L/2))*.55 ;
//      V_lm = ((v/R) - (w * L/2))*.55 ;
      //      if (v==0&&w==0){
      //        V_rm=0;
      //        V_lm=0;
      //        }
    }

    float get_LeftWheelRPM() {
      float RPM_lm = V_lm * 60;
      return RPM_lm;
    }

    float get_RightWheelRPM() {
      float RPM_rm = V_rm * 60;
      return RPM_rm;
    }


    //****************** GET FEED-BACK SPEED CALCULATIONS ***********************

    void MotorFeedBackCalculation(float feedbackRPM_lm, float feedbackRPM_rm) {
      long current_time = micros();
      float deltaT = ((float) (current_time - last_time)) / 1.0e6;
      
      float V_lm = ((feedbackRPM_lm *2*M_PI)/ 60)*R; float V_rm = ((feedbackRPM_rm*2*M_PI)/ 60)*R;


      feedbackLinearVel_x = (( V_rm + V_lm ))/ 2;
      feedbackLinearVel_y=0;
      feedbackAngularVel = (( V_rm - V_lm ))/ L;

      RobotPose_x += ((cos(RobotPose_theta) * feedbackLinearVel_x)-(sin(RobotPose_theta) * feedbackLinearVel_y))* deltaT;
      RobotPose_y += ((cos(RobotPose_theta) * feedbackLinearVel_y)+(sin(RobotPose_theta) * feedbackLinearVel_x))* deltaT;
      RobotPose_theta += feedbackAngularVel * deltaT;
      if (RobotPose_theta > 3.14)
        RobotPose_theta = -3.14;

      last_time = current_time;
    }

    double get_RobotPose_x() {

      return RobotPose_x;
    }

    double get_RobotPose_y() {

      return RobotPose_y;
    }


    double get_RobotPose_theta() {

      return RobotPose_theta;
    }
    
    double get_RobotLinearVel() {

      return feedbackLinearVel_x;
    }

    double get_RobotAngularVel() {

      return feedbackAngularVel;
    }
};
