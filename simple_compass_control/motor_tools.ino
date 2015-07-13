
void moveMotorsWithError() {
 
  leftSpeed = 100;
  rightSpeed = 100;
  
  if (compassEnabled) { 
    if (error > 0) {
      leftSpeed = 100 - abs(error);
      rightSpeed = 100;
    } else { 
      leftSpeed = 100;
      rightSpeed = 100 - abs(error);
    }
  } else {
    leftSpeed = 0; 
    rightSpeed = 0; 
  }
  moveMotors();
 
}

void moveMotors() {
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

