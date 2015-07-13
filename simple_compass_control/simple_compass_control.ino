#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>



/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
   
Adafruit_BNO055 bno = Adafruit_BNO055();

#include <Servo.h> 

Servo leftMotor;
Servo rightMotor; 

int leftSpeed; 
int rightSpeed; 
int error; 
boolean compassEnabled;

int targetHeading; 

void setup(void) 
{
  Serial1.begin(115200);
  Serial1.println("Orientation Sensor Raw Data Test"); Serial1.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial1.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial1.print("Current Temperature: ");
  Serial1.print(temp);
  Serial1.println(" C");
  Serial1.println("");
  
  bno.setExtCrystalUse(true);
  
  initMotors();
  initNav(); 
}


imu::Vector<3> euler; 


void loop(void) 
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  
  readSerial();
  
  euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  
  navigationAlgorithm();
  debugPrint();
  
  
  delay(BNO055_SAMPLERATE_DELAY_MS);
}

