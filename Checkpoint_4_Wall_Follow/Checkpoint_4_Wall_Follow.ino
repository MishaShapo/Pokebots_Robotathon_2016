//Include libraries for the:
//    -ultrasonic distance sensor (hcrs04)
//    -running median filtering algorithm (FastRunningMedian)
//    -Servos motors to control driving (Servo)
#include <hcrs04.h>
#include <FastRunningMedian.h>
#include <Servo.h>

enum Wall_Direction {
  LEFT,
  RIGHT
};

//Define pins on the Launchpad to use with each distance sensor
// Trig pin is to tell ultrasonic sensor to start taking measurement
// Echo pin is for Launchpad to receive signal
// Library handles converting signal time length to distance
// These pins must support digitalRead() and digitalWrite()
#define LEFT_TRIG PD_6
#define LEFT_ECHO PC_7

#define RIGHT_TRIG PB_6
#define RIGHT_ECHO PB_7

#define FRONT_TRIG PA_3
#define FRONT_ECHO PA_4


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


//Initialize 3 distance senors objects so that
//we can use the distance sensor library
hcrs04 leftUltra(LEFT_TRIG, LEFT_ECHO);
hcrs04 rightUltra(RIGHT_TRIG, RIGHT_ECHO);
hcrs04 frontUltra(FRONT_TRIG, FRONT_ECHO);


//Initialize 2 Servo motor objects so that
//we can use the Servo library
Servo left_servo;
Servo right_servo;


//Initiailze variables for holding distance readings
int leftDistance;
int rightDistance;
int frontDistance;

//Initialize running-median data structures
//  -FastRunningMedian<datatype_of_content, size_of_sliding_window, default_value> 
FastRunningMedian<int,10,0> leftMedians;
FastRunningMedian<int,10,0> rightMedians;
FastRunningMedian<int,10,0> leftMedians;


// Variable to measure starting distance from wall and hold that distance
int side_threshold = -1;


// Minimum distance in centimeters from front of bot to front wall
// Anything below 2-3 centimeters and the readings can get funky
int front_threshold = 3;


// Boolean value to tell whether bot shoudl follow wall to the left
// or wall to the right. This will be determined by whichever wall is closer.
// Defaults to RIGHT
Wall_Direction wall_dir = RIGHT;


void setup() {
  // Initialize the distance sensors
  leftUltra.begin();
  rightUltra.begin();
  frontUltra.begin();

  //Initialize servo motors to proper pins
  left_servo.attach(LEFT_SERVO);
  right_servo.attach(RIGHT_SERVO);
  delay(10);

  //Add first 10 values to the running medians to get good reading
  for(int i = 0; i < 10; i++){

      //Distance from each sensor in centimeters
      leftDistance = (int) leftUltra.read(); 
      rightDistance = (int) rightUltra.read(); 
      frontDistance = (int) frontUltra.read(); 

      //Adding the readings to the running medain
      leftMedians.addValue(leftDistance);
      rightMedians.addValue(rightDistance);
      frontMedians.addValue(frontDistance);

      //Delay to allow distance values to settle on start-up
      delay(10);
  }

  // Get proper distance from each wall
  leftDistance = leftMedians.getMedian();
  rightDistance = rightMedians.getMedian();

  // Set threshold to the closer of the 2 walls
  // Set wall direction
  if(leftDistance > rightDistance){
    side_threshold  = rightDistance;
    wall_dir = RIGHT;
  } else {
    side_threshold = leftDistance;
    wall_dir = LEFT;
  }

  //If threshold is greater than 30 centimeters (no wall found nearby),
  //  then set the threshold to 30 centimeters
  if(threshold > 30){
    threshold = 30;
  }

  left_servo.writeMicroseconds(LEFT_FORWARD);
  right_servo.writeMicroseconds(RIGHT_FORWARD);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  leftDistance = (int) leftUltra.read(); 
  rightDistance = (int) rightUltra.read(); 
  frontDistance = (int) frontUltra.read(); 

  leftMedians.addValue(leftDistance);
  rightMedians.addValue(rightDistance);
  frontMedians.addValue(frontDistance);

  leftDistnace = leftMedians.getMedian();
  rightDistnace = rightMedians.getMedian();
  frontDistnace = frontMedians.getMedian();

  if(wall_dir == LEFT){
    if(leftDistance > side_threshold){
      if(frontDistance > front_threshold){
        //We've lost sight of the left wall and there is still 
        //Space to go forward, but we need to turn to follow the wall
        rotateCCW();
      } else {
        //We've lost sight of the left wall and now going forward
        //is blocked too, so we definitely have to turn left
      }
    } else {
      if(frontDistance > front_threshold){
        // All is good
        // Wall is to our left and no wall is blocking us ahead
        //So just keep going stright
      } else {
        //Wall is to the left and front wall is blocking us
        //We'eve reached a dead-end so rotate 180 degrees
        rotateCCW();
        rotateCCW();
      }
    }
  } else {
    if(rightDistance > side_threshold){
      if(frontDistance > front_threshold){
        //We've lost sight of the right wall and there is still 
        //Space to go forward, but we need to turn to follow the wall
        rotateCW();
      } else {
        //We've lost sight of the right wall and now going forward
        //is blocked too, so we definitely have to turn right
      }
    } else {
      if(frontDistance > front_threshold){
        // All is good
        // Wall is to our right and no wall is blocking us ahead
        //So just keep going stright
      } else {
        //Wall is to the right and front wall is blocking us
        //We'eve reached a dead-end so rotate 180 degrees
        rotateCW();
        rotateCW();
      }
    }
  }
  
  delay(20);
}

void rotateCCW(){
  left_servo.writeMicroseconds(LEFT_BACKWARD);
  right_servo.writeMicroseconds(RIGHT_FORWARD);
  delay(CCW_DELAY);
}

void rotateCW(){
  left_servo.writeMicroseconds(LEFT_FORWARD);
  right_servo.writeMicroseconds(RIGHT_BACKWARD);
  delay(CW_DELAY);
}


