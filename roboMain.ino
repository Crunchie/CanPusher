#include "AFMotor.h"

#define SENSOR_LEFT 0
#define SENSOR_RIGHT 1

#define SEARCH_SPEED 255

#define SENSOR_THRESHOLD 500

AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor1(1, MOTOR12_64KHZ);
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  motor1.setSpeed(SEARCH_SPEED);     // set the speed to 200/255
  motor1.run(FORWARD);
  
  motor2.setSpeed(SEARCH_SPEED);     // set the speed to 200/255
  motor2.run(FORWARD);
  randomSeed(analogRead(3));
}

void loop() 
{

	int left = analogRead(SENSOR_LEFT);
	int right = analogRead(SENSOR_RIGHT);

	//Serial.println(left);
	//Serial.println(right);

	boolean off = false;

        
        int error;
	if(right > SENSOR_THRESHOLD)
	{
		off = true;
		motor1.setSpeed(160);
		motor2.setSpeed(160);

		motor1.run(FORWARD);
		motor2.run(BACKWARD);

		delay(random(500, 2000));
	} else if(left > SENSOR_THRESHOLD)
        {
                off = true;
		motor1.setSpeed(160);
		motor2.setSpeed(160);

		motor1.run(BACKWARD);
		motor2.run(FORWARD);

		delay(random(400,1700));
        }
	{
		off = false;
                if(Serial.available()){
                  error = Serial.read();
                }
                Serial.println(error);
		motor1.setSpeed(SEARCH_SPEED);
		motor2.setSpeed(SEARCH_SPEED); 

		motor1.run(FORWARD);
		motor2.run(FORWARD);
	}
  
}
