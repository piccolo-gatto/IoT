// #include <iarduino_HC_SR04.h>

#define DIR_RIGHT 4
#define SPEED_RIGHT 5
#define DIR_LEFT 7
#define SPEED_LEFT 6

#define left_sensor_trig 10
#define left_sensor_echo 11

#define forward_sensor_trig 9
#define forward_sensor_echo 3

// #define FD 20
// #define CD 15
// #define JD 15

const int SAFE_DISTANCE_FORWARD = 20; 
const int SAFE_DISTANCE_LEFT = 15;    
const int DEFAULT_VELOCITY = 128;     
const int TURN_DURATION = 500;        
const float Kp = 2;                   // Пропорциональный коэффициент PID
const float Kd = 10;                  // Дифференциальный коэффициент PID
const float ALPHA = 0.2;              // Коэффициент экспоненциального сглаживания
const int WATCHDOG_TIMER_THRESHOLD = 10000; // сторожевой таймер
unsigned long watchdogTimerStart = 0; 

unsigned long previousMillis = 0;
const long period = 2000; // Период для проверки сторожевого таймера


// iarduino_HC_SR04 left_sensor(10, 11);
// iarduino_HC_SR04 forward_sensor(9, 3);


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

void turn_90_degr(int direction){ // направо
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  const long period = 2000; // подобрать время
  if (currentMillis - previousMillis < period and direction==0) {
    previousMillis = currentMillis;
    turn_right(128); // подобрать скорость
  }
  else if (currentMillis - previousMillis < period and direction==1) {
    previousMillis = currentMillis;
    turn_left(128); // подобрать скорость
  }
}

void turn_270_degr(){ // направо
  turn_right(128); // подобрать время и скорость
}


int get_dist(int trig, int echo){
  long duration;
  int distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(3); 

  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig,LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0344 / 2; 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}



enum RobotState {
  FORWARD,
  TURN_RIGHT,
  TURN_LEFT,
  ROTATE_RIGHT,
  ROTATE_LEFT,
  FOLLOW_WALL,
  STOP,
  WATCHDOG_TIMER_TRIGGERED
};

RobotState currState = FORWARD;
float previousError = 0;
float integral = 0;
int ldist; // Объявляем переменную ldist здесь
int fdist; // Объявляем переменную fdist здесь

float error;
float pid_output;

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

  // ручной вариант
  // int ldist = get_dist(left_sensor_trig, left_sensor_echo);
  // int fdist = get_dist(forward_sensor_trig, forward_sensor_trig);

  // библиотечный вариант
  // left_sensor.averaging = 15; // усреднение значений
  // forward_sensor.averaging = 15;
  // int ld2 = left_sensor.distance();
  // int fd2 = forward_sensor.distance();
  
  switch(currState) {
    case FORWARD:

      ldist = get_dist(left_sensor_trig, left_sensor_echo);
      fdist = get_dist(forward_sensor_trig, forward_sensor_trig);

      if (millis() - watchdogTimerStart >= WATCHDOG_TIMER_THRESHOLD) {
        currState = WATCHDOG_TIMER_TRIGGERED;
        break;
      }

      error = SAFE_DISTANCE_LEFT - leftDistance;
      pid_output = pid_controller(error);

      // Если нет препятствия спереди, двигаемся вперед
      if(fdist > SAFE_DISTANCE_FORWARD) {
        move_forward(DEFAULT_VELOCITY);
        currState = FORWARD;
      }
      // Если есть препятствие спереди и слева, поворачиваем направо
      else if (ldist <= SAFE_DISTANCE_LEFT) {
        currState = TURN_RIGHT;
      }
      // Если есть препятствие спереди, но слева свободно, поворачиваем налево
      else {
        // float left_motor_speed = DEFAULT_VELOCITY + pid_output;
        // float right_motor_speed = DEFAULT_VELOCITY - pid_output;
        // move(true, true, left_motor_speed, right_motor_speed);
        // currentState = MOVE_FORWARD;
        currState = TURN_LEFT;
      }
      break;

    case TURN_RIGHT:
      // Поворачиваем направо
      rotate_right(DEFAULT_VELOCITY);
      delay(TURN_DURATION);
      currState = FORWARD; 
      break;

    case TURN_LEFT:
      // Поворачиваем направо
      rotate_left(DEFAULT_VELOCITY);
      delay(TURN_DURATION);
      currState = FORWARD; 
      break;

   
    case STOP:
      stop();
      break;

  case FOLLOW_WALL:
      // Проверяем дистанцию слева
      ldist = get_dist(left_sensor_trig, left_sensor_echo);
      
      // Если нет стены слева, поворачиваем налево
      if(ldist > SAFE_DISTANCE_LEFT) {
        currState = TURN_LEFT;
      }
      // Если стена слева, двигаемся вперед
      else {
        move_forward(DEFAULT_VELOCITY);
        currState = FOLLOW_WALL;
      }
      break;

  default:
        // Действие по умолчанию (например, остановка)
        move_forward(128);
        break;

  }


  // move_forward(255);
  // delay(2000);
  //     // if (current_time - prev_time >= 2000) {
  //     //   prev_time = current_time;
  //     // }
  //     rotate_left(255);
  //     delay(2000);
  //     // if (current_time - prev_time >= 2000) {
  //     //   prev_time = current_time;
  //     // }
  //     move_back(255);
  //     delay(2000);
  //     // if (current_time - prev_time >= 2000) {
  //     //   prev_time = current_time;
  //     // }
  //     rotate_right(255);
  //     delay(2000);
  //     stop();
  //     delay(2000);


  // Serial.println(counter-millis());
  // if (prev_time - millis() < 1250){ 
  //   rotate_left(255);
  // } else{
  //   stop();
  // }
  // move_forward(255);
  // delay(2000);
  // rotate_left(255);
  // delay(2000);
  // move_back(255);
  // delay(2000);
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