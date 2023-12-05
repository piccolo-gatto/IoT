#define LED_PIN 11
#define SENSOR_PIN A0
#define TRIG 9
#define ECHO 10

int lower = 0;
int upper = 0;
float offset = 0;
float intercept = 0;
bool flag = false;
float speed_of_sound = 0.0343;

const int requiredDataPercentage = 90;
const int maxGap = 2;
const int delayBetweenReadings = 500;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.println("Enter the range:");

  waitForSerialRange(lower, upper);

  Serial.print(lower);
  Serial.print("...");
  Serial.println(upper);
}

void loop() {
  if (flag == false) {
    calibration(lower, upper);
  } else {
    Serial.print("Distance is: ");
    //Serial.println(dist_sound());
    dist_ir();
    delay(1000);
  }
}

void waitForSerialRange(int &lower, int &upper) {
  while (!Serial.available());

  String input = Serial.readStringUntil('\n');
  sscanf(input.c_str(), "%d %d", &lower, &upper);
}

void calibration(int lower, int upper) {

  bool is_enough_data = false;
  int data_collected = 0;
  int x[100];
  float y[100];  // Массив для хранения данных
  int index = 0;

  digitalWrite(LED_PIN, HIGH);

  while (!is_enough_data) {
    int sensorValue = analogRead(SENSOR_PIN) * 5 / 1024;
    float distance = dist_sound();
    if (distance >= lower && distance <= upper) {
      if (index == 0 || (distance - y[index - 1] <= maxGap)) {
        y[index] = distance;
        x[index] = sensorValue;
          index++;
          data_collected++;
          Serial.println("Data collection in process...");
      }
    }

    if (data_collected > 0 && (data_collected * 100) / (upper - lower + 1) >= requiredDataPercentage) {
      is_enough_data = true;
    }

    delay(delayBetweenReadings);  // Задержка для сбора данных
  }
  digitalWrite(LED_PIN, LOW);  // Выключаем светодиод после сбора данных

  buildModel(x, y, data_collected);
}

float getOffset(int x[], float y[], int n) {
  float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

  for (int i = 0; i < n; ++i) {
    sumX += x[i];
    sumY += y[i];
    sumXY += x[i] * y[i];
    sumX2 += x[i] * x[i];
  }

  float offset = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
  return offset;
}

float getIntercept(int x[], float y[], int n, float offset) {
  float sumX = 0, sumY = 0;

  for (int i = 0; i < n; ++i) {
    sumX += x[i];
    sumY += y[i];
  }

  float intercept = (sumY - offset * sumX) / n;
  return intercept;
}

void buildModel(int signalValues[], float distanceValues[], int dataSize) {
  offset = getOffset(signalValues, distanceValues, dataSize);
  intercept = getIntercept(signalValues, distanceValues, dataSize, offset);
  Serial.print("Model: y = ");
  Serial.print(offset);
  Serial.print(" * x + ");
  Serial.println(intercept);
  flag = true;
}

float dist_sound() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long duration = pulseIn(ECHO, HIGH);
  float distance_cm = duration * speed_of_sound / 2.0;
  return distance_cm;
}

void dist_ir() {
  int sensorValue = analogRead(SENSOR_PIN) * 5 / 1024;
  float dist_cm = sensorValue * offset + intercept;
  Serial.print(dist_cm);
  Serial.println(" cm");
}
