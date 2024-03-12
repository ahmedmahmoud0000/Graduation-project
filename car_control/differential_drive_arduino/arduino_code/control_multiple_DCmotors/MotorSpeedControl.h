#include <util/atomic.h> // For the ATOMIC_BLOCK macro

class MOTORSPEEDCONTROL {

  private:

    volatile int posi ;
    volatile float vel_i;

    long prev_t;
    int prev_pose;

    float count_per_rev ;

    float velocity1, velocity2;

    float v1Filt, v1Prev, v2Filt, v2Prev ;

    float target_RPM;
    float kp, ki;
    float eintegral ;
    
    float MAX_RPM,RPM_to_PWM;

  public:

    void setParams(float count_per_rev_In, int posi_In, float vel_i_In, float target_RPM_In,float MAX_RPM_In, float kpIn,  float kiIn) {
      kp = kpIn;  ki = kiIn; target_RPM = target_RPM_In;MAX_RPM=MAX_RPM_In;
      posi = posi_In; vel_i = vel_i_In; count_per_rev = count_per_rev_In;
    }


    void motor_control() {

      int pos ;

      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {    // Read the position in an atomic block to avoid a potential misread if the interrupt coincides with this code running
        pos = posi;
        velocity2 = vel_i;

      }

      //*************Velocity calculations method 1*************************
      long currT = micros();
      float deltaT = ((float) (currT - prev_t)) / 1.0e6;
      velocity1 = (pos - prev_pose) / deltaT;
      prev_t = currT;
      prev_pose = pos;


      //****** convert "vel 1 & 2" FROM "count/s" TO "rev/m(RPM)" **********

      float rpm1 = (velocity1 / count_per_rev) * 60;
      float rpm2 = (velocity2 / count_per_rev) * 60;


      //*************filtering velocity using "LOW-PASS filter" **************

      v2Filt = 0.854 * v2Filt + 0.0728 * rpm2 + 0.0728 * v2Prev;
      v2Prev = rpm2;

      //
      if (rpm1 == 0 ) {

        rpm2 = 0;
        v2Filt = 0;
      }
      
//*************PID contorl on motor speed  **************

      // Compute the control signal u
      float e = target_RPM - v2Filt;
      eintegral = eintegral + e * deltaT;

      float u = kp * e + ki * eintegral;

      RPM_to_PWM = map(u, 0, 290, 0, 255);


      

    }
    void print_speed(){
      
      Serial.print(v2Filt);
      Serial.print(" ");
      }
    
    float get_speed() {

      return RPM_to_PWM;
    }



};
