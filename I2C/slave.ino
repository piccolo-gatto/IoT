//slave
#include <Wire.h>

#define PHOTO_RES_IN A0
#define I2C_ADDRES 9
#define LED_PIN 13


int* x;
int* y;
int max_records = 0;
int min = -1;
int max = -1;
int current = 0;
long start = 0;
bool state = HIGH;
bool started = false;
bool show = false;


void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Slave");
  Wire.begin(I2C_ADDRES);
  Wire.onReceive(getData);
}


float interpolation(int x_new) {
    int i = 0;
    while (i < current - 1 && x[i + 1] < x_new) {
        i++;
    }
    int x0 = x[i];
    int y0 = y[i];
    int x1 = x[i + 1];
    int y1 = y[i + 1];
    return y0 + (y1 - y0) * (x_new - x0) / (x1 - x0);
}


void loop() {
  if (started) {
      blinked(start, state);
    }
  if (Serial.available() && Serial.read()) {
      show = !show;
  }
  if (show) {
    if (max_records != 0) {
      Serial.print("Calibrated value: ");
      Serial.println(interpolation(analogRead(PHOTO_RES_IN)));
    } else {
      Serial.print("Value: ");
      Serial.println(analogRead(PHOTO_RES_IN));
    }
  }
}

void getData(int length){
  while (0 < Wire.available()){
    auto result = Wire.read();
    if (result == 's') {
      Serial.println("Calibration finished");
      started = false;
      digitalWrite(LED_PIN, HIGH);
      return;
    } else 
    if (result == 'c') {
      started = true;
      current = 0;
      Serial.println("Calibration started");
    } else {
      if (current < max_records && started){
        x[current] = analogRead(PHOTO_RES_IN);
        y[current] = result * 5;
        current += 1;
        Serial.println("Calibrating...");
       }
  }
}
}

void blinked(long &start, bool &state) {
  long end = millis();
  if (end - start > 70) {
    digitalWrite(LED_PIN, state);
    state = !state;
    start = end;
  }
}