#define DIR_RIGHT 4
#define SPEED_RIGHT 5
#define DIR_LEFT 7
#define SPEED_LEFT 6

#define left_sensor_trig 10
#define left_sensor_echo 11

#define forward_sensor_trig 9
#define forward_sensor_echo 3

// добавить библиотеку NewPing или другую для сенсоров

long int prev_time;
int counter = 0;

void setup(){
  // Serial.begin(counter);
  setupMotorShield();
  counter = millis()+1250;
}

void setupMotorShield(){
    for (int i=4; i<=7; i++){
    pinMode(i, OUTPUT);
  }
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

void stop(){
  move(false, true, 0, 0);
}



void loop(){
  unsigned long current_time = millis();

  // езду по кругу
  move_forward(255);
  delay(2000);
      // if (current_time - prev_time >= 2000) {
      //   prev_time = current_time;
      // }
      rotate_left(255);
      delay(2000);
      // if (current_time - prev_time >= 2000) {
      //   prev_time = current_time;
      // }
      move_back(255);
      delay(2000);
      // if (current_time - prev_time >= 2000) {
      //   prev_time = current_time;
      // }
      rotate_right(255);
      delay(2000);
      stop();
      delay(2000);


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