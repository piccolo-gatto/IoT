#include <SoftwareSerial.h>

#define START_PIN 2
#define END_PIN 9

SoftwareSerial next_node(10, 11);
int num_node = 0;

bool digits[10][8] = {
  {1,1,0,1,1,1,0,1},  // 0
  {0,1,0,1,0,0,0,0},  // 1
  {1,1,0,0,1,1,1,0},  // 2
  {1,1,0,1,1,0,1,0},  // 3
  {0,1,0,1,0,0,1,1},  // 4
  {1,0,0,1,1,0,1,1},  // 5
  {1,0,1,1,1,1,1,1},  // 6
  {1,1,0,1,0,0,0,0},  // 7
  {1,1,0,1,1,1,1,1},  // 8
  {1,1,1,1,1,0,1,1}   // 9
};

void setup() {
  for(int i = START_PIN; i <= END_PIN; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.begin(4800);
  next_node.begin(4800);
  num_node = 1; //write code to define it
}

void loop() {
  if(Serial.available() >= num_node) {
    char user_input = Serial.read();
    int digit = (int)(user_input - '0');
    if (digit >= 0 && digit <= 9) {
      show_digit(digit);
      if (num_node == 1) {
        delay(100);
        while (Serial.available()) {
          Serial.read();
        }
      }
      while (Serial.available()) {
        char received_char = Serial.read();
        next_node.write(received_char);

        if (received_char == 'n') {
          int neighbors_count = num_node - 1;
          char response_char = neighbors_count + '0';
          next_node.write(response_char);
        }
      }
    }
  }
}

void show_digit(int digit) {
  if (digit < 0 || digit > 9) {
    return;
  }
  for(int i = START_PIN; i <= END_PIN; i++) {
    digitalWrite(i, !digits[digit][i - START_PIN]);
    }
}
