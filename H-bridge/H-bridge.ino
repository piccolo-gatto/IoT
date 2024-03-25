int motorLeftPin = 3;
int motorRightPin = 5;

void setup()
{
  pinMode(motorLeftPin, OUTPUT);
  pinMode(motorRightPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
//  motorControl(1, 255); 
//  delay(2000); 
//  motorControl(0, 128); 
//  delay(2000); 
  
  if (Serial.available()) {
    String input = Serial.readString();
    char command = input[0];
    input.remove(0, 1); 
    int speed = input.toInt();
    if (command == 'l') { 
      motorControl(1, speed);
    } else if (command == 'r') { 
      motorControl(0, speed);
    } else if (command == 's') {
      motorControl(1, 0);
      //motorControl(0, 0);
    }
  }
}

void motorControl(int direction, int speed) {
  if (direction == 1) {
    analogWrite(motorLeftPin, speed); 
    analogWrite(motorRightPin, 0);
    
    Serial.print("Direction: counterclockwise, ");
    Serial.print("Speed: ");
    Serial.println(speed);
  } else {
    analogWrite(motorLeftPin, 0);     
    analogWrite(motorRightPin, speed);
    
    Serial.print("Direction: clockwise, ");
    Serial.print("Speed: ");
    Serial.println(speed);
  }
}

