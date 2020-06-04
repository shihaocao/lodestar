#include <Arduino.h>
#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;

void servoSetter(int w,int x,int y,int z){
    s1.write(w+90);
    s2.write(x+90);
    s3.write(y+90);
    s4.write(z+90);
}

void yaw(int th){
    servoSetter(th,0,0,-th);
}

void pitch(int th){
    servoSetter(0,th,-th,0);
}

void execute()
{
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    Serial.write("LED cycle\n");

    delay(1000);
    yaw(20);
    delay(1000);
    yaw(-20);
    delay(1000);
    servoSetter(0,0,0,0);
    delay(1000);
    pitch(20);
    delay(1000);
    pitch(-20);
    delay(1000);
    servoSetter(0,0,0,0);  
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

