#include <stepper.h>


const int pinA  =2 , pinNotA =3 , pinB = 4, pinNotB =5;


//Functions to set power
void setA(int power) {
  (power == 1) ? digitalWrite(pinA, HIGH) : digitalWrite(pinA, LOW); 
}

void setANot(int power) {
  (power == 1) ? digitalWrite(pinNotA, HIGH) : digitalWrite(pinNotA, LOW); 
}

void setB(int power) {
  (power == 1) ? digitalWrite(pinB, HIGH) : digitalWrite(pinB, LOW); 
}

void setBNot(int power) {
  (power == 1) ? digitalWrite(pinNotB, HIGH) : digitalWrite(pinNotB, LOW); 
}

struct STEPPER stepper1;




void setup() {
  // put your setup code here, to run once:
  pinMode(pinA, OUTPUT);
  pinMode(pinNotA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinNotB, OUTPUT);

  Serial.begin(9600);

  setupStepper(&stepper1, &setA, &setANot, &setB, &setBNot);

  //2048 is 360 on my stepper motor
  setTargetStep(&stepper1, 2048);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Serial.println(getCurrentStep(stepper1));
  updateStepper(&stepper1);
  delay(12);
}
