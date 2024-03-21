#define pin3 3
#define pin5 5

void setup() {
  pinMode(pin3, OUTPUT);
  analogWrite(pin3, 0);
  pinMode(pin5, OUTPUT);
  analogWrite(pin5, 0);

  Serial.begin(9600);
}

void control(int direction, int speed){
  if (speed > 0 && speed <= 255) {
    if (direction == 1){
        analogWrite(pin3, speed);
        analogWrite(pin5, 0);
    }
    else if (direction == 2){
        analogWrite(pin3, 0);
        analogWrite(pin5, speed);
    }
    else if (direction == 3){
        analogWrite(pin3, 0);
        analogWrite(pin5, 0);
    }
    else {
      Serial.println("Enter 1, 2 or 3!!!");
    }
  }
    else {
      Serial.println("Enter speed 1-255!!!");
   }
}

void loop() {
  String params = "";
  int direction, speed = 0;
   //Serial.println("Print 1 for left direction, 2 for right direction, 3 for stop");
  //Serial.println("Print speed 1-255");
  
  if (Serial.available() > 0) {
    String params = Serial.readStringUntil(' ');
    
	direction = params.toInt();
    
  	Serial.println(direction);
	params = Serial.readStringUntil('\n');
	speed = params.toInt();
    
  	Serial.println(speed);
  }
 control(direction, speed);
 delay(500);

}