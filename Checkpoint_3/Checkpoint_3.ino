#include <Servo.h>

#define LEFT_SERVO PF_1
#define RIGHT_SERVO PD_0

Servo left;
Servo right;

int speed;

void setup() {
  // put your setup code here, to run once:
  left.attach(LEFT_SERVO);
  right.attach(RIGHT_SERVO);
}

void loop() {
  // put your main code here, to run repeatedly: 
    delay(500);
    left.writeMicroseconds(1700);
    right.writeMicroseconds(1300);
    delay(500);
    left.writeMicroseconds(1300);
    right.writeMicroseconds(1700);
    delay(500);
    left.writeMicroseconds(1500);
    right.writeMicroseconds(1500);
    delay(500);
  
}
