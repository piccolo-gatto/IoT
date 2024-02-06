#define D8 8
#define D9 9
#define D10 10
#define D11 11


void setup() {
  pinMode(D10, INPUT_PULLUP);
  pinMode(D11, INPUT_PULLUP);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int defaultStates[2][2] = {{1, 0}, {0, 1}};
  int states[4] = {0, 0, 0, 0};
  for (int i = 0; i < 2; i++){
      digitalWrite(D8, defaultStates[0][i]);
      digitalWrite(D9, defaultStates[1][i]);
	  int row, col;
      for (int j = 0; j < 4; j++) {
        if (j >= 2) {
			row = digitalRead(D8);
        }
        else {
            row = digitalRead(D9);
        }
        if (j % 2 == 0) {
			col = digitalRead(D10);
        }
        else {
          	col = digitalRead(D11);
        }
        if (row == 0 && col == 0) {
          states[j] = 1;
        }
      }
      delay(50);
  }
  int currentStates[4] = {0, 0, 0, 0};
  bool check = true;
  for (int i = 0; i < 4; i++){
    if (currentStates[i] != states[i]){
      check = false;
    }
  }
  if (check == false) {
  for (int i = 0; i < 4; i++) {
    Serial.print("Button ");
    Serial.print(i + 1);
    Serial.print(" ");
    if (states[i] == 1) {
      Serial.println("ON ");
    }
    else {
      Serial.println("OFF ");
    }
    currentStates[i] = states[i];
  }
  Serial.println(" ");
  }

}