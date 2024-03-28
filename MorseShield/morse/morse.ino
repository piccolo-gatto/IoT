#define PIN_LATCH 8
#define PIN_DATA 11
#define PIN_CLOCK 12
#define PIN_TUMBLER 13
#define PIN_POT A0

#define PIN_TRANSMITTER 9
#define PIN_RECEIVER 10

#define TRANSMITTER 1
#define RECEIVER 0


int mode = 0; //0 - transmitter, 1 - receiver
int time = 0;
String textMessage = "";
String morseMessage = "";


char letters[] = {
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z',
  ' '
};
String morse[] = {
  ".-", //  A
  "-...", //  B
  "-.-.", //  C
  "-..", //  D
  ".", //  E
  "..-.", //  F
  "--.", //  G
  "....", //  H
  "..", //  I
  ".---", //  J
  "-.-", //  K
  ".-..", //  L
  "--", //  M
  "-.", //  N
  "---", //  O
  ".--.", //  P
  "--.-", //  Q
  ".-.", //  R
  "...", //  S
  "-", //  T
  "..-", //  U
  "...-", //  V
  ".--", //  W
  "-..-", //  X
  "-.--", //  Y
  "--.." //  Z
};
String start = "";

byte digits[] = {
  0b11101110, //  A
  0b11011111, //  B
  0b10011010, //  C
  0b11011101, //  D
  0b01010000, //  E
  0b10001110, //  F
  0b01000000, //  G
  0b0101110, //  H
  0b01010000, //  I
  0b01111000, //  J
  0b10101110, //  K
  0b01110000, //  L
  0b10101100, //  M
  0b00101100, //  N
  0b11011101, //  O
  0b11001110, //  P 
  0b11111011, //  Q
  0b00001100, //  R
  0b10011011, //  S
  0b00011110, //  T
  0b01111010, //  U
  0b111000, //    V
  0b1010110, //   W
  0b01101110, //  X
  0b01110110, //  Y
  0b11011100, //  Z
  0b00000000, //empty 
};

void setup() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_TUMBLER, INPUT);
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_TRANSMITTER, OUTPUT);
  pinMode(PIN_RECEIVER, INPUT);

  Serial.begin(9600);
  if (digitalRead(PIN_TUMBLER) == 1) {
    Serial.println("TRANSMITTER ");
    mode = TRANSMITTER;
  } else {
    mode = RECEIVER;
    Serial.println("RECEIVER ");
  }
}

void loop() {
  if (digitalRead(PIN_TUMBLER) != mode) {
    mode = digitalRead(PIN_TUMBLER);
  }
  time = analogRead(PIN_POT);
  if (mode == RECEIVER) {
    
    fromMorse();
  } else {
    
    toMorse("EGO");
  }
}

void setDisplay(int index) {
  Serial.println("я зашёл сюда");
  digitalWrite(PIN_LATCH, LOW);
  shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, digits[index]);
  digitalWrite(PIN_LATCH, HIGH);
}

String decode(String morseMessage) {
  String message = "";
  String letter = "";
  for (int i = 0; i < morseMessage.length(); i++) {
    char current = i < morseMessage.length() ? morseMessage.charAt(i) : ' ';
    if (current != ' ' && current != '_') {
      letter += current;
    } else {
      char recognized;
      for (int j = 0; j < 25; j++) {
        if (letter == morse[j]) {
          recognized = letters[j];
          break;
        }
      }
      if (letter.length() != 0) {
        if (current == '_') {
        	message += " ";
      }
        else {
        	message += recognized;
        }
        letter = "";
      }

    }
  }

  return message;
}


void fromMorse(){
  
  //setDisplay(26);
  int count = 0;
  while(digitalRead(PIN_RECEIVER) == HIGH) {
    delay(time);
    count++;

    
    //Serial.println(count);  //для отладки
  }
  

       
      
  
    if (count == 3) {
    morseMessage += " ";
  } else if (count == 7) {
    morseMessage += "_";
  } else if (count > 7) {
    Serial.println(count);
    textMessage += decode(morseMessage) + " ";
    //morseMessage = "";
        if (count > 10){
      for (int i = 0; i < textMessage.length(); i++) {
      for (int j = 0; j < 27; j++) {
    	if (letters[j] == textMessage[i]) {
      Serial.print("leter "); //для отладки
      Serial.println(letters[j]); //для отладки
      setDisplay(j); //для отладки
          
                Serial.print("digit "); //для отладки
      Serial.println(j); //для отладки
           //break;
        }

      }     
        
		 delay(1000);
        	textMessage = "";
      break;
        }
      }
  }

    int signal = 0;
  	while (digitalRead(PIN_RECEIVER) == LOW) {
      
    	delay(time);
    	signal++;
  }
Serial.println(signal);
  if (signal == 1) {
    morseMessage += '.';
  } else if (signal == 3) {
    morseMessage += '-';
  }
  Serial.print("Message ");
  Serial.println(morseMessage); //для отладки
  Serial.println(textMessage); //для отладки
  delay(time);
  
}

void blick(int timeStop) {
  digitalWrite(PIN_TRANSMITTER, LOW);
  delay(timeStop * time);
  digitalWrite(PIN_TRANSMITTER, HIGH);
  delay(1 * time);
}

void toMorse(String message){
  String data = message;
  data.toUpperCase();
  for (int i = 0; i < data.length(); i++) {
    char letter = data.charAt(i);
    if (letter == ' ') {
      delay(7 * time);
    } else {
      for (int j = 0; j < 25; j++) {
        if (letters[j] == letter) {
          	String code = morse[j];
            for (int k = 0; k < code.length(); k++) {
    			if (code[k] == '.') {
					blick(1);
    			} else if (code[k] == '-') {
					blick(3);
    			} else if (code[k] == ' ') {
					blick(7);
    			} else {
					blick(2);
    			}
              }
      			Serial.print("Morse: ");
      			Serial.println(code); //для отладки
  			
          
      delay(3 * time);
      break;
        }
      }
    }
  }
  delay(8 * time);
}
