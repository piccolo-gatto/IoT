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

void move_forward(int velocity1, int velocity2){
  move(true, true, velocity1, velocity2);
}

void move_back(int velocity1, int velocity2){
  move(false, false, velocity1, velocity2);
}

void rotate_left(int velocity1, int velocity2){
  move(false, true, velocity1, velocity2);
}

void rotate_right(int velocity1, int velocity2){
  move(true, false, velocity1, velocity2);
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
char previous_cmd;

char cmdArr[4] = {FORWARD, BACKWARD, RIGHT, LEFT};
char cmdRot[4] = {TRIANGLE, CIRCLE, CROSS, SQUARE};
int TURN_DURATION[4] = {500, 1000, 1500, 2000};

using CommandsArray = void (*)(int, int);
CommandsArray commands[4] = {move_forward, move_back, rotate_right, rotate_left};

char cmdtmpchar[4] = {' ', ' ', ' ', ' '};
int lsp = 200; // left wheel speed
int rsp = 200; // right wheel speed
int delta_sp = 15; // delta speed changing +-
int delta_rot = 50; // delta time changing + -
int calibrated_left = -1;
int calibrated_right = -1;
int curr_rot = calibrated_right;


bool is_changed = false; 
bool is_plused = false; 
bool is_minused = false; 
bool is_plused_t = false;
bool is_minused_t = false;

void runcmd(char cmd){
  for (int i = 0; i < 4; ++i) {
    if (cmd == cmdtmpchar[i]) {
      commands[i](lsp, rsp);
      return;
    }
  }
  if (calibrated_right != -1 && calibrated_left != -1){
    for (int i = 0; i < 4; ++i) {
        if (cmd == cmdRot[i]) {
          commands[curr_rot](lsp, rsp);
          delay(TURN_DURATION[i]);
          return;
        }
      }
  }
  stop();
}

void calibrate_dir(char cmd){
  if (cmd == TRIANGLE) {
    if (!is_changed) {
      changedir(cmdArr, 4);
      is_changed = true;
    }
  } else if (cmd == CIRCLE) {
    for (int i = 0; i < 4; ++i) {
      if (previous_cmd == cmdArr[i]) {
        cmdtmpchar[i] = previous_cmd;
        if (previous_cmd == RIGHT) {
          calibrated_right = i;
          curr_rot = calibrated_right;
        } else if (previous_cmd == LEFT) {
          calibrated_left = i;
        }
        return;
      }
    }
  } else {
    is_changed = false;
    for (int i = 0; i < 4; ++i) {
      if (cmd == cmdArr[i]) {
        commands[i](lsp, rsp);
        previous_cmd = cmd;
        return;
      }
    }
    stop();
  }
}



void changedir(char arr[], int size) {
  char firstElement = arr[0];
  for (int i = 0; i < size - 1; ++i) {
    arr[i] = arr[i + 1];
  }
  arr[size - 1] = firstElement;
}

void calibrate_sp(char cmd){
  if (cmd == TRIANGLE) {
    if (!is_plused) {
      if (previous_cmd == RIGHT) {
        plus_sp(rsp);
      } else if (previous_cmd == LEFT) {
        plus_sp(lsp);
      }
      is_plused = true;
    }
  } else if (cmd == CROSS) { 
    if (!is_minused) {
      if (previous_cmd == RIGHT) {
        minus_sp(rsp);
      } else if (previous_cmd == LEFT) {
        minus_sp(lsp);
      }
      is_minused = true;
    }
  } else { 
    is_plused = false;
    is_minused = false;
    for (int i = 0; i < 4; ++i) {
      if (cmd == cmdtmpchar[i]) {
        if (cmd != LEFT && cmd != RIGHT) { 
          commands[i](lsp, rsp);
        }
        previous_cmd = cmd;
        return;
      }
    }
    stop();
  }
}


void plus_sp(int sp){
  if (sp + delta_sp <= 255)
    sp += delta_sp;
}

void minus_sp(int sp){
  if (sp - delta_sp >= 5)
    sp -= delta_sp;
}

void calibrate_rot(char cmd){
  if (cmd == FORWARD) {
    if (!is_plused_t) {
      for (int i = 0; i < 4; ++i) {
        if (previous_cmd == cmdRot[i]) {
          TURN_DURATION[i] += delta_rot;
          is_plused_t = true;
          return;
        }
      }
    }
  } else if (cmd == BACKWARD) { 
    if (!is_minused_t) {
      for (int i = 0; i < 4; ++i) {
        if (previous_cmd == cmdRot[i]) {
          if (TURN_DURATION[i] - delta_rot >= 50) {
            TURN_DURATION[i] -= delta_rot;
            is_minused_t = true;
          }
          return;
        }
      }
    }
  } else { 
    is_minused_t = false;
    is_plused_t = false;
    for (int i = 0; i < 4; ++i) {
      if (cmd == cmdRot[i]) {
        commands[curr_rot](lsp, rsp);
        delay(TURN_DURATION[i]);
        previous_cmd = cmd;
        return;
      }
    }
    stop();
  }
}

void choose(){ 
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
      if (curr_rot == calibrated_right) {
        curr_rot = calibrated_left;
      } else {
        curr_rot = calibrated_right;
      }
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


void loop() {
  if (state == NOTHING) {
    // пусто
  } else if (state == MOVE) {
    // проиграть_команду cmd
    runcmd(cmd);} 
    else if (state == DIR) {
    calibrate_dir(cmd);} 
    else if (state == SP) {
    calibrate_sp(cmd);} 
    else if (state == ROT) {
    calibrate_rot(cmd);}

  if(mySerial.available()){
    cmd = mySerial.read();
    choose();
  }
}
