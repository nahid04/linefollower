
/////////////////////////////////////////////////////////////////
#include "MotorClassL.h"
int pinArray[]={34,32,30,28,8,9};
MotorClassL mc(pinArray);

int M1=150,M2=150;
int m1Speed,m2Speed,boostSpeed;
//////////////////////////////////////////////////////////////////
#define NUM_SENSOR 8
#define SENSOR_DEBUG
//#define CALIBON
int sensorPin[]={A7,A6,A5,A4,A3,A2,A1,A0};
int sensorA[NUM_SENSOR];
int chk[NUM_SENSOR];
int sensorD[NUM_SENSOR];
int sensorMin[NUM_SENSOR];
int sensorMax[NUM_SENSOR];
//////////////////////////////////////////////////////////////////
int lastError=0;
float KP,KD;
//////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);
  //sensorInit();
  m1Speed = m2Speed = 0;
  KP=.81;
  KD=2.11;
}
void loop(){
  
  motorTest();
  //digitalWrite(22,HIGH);
  //analogWrite(9,100);
  //mc.motor2(0,1,100);
  //sensorTest();
  
  //pid();
  //pidCalib();
  Serial.println();
}
void motorTest(){
  mc.motorForward(255,255);
  delay(1500);
  //mc.brake();
  //delay(500);
}
void sensorTest(){
  sensorRead();
}
void pidCalib(){
  if(Serial.available()){
    char x=Serial.read();
    if(x=='+'){
      KP+=.1;
    }
    else if(x=='-'){
      KP-=.1;
    }
    else if(x=='9'){
      KD+=.1;
    }
    else if(x=='0'){
      KD-=.1;
    }
  }
}
void pid(){
  int pos=sensorRead();
  int error = ((pos)-2500)/10;
  #ifdef SENSOR_DEBUG
  Serial.print('\t');
  Serial.print(error);
  Serial.print('\t');
  Serial.print(KP);
  Serial.print('\t');
  Serial.print(KD);
  #endif
  int motorSpeed = KP * error + KD * (error - lastError);
  lastError = error;
  
  if((M1 + motorSpeed)>255){
    m1Speed = 255;
    m2Speed = M2 - motorSpeed - (M1+motorSpeed-255);
  }
  else if((M2 - motorSpeed)>255){
    m2Speed = 255;
    m1Speed = M1 + motorSpeed - (M2-motorSpeed-255);
  }
  else{
    m1Speed = M1 + motorSpeed;
    m2Speed = M2 - motorSpeed;
  }
  
  if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
    
   mc.motorForward(m1Speed,m2Speed);
}

