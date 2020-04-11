#include <Arduino.h>
#include <Servo.h>
Servo s1;
int pos = 0;

void execute()
{
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    Serial.write("LED cycle\n");
    
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        s1.write(pos);              // tell servo to go to position in variable 'pos'
        Serial.print("POS: "+String(pos)+"\n");

        delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        s1.write(pos);              // tell servo to go to position in variable 'pos'
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
}

void loop()
{
    // put your main code here, to run repeatedly:
    execute();
}