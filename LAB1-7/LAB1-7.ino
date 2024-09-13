const int LED1 = 0;
const int LED2 = 4;
const int LED3 = 16;

unsigned long previousMillisLED1 = 0;
unsigned long previousMillisLED2 = 0;
unsigned long previousMillisLED3 = 0;

const long intervalLED1 = 1000; 
const long intervalLED2 = 2000; 
const long intervalLED3 = 5000; 

int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisLED1 >= intervalLED1) {
    previousMillisLED1 = currentMillis;
    ledState1 = !ledState1; 
    digitalWrite(LED1, ledState1);
  }

  if (currentMillis - previousMillisLED2 >= intervalLED2) {
    previousMillisLED2 = currentMillis;
    ledState2 = !ledState2; 
    digitalWrite(LED2, ledState2); 
  }

  if (currentMillis - previousMillisLED3 >= intervalLED3) {
    previousMillisLED3 = currentMillis;
    ledState3 = !ledState3; 
    digitalWrite(LED3, ledState3);
  }
}
