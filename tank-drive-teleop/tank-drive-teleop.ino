/*

XBee Serial Communication Test

*/

#include <Servo.h> 

Servo leftMotor;
Servo rightMotor; 

int leftSpeed; 
int rightSpeed; 

void setup () {
  Serial.begin(115200); 
  Serial1.begin(115200);
  
  Serial.println("Robot Debug");
  Serial1.println("Robot Ready...");
  
  leftMotor.attach(5);
  rightMotor.attach(6);
  
  leftSpeed = 0;
  rightSpeed = 0;
}

void moveMotors() {
 leftMotor.write(map(leftSpeed, -100, 100, 0, 180));
 rightMotor.write(map(rightSpeed, -100, 100, 0, 180));
}

void loop () {
  char character = Serial1.read(); 
  //if (character != -1) Serial.write(character);
  if (character == 'S') {
    Serial1.read();
    Serial.print("Left Speed : ");
    leftSpeed = Serial1.parseInt();
    Serial.print(leftSpeed);
    Serial1.read();
    Serial.print("      Right Speed : ");
    rightSpeed = Serial1.parseInt(); 
    Serial.println(rightSpeed);
    Serial1.read();
    
    moveMotors();
  }
  
  if (character == ';') {
    //Serial.print("   end character\n\r");
    Serial1.write("\n\r"); 
  }
  
  
}


