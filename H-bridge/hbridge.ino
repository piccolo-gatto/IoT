#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int PIN1 = 0;
const int PIN2 = 1;

void setMotor(int direction, int speed) {
  if (direction == 1) {
    pwm.setPin(PIN1, 255);
    pwm.setPin(PIN2, 0);
  } else {
    pwm.setPin(PIN1, 0);
    pwm.setPin(PIN2, 255);
  }

  pwm.setPWM(PIN1, 0, speed);
  pwm.setPWM(PIN2, 0, speed);
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(200);  
}

void loop() {


  setMotor(1, 50);
  delay(2000);


  setMotor(-1, 150);
  delay(2000);
}
