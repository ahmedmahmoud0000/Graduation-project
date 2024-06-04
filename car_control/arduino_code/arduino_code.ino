#define pwm_1 10
#define pwm_2 8
#define dir_1 11
#define dir_2 9
#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA  3 // YELLOW
#define ENCB  2 // green
#define ENCC 18 // YELLOW
#define ENCD 19 // green

#define COMMAND_RATE 50

volatile int posi_left = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
volatile int posi_right = 0;

int inByte = 0;
uint8_t data_Received=0,irt=0,data_complete=0;
uint8_t data[2]={0,0},i=0;


//int inByte=0;
//** Left Motor Encoder Pins ****
#define ENCLA 3 // YELLOW
#define ENCLB 2 // GREEN


//** Right Motor Encoder Pins ****
#define ENCRA 18 // YELLOW
#define ENCRB 19 // GREEN

unsigned long lastInterruptTimeR = 0;  // variable to store the time of the last interrupt
unsigned long lastInterruptTimeL = 0;  // variable to store the time of the last interrupt
int LM_pose_cahnge=0;
int RM_pose_cahnge=0;

float count_per_rev_lm = 507;// <======== set this number according to your motor (count per rev) for left motor 510.0

float count_per_rev_rm = 507;// <======== set this number according to your motor (count per rev) for right motor 468.5

unsigned long lastTime, now;

//LEFT MOTOR PARAMTERS

volatile int posi_lm = 0;
double LM_kp = 0.03 , LM_ki = 0.0003 , LM_kd = 0.000003;          // modify for optimal performance



volatile long LM_encoderPos = 0, LM_last_pos = 0, LM_lastpos = 0;

//RIGHT MOTOR PARAMTERS

volatile int posi_rm = 0;

double RM_kp = 0.03 , RM_ki = 0.0003, RM_kd = 0.000003;          // modify for optimal performance


volatile long RM_encoderPos = 0, RM_last_pos = 0, RM_lastpos = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(dir_1, OUTPUT);
  pinMode(dir_2, OUTPUT);
//  pinMode(ENCA,INPUT);
//   pinMode(ENCB,INPUT);
//   pinMode(ENCC,INPUT);
//   pinMode(ENCD,INPUT);
  pinMode(ENCLA, INPUT);
  pinMode(ENCLB, INPUT);
  pinMode(ENCRA, INPUT);
  pinMode(ENCRB, INPUT);
  // attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder_left,RISING);
  // attachInterrupt(digitalPinToInterrupt(ENCC),readEncoder_right,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCLA), readEncoder_left, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCRA), readEncoder_right, RISING);

  stop_motor();
}

void loop() {
  if (Serial.available() > 0) {
    inByte = Serial.read();
    //Serial.print(inByte);
    if (data_Received==1){
        if(inByte==0x78){

          data_complete=1;
          
          data_Received=0;
          //cli();
//          for( i=0;i<irt;i++){
//            Serial.write(data[i]);//data[i]+
//          }
          irt=0;
         
        }
        else{
          data[irt]=inByte;
          //Serial.print(data[irt]);
          irt++;
        }
      }
            else if(inByte==0x7A)
      {
        data_Received=1;
      }
    }
    int pos_left = 0; 
  int pos_right = 0; 
  static unsigned long prev_imu_time = 0;
  static unsigned long prev_control_time = 0;
  // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
  //   pos_left = posi_left;
  //   pos_right = posi_right;
  // }
 ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { // Read the position in an atomic block to avoid a potential misread if the interrupt coincides with this code running
  //  unsigned long interruptTimeL = millis();  // get the current time
  //  if (interruptTimeL - lastInterruptTimeL > 8) {  // check if enough time has elapsed since the last interrupt
      LM_encoderPos = posi_lm;
  //    lastInterruptTimeL = interruptTimeL;
  //  }
  //  unsigned long interruptTimeR = millis();  // get the current time
  //  if (interruptTimeR - lastInterruptTimeR > 8) {  // check if enough time has elapsed since the last interrupt
      RM_encoderPos = posi_rm;
  //    lastInterruptTimeR = interruptTimeR;
  //  }
  }
    now = millis();
    if ((millis() - prev_control_time) >= (1000 / COMMAND_RATE))
  {

    LM_pose_cahnge = ((LM_encoderPos - LM_last_pos));// / count_per_rev_lm; //change in position in degrees of the wheel 360.0 * LM_lastpos

    RM_pose_cahnge = ( (RM_encoderPos - RM_last_pos));// / count_per_rev_rm; //change in position in degrees of the wheel 360.0 * RM_lastpos

    lastTime = now;
    LM_last_pos = LM_encoderPos;
    RM_last_pos = RM_encoderPos;
  }
  Serial.print(LM_pose_cahnge);
    Serial.print(" ");
    Serial.print(RM_pose_cahnge);
    Serial.println();
  // put your main code here, to run repeatedly:
//  if (Serial.available() > 0) {
//    // get incoming byte:
//    inByte = Serial.read();
//     Serial.println(inByte);
//  }

  switch (data[0]) {
    case 1:  // your hand is on the sensor
      // Serial.println("forward");
      forward(data[1]);
      break;
    case 2:  // your hand is close to the sensor
      // Serial.println("backward");
      back(data[1]);
      break;
    case 3:  // your hand is a few inches from the sensor
      // Serial.println("left");
      left(data[1]);
      break;
    case 4:  // your hand is nowhere near the sensor
      // Serial.println("right");
      right(data[1]);
      break;
    case 5:  // your hand is nowhere near the sensor
      // Serial.println("stop");
      stop_motor();
      break;
    default:

      break;
  }
 delay(5);  
}



void forward(int moter_speed) {
  analogWrite(pwm_1, moter_speed);
  analogWrite(pwm_2, moter_speed);
  digitalWrite(dir_1, HIGH);
  digitalWrite(dir_2, HIGH);
}

void back(int moter_speed) {
  analogWrite(pwm_1, moter_speed);
  analogWrite(pwm_2, moter_speed);
  digitalWrite(dir_1, LOW);
  digitalWrite(dir_2, LOW);
}

void right(int moter_speed) {
  analogWrite(pwm_1, moter_speed);
  analogWrite(pwm_2, moter_speed);
  digitalWrite(dir_1, HIGH);
  digitalWrite(dir_2, LOW);
}

void left(int moter_speed) {

  analogWrite(pwm_1, moter_speed);
  analogWrite(pwm_2, moter_speed);
  digitalWrite(dir_1, LOW);
  digitalWrite(dir_2, HIGH);
}

void stop_motor(void) {

  analogWrite(pwm_1, 0);
  analogWrite(pwm_2, 0);
  digitalWrite(dir_1, HIGH);
  digitalWrite(dir_2, HIGH);
}



// void readEncoder_left(){
//   int A = digitalRead(ENCB);
//   if(A > 0){
//     posi_left++;
//   }
//   else{
//     posi_left--;
//   }
// }

// void readEncoder_right(){
//   int B = digitalRead(ENCD);
//   if(B > 0){
//     posi_right++;
//   }
//   else{
//     posi_right--;
//   }
// }



void readEncoder_left() {

  int b = digitalRead(ENCLB);

  if (b > 0) {
    posi_lm ++;

  }
  else {
    posi_lm --;

  }

}

void readEncoder_right() {

  int b = digitalRead(ENCRB);

    if (b > 0) {
      posi_rm ++;
//Serial.println(posi_rm);
    }
    else {
      posi_rm --;

    }
   
}
