#include <Servo.h>

#define LEFT_SERVO PD_2
#define RIGHT_SERVO PD_3                                                                                                                                                                                    

Servo left;
Servo right;

int speed;

void setup() {
  // put your setup code here, to run once:
  left.attach(LEFT_SERVO);
  right.attach(RIGHT_SERVO);
     left.writeMicroseconds(1000);
    right.writeMicroseconds(2000);
}

void loop() {
  // put your main code here, to run repeatedly: 
//    delay(750);
//    left.writeMicroseconds(1000);
//    right.writeMicroseconds(2000);
//    delay(750);
//    left.writeMicroseconds(1500);
//    right.writeMicroseconds(1500);
//    delay(750);
//    left.writeMicroseconds(1000);
//    right.writeMicroseconds(2000);
//    delay(750);
//    left.writeMicroseconds(1500);
//    right.writeMicroseconds(1500);
  
}
