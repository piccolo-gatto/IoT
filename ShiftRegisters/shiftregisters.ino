// Latch pin (ST_CP) of 74HC595 to pin 5
int latchPin = 5;      
// Latch pin (SH_CP) of 74HC595 to pin 6
int clockPin = 3;
// Data pin (DS of 74HC595 to pin 6
int dataPin = 7;       
// Make sure MR is HIGH (connect ot Vcc)

// 2 3 4 5 6 7 8 9 
// A B . C D E G F
//bool digits[10][8] = {
//  {1,1,0,1,1,1,0,1},  // 0
//  {0,1,0,1,0,0,0,0},  // 1
//  {1,1,0,0,1,1,1,0},  // 2
//  {1,1,0,1,1,0,1,0},  // 3
//  {0,1,0,1,0,0,1,1},  // 4
//  {1,0,0,1,1,0,1,1},  // 5
//  {1,0,1,1,1,1,1,1},  // 6
//  {1,1,0,1,0,0,0,0},  // 7
//  {1,1,0,1,1,1,1,1},  // 8
//  {1,1,1,1,1,0,1,1}   // 9
//};

byte digits[10] = {
  0b11011101, // 0
  0b01010000, // 1
  0b11001110, // 2
  0b11011010, // 3
  0b01010011, // 4
  0b10011011, // 5
  0b10111111, // 6
  0b11010000, // 7
  0b11011111, // 8
  0b11111011  // 9
};

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  //digitalWrite(latchPin, HIGH);
  for (int i = 0; i < 10; i++){
  	show_number(i);
    delay(500);
  }
  Serial.begin(9600);
}

void show_number(int digit) {
  digitalWrite(latchPin, LOW);
  if(digit <0 or digit >9) {
    return;
  }
  
  shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);
  //for(int i = 7; i >=0; i--) {
  //  shift_and_set(digits[digit][i]);
  //}
  digitalWrite(latchPin, HIGH);
}

void loop() 
{
  if (Serial.available()) {
    char user_input = Serial.read(); 
    int digit = (int)(user_input - '0');
    show_number(digit);
  }
}


void shift_and_set(bool val) {
  digitalWrite(dataPin, val);
  digitalWrite(clockPin, HIGH);
  delay(10);
  digitalWrite(clockPin, LOW);
}
