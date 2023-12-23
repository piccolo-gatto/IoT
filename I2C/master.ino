//master
#include <Wire.h>

#define PHOTO_RES_IN A0
#define SLAVE_ADDRES 9
#define RESPONSE_SIZE 1



int previous = -1;
int cntr = 0;
int records = 0;
int min = -1;
int max = -1;
bool min_range = false;
bool max_range = false;
bool calibration = false;
bool send = false;
bool stop = false;
bool show = false;




void setup() {
  pinMode(PHOTO_RES_IN, INPUT);
  Serial.begin(9600);
  Serial.println("Master");
  Wire.begin();
}

void loop() {
   if (show) {
      Serial.print("Source value: ");
      Serial.println(analogRead(PHOTO_RES_IN));
      delay(500);
    }

  if (Serial.available()) {
     if (Serial.read() == 's') {
      show = !show;
    }

    if (Serial.read() == 'c') {
      if (min == -1) {
        min = analogRead(PHOTO_RES_IN) + 10;
        Serial.println("Input 'c'");
      } else if (max == -1) {
        max = analogRead(PHOTO_RES_IN) - 10;
        calibration = true;

        Wire.beginTransmission(SLAVE_ADDRES);
        Wire.write('r');
        records  = (int)((max - min + 1) / 10);
        Wire.write(records);
        Serial.print("Records: ");

        Serial.println(records);


        Wire.endTransmission(SLAVE_ADDRES);
        Serial.println(min);
        Serial.println(max);
        Serial.println("Calibration started");
        delay(5000); 
      }
    }
  }
  if (calibration) {
    Wire.beginTransmission(SLAVE_ADDRES);
    if (!send) {
      Wire.write("c");
      send = true;
    }
    if (send && !stop){
      int res = analogRead(PHOTO_RES_IN);
      if (res <= min && !min_range) {
        min_range = true;
      }
      if (res >= min && !max_range) {
        max_range = true;
      }


      if (res - previous >= 10){
        Serial.print("Value: ");
        Serial.println(analogRead(PHOTO_RES_IN));
        Wire.write((int)(res / 5));
        previous = res;
        cntr += 1;
      }
      Wire.endTransmission(SLAVE_ADDRES);

      if (previous == -1){
        previous = res;
      }
    }
    if (min_range && max_range && cntr >= records) {
      calibration = false;
      send = false;
      stop = false;
      min = -1;
      max = -1;
      Wire.beginTransmission(SLAVE_ADDRES);
      Wire.write('s');
      Wire.endTransmission(SLAVE_ADDRES);
      Serial.println("Calibration finished");
    }
  }
}