#include <Arduino.h>
#include <Servo.h>
Servo m1;   //Top motor
Servo m2;   //Bottom motor
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
    




    
    //Throttle up in increments of 10 staying on each step for 3 seconds
    for (pos = 0; pos <= 180; pos += 10) { 
        m1.write(pos);              
        m2.write(pos);
        Serial.println(pos);                       
        delay(4500);
    }
    
    //Throttle down
    for (pos = 180; pos >=0; pos -= 20) { 
        m1.write(pos);              
        m2.write(pos);
        delay(150);                       
    }
    
}


void setup()
{
    // put your setup code here, to run once:
    delay(2000);
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    m1.attach(29);
    m2.attach(30);
    s1.attach(2);
    s2.attach(23);
    s3.attach(3);
    s4.attach(22);
}

void loop()
{
    execute();
}