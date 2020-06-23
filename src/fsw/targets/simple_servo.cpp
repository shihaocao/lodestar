#include <Arduino.h>
#include <Servo.h>
Servo m1;
Servo s1;
Servo s2;
Servo s3;
Servo s4;

int pos = 0;

int eq1=90;
int eq2=90;
int eq3=94;
int eq4=90;

void set(int w, int x, int y, int z){
    s1.write(w+eq1);
    s2.write(x+eq2);
    s3.write(y+eq3);
    s4.write(z+eq4);

}

void execute()
{
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    Serial.write("LED cycle\n");

    
    
    for (pos = 0; pos <= 144; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        set(20,-20,0,0);
        m1.write(pos);              // tell servo to go to position in variable 'pos'
        delay(150);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 144; pos >=0; pos -= 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        set(20,-20,0,0);
        m1.write(pos);              // tell servo to go to position in variable 'pos'
        delay(150);                       // waits 15ms for the servo to reach the position
    }
    
   
   
}

void setup()
{
    // put your setup code here, to run once:
    delay(2000);
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    m1.attach(29);
    s1.attach(2);
    s2.attach(23);
    s3.attach(3);
    s4.attach(22);
}

void loop()
{
    // put your main code here, to run repeatedly:
    execute();
}