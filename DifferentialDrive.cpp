/*  
*   Constructor Parameters 
*   ( pins[rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB], rightDefaultSpeed, leftDefaultSpeed ) 
*   
*/    

DifferentialDrive::DifferentialDrive() {

}

DifferentialDrive(int pins[],int rDS, int lDS) {
  rightMotorEnable = pins[0];
  rightMotorDirF = pins[1];
  rightMotorDirB = pins[2];
  
  leftMotorEnable = pins[3];
  leftMotorDirF = pins[4];
  leftMotorDirB = pins[5];

  rigthDefaultSpeed = rDS;
  leftDefaultSpeed = lDS;
}

void DifferentialDrive::forward(int leftSpeed = leftDefaultSpeed, int rightSpeed = rightDefaultSpeed) {
  //      Right Motor 
  analogWrite(rightMototrEnable, rightSpeed);
  digitalWrite(rightMotorDirF, HIGH);
  digitalWrite(rightMotorDirB, LOW);
  //      Left Motor 
  analogWrite(leftMototrEnable, leftSpeed);
  digitalWrite(leftMotorDirF, HIGH);
  digitalWrite(leftMotorDirB, LOW);      
}

void DifferentialDrive::backward(int leftSpeed = leftDefaultSpeed, int rightSpeed = rightDefaultSpeed) {
  //      Right Motor 
  analogWrite(rightMototrEnable, rightSpeed);
  digitalWrite(rightMotorDirF, LOW);
  digitalWrite(rightMotorDirB, HIGH);
  //      Left Motor 
  analogWrite(leftMototrEnable, leftSpeed);
  digitalWrite(leftMotorDirF, LOW);
  digitalWrite(leftMotorDirB, HIGH);      
}

void DifferentialDrive::left(int leftSpeed = leftDefaultSpeed, int rightSpeed = rightDefaultSpeed) {
  //      Right Motor 
  analogWrite(rightMototrEnable, rightSpeed);
  digitalWrite(rightMotorDirF, LOW);
  digitalWrite(rightMotorDirB, HIGH);
  //      Left Motor 
  analogWrite(leftMototrEnable, leftSpeed);
  digitalWrite(leftMotorDirF, HIGH);
  digitalWrite(leftMotorDirB, LOW);      
}

void DifferentialDrive::right(int leftSpeed = leftDefaultSpeed, int rightSpeed = rightDefaultSpeed) {
  //      Right Motor 
  analogWrite(rightMototrEnable,rightSpeed);
  digitalWrite(rightMotorDirF,HIGH);
  digitalWrite(rightMotorDirB,LOW);
  //      Left Motor 
  analogWrite(leftMototrEnable,leftSpeed);
  digitalWrite(leftMotorDirF,LOW);
  digitalWrite(leftMotorDirB,HIGH);      
}

void DifferentialDrive::stop() {
  //      Right Motor 
  analogWrite(rightMototrEnable,0);
  digitalWrite(rightMotorDirF,0);
  digitalWrite(rightMotorDirB,LOW);
  //      Left Motor 
  analogWrite(leftMototrEnable,0);
  digitalWrite(leftMotorDirF,LOW);
  digitalWrite(leftMotorDirB,LOW);      
}