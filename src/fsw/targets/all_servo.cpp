#include <Arduino.h>
#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
int pos = 0;

int servoSetter(int w,int x,int y,int z){
    s1.write(w);
    s2.write(x);
    s3.write(y);
    s4.write(z);
    return 0;
}

void execute()
{
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    Serial.write("LED cycle\n");

    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        servoSetter(pos,pos,pos,pos);            // tell servo to go to position in variable 'pos'
        Serial.print("POS: "+String(pos)+"\n");
        delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        servoSetter(pos,pos,pos,pos);               // tell servo to go to position in variable 'pos'
        Serial.print("POS: "+String(pos)+"\n");
        delay(15);                       // waits 15ms for the servo to reach the position
    }
}

void setup()
{
    // put your setup code here, to run once:
    delay(2000);
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    s1.attach(29);
    s2.attach(30);
    s3.attach(35);
    s4.attach(36);
}

void loop()
{
    // put your main code here, to run repeatedly:
    execute();
}

