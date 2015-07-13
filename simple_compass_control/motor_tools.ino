
void moveMotorsWithError() {
  
  leftSpeed = 0;
  rightSpeed = 0;
  
  if (compassEnabled) { 
    leftSpeed = error * -1;
    rightSpeed = error;
  } else {
    leftSpeed = 0; 
    rightSpeed = 0; 
  }
  moveMotors();
 
}
int normalizedMotorVal(int input) {
  if (input > 100) input = 100; 
  if (input < -100) input = -100;
  return input;
}

void moveMotors() {
  leftSpeed = normalizedMotorVal(leftSpeed);
  rightSpeed = normalizedMotorVal(rightSpeed);
  
  leftMotor.writeMicroseconds(map(leftSpeed * -1, -100, 100, 1000, 2000));
  rightMotor.write(map(rightSpeed, -100, 100, 1000, 2000));
 
}

void initMotors() {
  leftMotor.attach(6);
  rightMotor.attach(5);
  
  leftSpeed = 0;
  rightSpeed = 0;
  
  
}


void navigationAlgorithm() {
    correctForMovement(euler.x());  
}

