#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
    
   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
   
Adafruit_BNO055 bno = Adafruit_BNO055();

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/

#include <Servo.h> 

Servo leftMotor;
Servo rightMotor; 

int leftSpeed; 
int rightSpeed; 
int error; 
boolean compassEnabled;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");
  
  bno.setExtCrystalUse(true);
  
  initMotors();
}

void initMotors() {
  leftMotor.attach(6);
  rightMotor.attach(5);
  
  leftSpeed = 0;
  rightSpeed = 0;
  
  
}

void correctForMovement(int heading) {
  // fix to make current heading 0 (less -, more +)
  if (heading > 180) heading -= 360;
  
  // Start of navigation method 
  
  /* This is the "cheap" navigation method that can result in osilations,
     it is a quick test */
  
  error = heading * 10;

  moveMotorsWithError();
  
  
}

void moveMotorsWithError() {
  
  leftSpeed = 100;
  rightSpeed = 100;
  
  if (error > 0) {
    leftSpeed = 100 - abs(error);
    rightSpeed = 100;
  } else { 
    leftSpeed = 100;
    rightSpeed = 100 - abs(error);
  }
  
  
  

  moveMotors();
 
}

void moveMotors() {
  leftMotor.writeMicroseconds(map(leftSpeed * -1, -100, 100, 1000, 2000));
  rightMotor.write(map(rightSpeed, -100, 100, 1000, 2000));
 
}
  

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void) 
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
  

  correctForMovement(euler.x()); 
  
  Serial.print(" Error: "); 
  Serial.print(error);

  Serial.print(" Left: ");
  Serial.print(leftSpeed);
  Serial.print(" Right: ");
  Serial.print(rightSpeed);
  
  Serial.println(""); 

  /*
  // Quaternion data
  imu::Quaternion quat = bno.getQuat();
  Serial.print("qW: ");
  Serial.print(quat.w(), 4);
  Serial.print(" qX: ");
  Serial.print(quat.y(), 4);
  Serial.print(" qY: ");
  Serial.print(quat.x(), 4);
  Serial.print(" qZ: ");
  Serial.print(quat.z(), 4);
  Serial.println("");
  */
  
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
