#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

#define DIR_RIGHT 4
#define SPEED_RIGHT 5
#define DIR_LEFT 7
#define SPEED_LEFT 6

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C' 
#define CROSS 'X' 
#define TRIANGLE 'T' 
#define SQUARE 'S' 
#define START 'A' 
#define PAUSE 'P' 

#define NOTHING 0
#define DIR 1
#define SP 2
#define ROT 3
#define MOVE 4

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

void turn_left(int velocity){
  move(true, true, velocity, 0); 
}

void turn_right(int velocity){
  move(true, true, 0, velocity);
}

void stop(){
  move(true, true, 0, 0);
}

void setup(){
  Serial.begin(9600);
  setupMotorShield();
  mySerial.begin(9600);
}

int state = NOTHING;
int previous_state = NOTHING;
char cmd;

void loop() {
  if (state == NOTHING) {
    // пусто
  } else if (state == MOVE) {
    // проиграть_команду cmd


  } else if (state == DIR) {
    // откалибровать направления
  } else if (state == SP) {
    // откалибровать скорости колес

  } else if (state == ROT) {
    // откалибровать повороты
  }





  if(mySerial.available()){
    cmd = mySerial.read();
    choose();
  }
}





void choose(){  // переключение режимов калбровки
  if (cmd == START) {
    if (state == NOTHING) {
      state = DIR;
    } else if (state == DIR) {
      state = SP;
    } else if (state == SP) {
      state = ROT;
    } else if (state == ROT) {
      state = DIR;
    } else if (state == MOVE) {
      // для поворотов ...
    }
  } else if (cmd == MOVE) {
    if (state != MOVE) {
      previous_state = state;
      state = MOVE;
    } else if (state == MOVE) {
      state = previous_state;
    }
  }
}
