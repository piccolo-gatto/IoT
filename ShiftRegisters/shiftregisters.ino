int latchPin = 5;
int clockPin = 3;
int dataPin = 7;

byte digits[10] = {
	0b11011101,	// 0
	0b01010000,	// 1
	0b11001110,	// 2
	0b11011010,	// 3
	0b01010011,	// 4
	0b10011011,	// 5
	0b10111111,	// 6
	0b11010000,	// 7
	0b11011111,	// 8
	0b11111011	// 9
};

int minutes = 0;
int seconds = 0;

void setup() {
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	digitalWrite(clockPin, LOW);
  	//digitalWrite(latchPin, HIGH);
	for(int i = 0; i < 10; i++){
		show_number(i);
		delay(500);
	}
	Serial.begin(9600);
}

void show_time(int m, int s) {
	show_number(m / 10);
	delay(5);
	show_number(m % 10);
	delay(5);
	show_number(s / 10);
	delay(5);
	show_number(s % 10);
	delay(5);
}

void show_number(int digit) {
	digitalWrite(latchPin, LOW);
	if (digit < 0 or digit > 9) {
		return;
	}
	shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);
	digitalWrite(latchPin, HIGH);
}

void loop() {
	if (Serial.available() >= 5) {
		String user_input = Serial.readStringUntil(':');
		minutes = user_input.toInt();
		user_input = Serial.readStringUntil('\n');
		seconds = user_input.toInt();


		for (int i = 0; i < 3600; ++i) {
			show_time(minutes, seconds);
			delay(1000);

			if (++seconds == 60) {
				seconds = 0;
				if (++minutes == 60) {
					minutes = 0;
				}
			}
		}
	}
}
