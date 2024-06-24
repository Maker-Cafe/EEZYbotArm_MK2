#include <Servo.h>

Servo M0;
Servo M1;
Servo M2;
Servo claw;

int M0_Pos = 0;
int M1_Pos = 0;
int M2_Pos = 0;
int c_Pos = 0;

int X, Y, A, B, C, D, E, F;
const int xPin = A0;
const int yPin = A1;
const int aPin = 2;
const int bPin = 3;
const int cPin = 4;
const int dPin = 5;
const int ePin = 6;
const int fPin = 7;

int xVal;
int yVal;
int aVal;
int bVal;
int cVal;
int dVal;
int eVal;
int fVal;

const int M0_maxAng = 180;
const int M1_maxAng = 135;
const int M2_maxAng = 135;
const int C_maxAng = 100;

const int M0_minAng = 0;
const int M1_minAng = 45;
const int M2_minAng = 45;
const int C_minAng = 0;

double myAngDif;
int jointPress = 0;
unsigned long myTime;

//Input Variables
double rate = 25;





void jointPosFun(int val, int joint){
  //Change angle of joint at a rate of:   joystick position / rate[ms]
  int joint_Pos;
  int minAng, maxAng, minAngRate, maxAngRate;

  if(millis() - myTime >= rate){
    
    switch(joint){
      case 1:
        // A Button 
        maxAng = M0_maxAng;
        minAng = M0_minAng;
        maxAngRate = 250;
        minAngRate = -250;
        joint_Pos = M0.read();
        break;
      case 2:
      // C Button 
        maxAng = M1_maxAng;
        if(M2.read() <= 65){
          minAng = M1_minAng + (65-M2.read());
        }else{
          minAng = M2_minAng;
        }
        maxAngRate = 250;
        minAngRate = -250;
        joint_Pos = M1.read();
        break;
      case 3:
        // B Button 
        maxAng = M2_maxAng;
        if(M1.read() <= 65){
          minAng = M2_minAng + (65-M1.read());
        }else{
          minAng = M2_minAng;
        }
        maxAngRate = 250;
        minAngRate = -250;
        joint_Pos = M2.read();
        break;
      case 4:
        // D Button 
        maxAng = C_maxAng;
        minAng = C_minAng;
        maxAngRate = 500;
        minAngRate = -500;
        joint_Pos = claw.read();
        break;
      default:
        break;
    }

    myAngDif = (map(val, 0, 1023, minAngRate, maxAngRate))/100.0;
    
    Serial.print(val);
    Serial.print(", ");
    Serial.print(myAngDif);
    Serial.print(", ");
    Serial.print(joint_Pos);
    Serial.print(", ");
    Serial.println(joint);

    if(myAngDif > 2 || myAngDif < -2){
      if(joint_Pos <= maxAng && joint_Pos >= minAng){
        joint_Pos = joint_Pos + myAngDif;
      }
      if(joint_Pos > maxAng){
        joint_Pos = maxAng;
      }
      if(joint_Pos < minAng){
        joint_Pos = minAng;
      }
    }  

    myTime = millis();  

    switch(joint){
      case 1:
        M0.write(joint_Pos);
        break;
      case 2:
        M1.write(joint_Pos);
        break;
      case 3:
        M2.write(joint_Pos);
        break;
      case 4:
        claw.write(joint_Pos);
        break;
      default:
        break;
    }
  } 
}

void pinRead(){
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  aVal = digitalRead(aPin);
  bVal = digitalRead(bPin);
  cVal = digitalRead(cPin);
  dVal = digitalRead(dPin);
  eVal = digitalRead(ePin);
  fVal = digitalRead(fPin);
}

void pinSerialOutput(){
  Serial.print(xVal);
  Serial.print(", ");
  Serial.print(yVal);
  Serial.print(", ");
  Serial.print(aVal);
  Serial.print(", ");
  Serial.print(bVal);
  Serial.print(", ");
  Serial.print(cVal);
  Serial.print(", ");
  Serial.print(dVal);
  Serial.print(", ");
  Serial.print(eVal);
  Serial.print(", ");
  Serial.println(fVal);
}

void servoPosRead(){
  Serial.print(M0.read());
  Serial.print(", ");
  Serial.print(M1.read());
  Serial.print(", ");
  Serial.print(M2.read());
  Serial.print(", ");
  Serial.println(claw.read());
}





void setup() {
  Serial.begin(9600);

  M0.attach(10);
  M1.attach(12);
  M2.attach(11);
  claw.attach(13);

  pinMode(aPin,INPUT);
  pinMode(bPin,INPUT);
  pinMode(cPin,INPUT);
  pinMode(dPin,INPUT);
  pinMode(ePin,INPUT);
  pinMode(fPin,INPUT);

  myTime = millis();

  M0.write(90);
  M1.write(45);
  M2.write(65);
  claw.write(0);

}

void loop() {
  pinRead();
  //pinSerialOutput();

  if(!aVal){
    jointPress = 1;
  }
  if(!bVal){
    jointPress = 2;
  }
  if(!cVal){
    jointPress = 3;
  }
  if(!dVal){
    jointPress = 4;
  }

  
  xVal = analogRead(xPin);
  jointPosFun(xVal,jointPress);

}
















