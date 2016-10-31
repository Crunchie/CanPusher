#include "AFMotor.h"

#define DEBUG 1

#define SENSOR_LEFT 0
#define SENSOR_RIGHT 1

#define SEARCH_SPEED 140

#define SENSOR_THRESHOLD 980

AF_DCMotor left_motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor right_motor(1, MOTOR12_64KHZ);

AF_DCMotor left_spinner(4, MOTOR34_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor right_spinner(3, MOTOR34_64KHZ);

int leftTriggered;
int rightTriggered;

void doDebug(int v);
void checkSensors();

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  right_motor.setSpeed(SEARCH_SPEED);     // set the speed to 200/255
  right_motor.run(FORWARD);
  
  left_motor.setSpeed(SEARCH_SPEED);     // set the speed to 200/255
  left_motor.run(FORWARD);

  left_spinner.setSpeed(200);
  left_spinner.run(BACKWARD);
  right_spinner.setSpeed(200);
  right_spinner.run(FORWARD);

  
  randomSeed(analogRead(3));
  leftTriggered = 0;
  rightTriggered = 0;
}

void loop()
{


  checkSensors();

  int error;
  if(rightTriggered)
  {
    right_motor.setSpeed(100);
    left_motor.setSpeed(50);

    right_motor.run(FORWARD);
    left_motor.run(BACKWARD);

    delay(random(100, 900));
  }
  else if(leftTriggered)
  {
    right_motor.setSpeed(50);
    left_motor.setSpeed(100);

    right_motor.run(BACKWARD);
    left_motor.run(FORWARD);

    delay(random(100,900));
  }
  if(Serial.available()){
    error = Serial.read();
  }
  //Serial.println(error);
  right_motor.setSpeed(SEARCH_SPEED);
  left_motor.setSpeed(SEARCH_SPEED);

  right_motor.run(FORWARD);
  left_motor.run(FORWARD);
  
}

void checkSensors()
{
    int left = analogRead(SENSOR_LEFT);
    int right = analogRead(SENSOR_RIGHT);
    
    doDebug(left);
    doDebug(right);
    
    static int rightCount = 0;
    static int leftCount = 0;
  
    //Right Sensor hysterysis
    if(right > SENSOR_THRESHOLD)
    {
        if(!rightTriggered)
        {
            rightCount++;
            if(rightCount > 5)
            {
                rightTriggered = true;
            }
        }
    }
    else
    {
        if(rightTriggered)
        {
            rightCount--;
            if(rightCount == 0)
            {
                rightTriggered = false;
            }
        }
    }
    
    // Left Sensor
    if(left > SENSOR_THRESHOLD)
    {
        if(!leftTriggered)
        {
            leftCount++;
            if(leftCount > 5)
            {
                leftTriggered = true;
            }
        }
    }
    else
    {
        if(leftTriggered)
        {
            leftCount--;
            if(leftCount == 0)
            {
                leftTriggered = false;
            }
        }
    }
}

void doDebug(int v)
{
#ifdef DEBUG
    Serial.println(v);
#endif
}