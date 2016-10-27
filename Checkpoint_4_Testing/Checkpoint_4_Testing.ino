//Define servo pins
// These pins must support analogWrite()
#define LEFT_SERVO PD_2
#define RIGHT_SERVO PD_3


//Define Servo speeds
// Left and right should be inverted
// Because there are on opposite sides of the bot
#define LEFT_FORWARD 1700
#define LEFT_BACKWARD 1300
#define RIGHT_FORWARD LEFT_BACKWARD
#define RIGHT_BACKWARD LEFT_FORWARD
#define SERVO_STOP 1500


//Magic numbers that determine how long we wait
//While executing a turn
#define CCW_DELAY 250
#define CW_DELAY 250

Servo left_servo;
Servo right_servo;

void setup() {
  // put your setup code here, to run once:
  left_servo.attach(LEFT_SERVO);
  right_servo.attach(RIGHT_SERVO);
  delay(1000);

  left_servo.writeMicroseconds(LEFT_FORWARD);
  right_servo.writeMicroseconds(RIGHT_FORWARD);

  delay(1000);

  left_servo.writeMicroseconds(SERVO_STOP);
  right_servo.writeMicroseconds(SERVO_STOP);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
