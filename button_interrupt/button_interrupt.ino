#define BUTTON_PIN 2
#define PRESSED LOW

int counter = 0;
volatile long int press_time = 0;
volatile bool check_button = false;

void setup() {
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  
  cli(); 
  TCCR1A = 0; 
  TCCR1B = 0; 
  TCCR1B |= (1 << CS10); 
  TIMSK1 |= (1 << TOIE1); 
  sei(); 

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), process_button_click, FALLING);
}

ISR(TIMER1_OVF_vect) {
  if (check_button && digitalRead(BUTTON_PIN) == PRESSED) {
    counter++;
    check_button = false;
  }
}

void loop() {
  delay(2000);

  if (counter > 0) {
    Serial.print("Pressed ");
    Serial.print(counter);
    Serial.println(" times");
    counter = 0;
  }
}

void process_button_click() {
  if (!check_button) {
    press_time = millis();
    check_button = true;
  }
}
