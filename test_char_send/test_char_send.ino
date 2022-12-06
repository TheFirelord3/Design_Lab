#include <SoftwareSerial.h>

SoftwareSerial HC12(10,11);  //RX, TX

int joystickValue;
int input = A1;
char joystickValueChar[5];

String xval;

boolean newData = false;

int dataNumber = 0;             // new for this version

void setup() {
    Serial.begin(9600);
    HC12.begin(9600);

    


    pinMode(input,INPUT);

}

void loop() {
    xval= "";
    joystickValue=analogRead(input);
    xval+=itoa(joystickValue,joystickValueChar,10);
    xval+='T';
    Serial.println(xval);
    HC12.print(xval);
}
