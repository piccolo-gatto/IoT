#include <iarduino_HC_SR04.h>

#define DIR_RIGHT 4
#define SPEED_RIGHT 5
#define DIR_LEFT 7
#define SPEED_LEFT 6

#define left_sensor_trig 11
#define left_sensor_echo 10
#define forward_sensor_trig 9
#define forward_sensor_echo 8

// #define FD 20
// #define CD 15
// #define JD 15

// const int SAFE_DISTANCE_FORWARD = 25; 
// const int SAFE_DISTANCE_LEFT = 15; 

const int CD = 10;
const int FD = 25;
const int JD = 15;
   
const int DEFAULT_VELOCITY = 255; 
const int TURN_VELOCITY = 150;   
const int TURN_DURATION = 550;    

const float Kp = 2;                   // Пропорциональный коэффициент PID
const float Kd = 10;                  // Дифференциальный коэффициент PID
const float ALPHA = 0.2;              // Коэффициент экспоненциального сглаживания
const int WATCHDOG_TIMER_THRESHOLD = 20000; // сторожевой таймер
unsigned long watchdogTimerStart = 0; 

unsigned long previousMillis = 0;
const long period = 2000; // Период для проверки сторожевого таймера


iarduino_HC_SR04 left_sensor(left_sensor_trig, left_sensor_echo);
iarduino_HC_SR04 forward_sensor(forward_sensor_trig, forward_sensor_echo);


void setupMotorShield(){
    for (int i=4; i<=7; i++){
    pinMode(i, OUTPUT);
  }
}

void setupSensors(){
  pinMode(left_sensor_trig, OUTPUT);
  pinMode(left_sensor_echo, INPUT);
  pinMode(forward_sensor_trig, OUTPUT);
  pinMode(forward_sensor_echo, INPUT);
}

void move(bool rforward, bool lforward, int rvelocity, int lvelocity){
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rvelocity);
  analogWrite(SPEED_LEFT, lvelocity);
}

void move_forward(int velocity){
  move(true, true, velocity, velocity);
}

void move_back(int velocity){
  move(false, false, velocity, velocity);
}

void rotate_left(int velocity){
  move(false, true, velocity, velocity);
}

void rotate_right(int velocity){
  move(true, false, velocity, velocity);
}

void turn_left(int velocity){
  move(true, true, velocity, 0); // возможно velocity/2
}

void turn_right(int velocity){
  move(true, true, 0, velocity);
}

void stop(){
  move(true, true, 0, 0);
}

// void turn_90_degr(int direction){ 
//   unsigned long currentMillis = millis();
//   unsigned long previousMillis = 0;
//   const long period = 2000; // подобрать время
//   if (currentMillis - previousMillis < period and direction==0) {
//     previousMillis = currentMillis;
//     turn_right(DEFAULT_VELOCITY); // подобрать скорость
//   }
//   else if (currentMillis - previousMillis < period and direction==1) {
//     previousMillis = currentMillis;
//     turn_left(DEFAULT_VELOCITY); // подобрать скорость
//   }
// }

// int get_dist(int trig, int echo){
//   long duration;
//   int distance;
//   digitalWrite(trig, LOW);
//   delayMicroseconds(3); 

//   digitalWrite(trig, HIGH); 
//   delayMicroseconds(10); 
//   digitalWrite(trig,LOW);
//   duration = pulseIn(echo, HIGH);
//   distance = duration * 0.0344 / 2; 
//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");
//   return distance;
// }

enum RobotState {
  FORWARD,
  TURN_RIGHT,
  TURN_LEFT,
  ROTATE_RIGHT,
  ROTATE_LEFT,
  CHOOSE,
  STOP,
  WATCHDOG_TIMER_TRIGGERED
};

RobotState currState = FORWARD;

float previousError = 0;
float integral = 0;

int ldist; 
int fdist; 

int ldist_prev=0;

float error;
float pid_output;

// попытки сделать pid 
float pid_controller(float currentError) {
  float derivative = currentError - previousError;
  integral = ALPHA * integral + currentError;
  float output = Kp * currentError + Kd * derivative + integral;
  previousError = currentError;
  return output;
}

void setup(){
  Serial.begin(9600);
  setupMotorShield();
  setupSensors();
  watchdogTimerStart = millis();
}

void loop(){
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  const long period = 2000; 

  // Сторожевой таймер
    if (currentMillis - watchdogTimerStart >= WATCHDOG_TIMER_THRESHOLD) {
        currState = STOP;
    }

  // ручной вариант
  // int ldist = get_dist(left_sensor_trig, left_sensor_echo);
  // int fdist = get_dist(forward_sensor_trig, forward_sensor_trig);

  // библиотечный вариант
  left_sensor.averaging = 15; // усреднение значений
  forward_sensor.averaging = 15;
  int ldist = left_sensor.distance();
  int fdist = forward_sensor.distance();

  // Serial.print('f');
  // Serial.println(fdist);
  // Serial.print('l ');
  // Serial.println(ldist);
  
  
  switch (currState) {
    case FORWARD:
      move_forward(DEFAULT_VELOCITY);
      currState = CHOOSE;
      break;
      
    case TURN_RIGHT:
      turn_right(TURN_VELOCITY);
      if (ldist > CD && ldist < FD && fdist > CD){
        currState = FORWARD;
      }
      break;

    case TURN_LEFT:
      turn_left(TURN_VELOCITY);
      if (ldist > CD && ldist < FD && fdist > CD){
        currState = FORWARD;
      }
      break;
      
    case ROTATE_RIGHT:
      currentMillis = millis();
      while (millis() - currentMillis < TURN_DURATION){
        rotate_right(DEFAULT_VELOCITY);
      } 
      currState = FORWARD;
      break;

    case ROTATE_LEFT:
      currentMillis = millis();
      while(millis() - currentMillis < TURN_DURATION/2){
        move_forward(DEFAULT_VELOCITY);
      } 
      currentMillis = millis();
      while(millis() - currentMillis < TURN_DURATION){
        rotate_left(DEFAULT_VELOCITY);
      } 
      currState = FORWARD;
      break;

    case CHOOSE:
      if (ldist < CD) {
        currState = TURN_RIGHT;
      } else if (ldist > FD && fdist > FD) {
        currState = TURN_LEFT;
      } else if (fdist < CD && CD < ldist && ldist < FD){
        currState = ROTATE_RIGHT;
      } else if (fdist <= CD && ldist > ldist_prev && ldist - ldist_prev > JD){
        currState = ROTATE_LEFT;
      }
      break;

    case STOP:
      stop();
      break;

  }
  ldist_prev = ldist;

}

// код для проверок
// dir 4 7
// speed 5 6
// правильная ли распиновка, если нет то меняем на right
// и определяем high low кто вперед кто назад (и для левого и для правого!)
// #define DIR_RIGHT 4
// #define SPEED_RIGHT 5
// #define DIR_LEFT 7
// #define SPEED_LEFT 6
// void setup(){
//   for (int i=4; i<=7; i++){
//     pinMode(i, OUTPUT);
//   }
//   digitalWrite(DIR_RIGHT, HIGH);
//   digitalWrite(SPEED_RIGHT, 255);
// }
// void loop(){
// }