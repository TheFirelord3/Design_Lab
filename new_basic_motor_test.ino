#include <SoftwareSerial.h>

SoftwareSerial HC12(10,11);  //RX, TX

 int pin1 = 4;  //Set pin 4 and 5 as input pins for motor controller
  int pin2 = 5;
  int N = 512;
  int pin3 = 3;
  int x = 0;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HC12.begin(9600);
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(A0);
  
  int upper =map(x,511,0,0,255);
  upper=constrain(upper,0,255);

  int lower=map(x,512,1023,0,2550);
  lower=constrain(lower,0,255);
  //if (HC12.available()){
    
    //x = HC12.read();
   
    if (x >= N){
      digitalWrite(pin1,HIGH);
      digitalWrite(pin2,LOW);
      analogWrite(pin3,lower);
      Serial.println(lower);
    }
    if (x < N){
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,HIGH);
      analogWrite(pin3,upper);
       Serial.println(upper);
  }
    else{
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,LOW);
      //Serial.println(x);
    }
//}

}
