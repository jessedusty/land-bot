void correctForMovement(int heading) {
  
  int degreesError = findDegreesDifference(targetHeading, heading);
  // Start of navigation method 
  
  if (degreesError > 180) degreesError -= 360;
  
  /* This is the "cheap" navigation method that can result in osilations,
     it is a quick test */
     
  error = degreesError * 5;

  moveMotorsWithError();
}

void initNav() {
  targetHeading = 0;
  compassEnabled = false;
}

int findDegreesDifference(int desired, int actual) {
  return ((desired - actual) + 360) % 360;
}


