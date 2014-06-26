#include "AFMotor.h"

#define SENSOR_LEFT 0
#define SENSOR_RIGHT 1

#define SEARCH_SPEED 200

#define SENSOR_THRESHOLD 500

AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor1(1, MOTOR12_64KHZ);
void setup() {
  //Serial.begin(9600);           // set up Serial library at 9600 bps
  
  motor1.setSpeed(SEARCH_SPEED);     // set the speed to 200/255
  motor1.run(FORWARD);
  
  motor2.setSpeed(SEARCH_SPEED);     // set the speed to 200/255
  motor2.run(FORWARD);
}

void loop() 
{

	int left = analogRead(SENSOR_LEFT);
	int right = analogRead(SENSOR_RIGHT);

	//Serial.println(left);
	//Serial.println(right);

	boolean off = false;

	if((left > SENSOR_THRESHOLD) || ( right > SENSOR_THRESHOLD))
	{
		off = true;
		motor1.setSpeed(100);
		motor2.setSpeed(180);

		motor1.run(BACKWARD);
		motor2.run(BACKWARD);

		delay(1000);
	} else
	{
		off = false;
		motor1.setSpeed(SEARCH_SPEED);
		motor2.setSpeed(SEARCH_SPEED); 

		motor1.run(FORWARD);
		motor2.run(FORWARD);
	}
  
}