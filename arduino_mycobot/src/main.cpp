//myCobotの動作プログラム
#include <Arduino.h>
#include <SCServo.h>

// generate instance
SMS_STS sms_sts;

// define and initialize parameters
#define SW1 9
#define SW2 10
#define LED 7
#define joint_num 6
#define push_time 100
unsigned char ID[joint_num] = {1,2,3,4,5,6};
short init_angle = 2048;
short angle[6] = {2048};
unsigned short speed = 150;
unsigned char ACC = 254;

// put function declarations here:
void initialize();
void set_init_pos();
void set_measure_pos();
void measure();

void setup() {
  // put your setup code here, to run once:
  initialize();
  set_init_pos();
  set_measure_pos();
}

void loop() {
  // put your main code here, to run repeatedly:
  measure();
}

// put function definitions here:
void initialize(){
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  Serial.begin(1000000);
  sms_sts.pSerial = &Serial;
}

void set_init_pos(){
  int i;
  for(i=0;i<joint_num;i++){
    sms_sts.WritePosEx(ID[i],init_angle,speed,ACC);
  }
  delay(10000);
}

void set_measure_pos(){
  // describe procession
  while(1){
    if(digitalRead(SW1) == 1){
      delay(1000);
      break;
    }
  }
  if(angle[0] != 3072){
    sms_sts.WritePosEx(ID[0],3072,speed,ACC);
  }
  if(angle[2] != 3072){
    sms_sts.WritePosEx(ID[2],3072,speed,ACC);
  }
  if(angle[3] != 3072){
    sms_sts.WritePosEx(ID[3],3072,speed,ACC);
  }
  if(angle[4] != 1024){
    sms_sts.WritePosEx(ID[4],1024,speed,ACC);
  }
  delay(5000);
}

void measure(){
  // set parameters
  uint8_t flag = 0;
  short set_pos = 0;

  // describe procession
  while(1){
    if(digitalRead(SW1) == 1){
      delay(1000);
      break;
    }
    if((digitalRead(SW2) == 1) && (flag == 0)){
      delay(1000);
      flag = 1;
      set_init_pos();
    }
    else if((digitalRead(SW2) == 1) && (flag == 1)){
      delay(1000);
      flag = 0;
      set_measure_pos();
    }
    digitalWrite(LED,LOW);
    delay(1000);
    digitalWrite(LED,HIGH);
    delay(1000);
  }
  set_pos = 2048+683;
  sms_sts.WritePosEx(ID[5],set_pos,speed,ACC);
  delay(6000);
  set_pos = 2048-683;
  sms_sts.WritePosEx(ID[5],set_pos,speed,ACC);
  delay(12000);
  set_pos = 2048;
  sms_sts.WritePosEx(ID[5],set_pos,speed,ACC);
  delay(6000);
}