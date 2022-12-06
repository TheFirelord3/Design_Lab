#include <SoftwareSerial.h>

SoftwareSerial HC12(10,11);  //RX, TX

char receivedChars[6];   // an array to store the received data

boolean newData = false;

int dataNumber = 0;             // new for this version

 int pin1 = 4;  //Set pin 4 and 5 as input pins for motor controller
  int pin2 = 5;
  int N = 512;
  int pin3 = 3;
  int x = dataNumber;

void setup() {
    Serial.begin(9600);
    HC12.begin(9600);
    pinMode(pin1,OUTPUT);
    pinMode(pin2,OUTPUT);
    pinMode(pin3,OUTPUT);
    pinMode(A0,INPUT);
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
}

void loop() {
    recvWithEndMarker();
    showNewNumber();
    

}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = 'T';
    char rc;
    
    if (HC12.available() > 0) {
        rc = HC12.read();
        

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            //Serial.println(ndx);
            //Serial.println(receivedChars[ndx]);
            ndx++;
            if (ndx >= 6) {
                ndx = 6 - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            //Serial.println(receivedChars);
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
        dataNumber = 0;             // new for this version
        dataNumber = atoi(receivedChars);   // new for this version
        x=dataNumber;
                //Serial.println(dataNumber); 
               //Serial.println(x);
               
              //  Serial.println(upper);
              
  //Serial.println(lower);
   
                if (x >= N){
                    int lower=map(x,512,1023,0,255);
                lower=constrain(lower,0,255);
                digitalWrite(pin1,HIGH);
                digitalWrite(pin2,LOW);
      analogWrite(pin3,lower);
      Serial.println(lower);
    }
    if (x < N){
       int upper =map(x,511,0,0,255);
                upper=constrain(upper,0,255);
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








                
        newData = false;
    }
}
