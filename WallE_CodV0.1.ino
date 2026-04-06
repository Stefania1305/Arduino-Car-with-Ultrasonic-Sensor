#include <IRremote.h>
#include <Servo.h>
#define Lpwm_pin  5
#define Rpwm_pin  6
int pinLB=3
int pinLF=4;
int pinRB=7;
int pinRF=8;
int Rec_Pin = 12;
int pinRoti[] = {8,7,4,3};
bool MotorStates[2][2] = {{LOW,LOW},{LOW,LOW}};
IRrecv irrecv(Rec_Pin);
decode_results results;

Servo myservo;



int pos = 0;    //servo pos

void setup()
{
    Set_Speed(255);
    Serial.begin(9600);
    irrecv.enableIRIn();
  pinMode(pinLB,OUTPUT); // /pin 2
  pinMode(pinLF,OUTPUT); // pin 4
  pinMode(pinRB,OUTPUT); // pin 7
  pinMode(pinRF,OUTPUT);  // pin 8
  pinMode(Lpwm_pin,OUTPUT);  // pin 5 (PWM) 
  pinMode(Rpwm_pin,OUTPUT);  // pin6(PWM) 
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  myservo.attach(A2);
}

void loop(){

  float distanta = checkdistance();
  if(irrecv.decode(&results) == 0xFF18E7)
  {
    advance();
    delay(1000);
    pos = 90;
    if (distanta <= 7){
      stopp();
    }

    pos = 0;
    distanta = checkdistance();
    while (distanta > 7){
      turnL();
      distanta = checkdistance();
    }

    pos = 180;
    distanta = checkdistance();
    while (distanta > 7){
      turnL();
      distanta = checkdistance();
    }
  }
  pos = 90;
}

float checkdistance() {
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  float distance = pulseIn(A0, HIGH) / 58.00;
  delay(10);
  return distance;
}


void Set_Speed(unsigned char pwm) //function setting speed
{
  analogWrite(Lpwm_pin,pwm);
  analogWrite(Rpwm_pin,pwm);
}

void advance()    // forward
    {
     digitalWrite(pinRB,LOW);
     MotorStates[1][1] = LOW;
     digitalWrite(pinRF,HIGH);
     MotorStates[0][1] = HIGH;
     digitalWrite(pinLB,LOW);
     MotorStates[1][0] = LOW;
     digitalWrite(pinLF,HIGH); 
     MotorStates[0][0] = HIGH;
    }
void turnR()        //turning right(dual wheel)
    {
     digitalWrite(pinRB,LOW);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);
  
    }
void turnL()         //turning left(dual wheel)
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW );
     digitalWrite(pinLB,LOW);
     digitalWrite(pinLF,HIGH);
    
    }    
void stopp()        //stop
    {
     digitalWrite(pinRB,LOW);
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,LOW);
     digitalWrite(pinLF,LOW);
    
    }
void back()         //back up
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);
    }