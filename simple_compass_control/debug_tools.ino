void debugPrint() {
  /* Display the floating point data */
  Serial1.print("X: ");
  Serial1.print(euler.x());
  Serial1.print(" Y: ");
  Serial1.print(euler.y());
  Serial1.print(" Z: ");
  Serial1.print(euler.z());

  Serial1.print(" Error: "); 
  
  Serial1.print(error);
  if (compassEnabled) {
    Serial1.print(" Left: ");
    Serial1.print(leftSpeed);
    Serial1.print(" Right: ");
    Serial1.print(rightSpeed);
  }
  Serial1.println(""); 
}
