TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;
TaskHandle_t Task5;

const int led1 = 13;
const int led2 = 12;
const int led3 = 14;
const int led4 = 27;

const int vr = 34;
const int buttonPin = 25;
int ledState = LOW;
int buttonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int LED[] = { 2, 0, 4, 16, 17, 5, 18, 19 };

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(led3, ledState);
  pinMode(vr, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,3,&Task1,0);
  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,0);
  xTaskCreatePinnedToCore(Task3code,"Task3",10000,NULL,2,&Task3,0);
  xTaskCreatePinnedToCore(Task4code,"Task4",10000,NULL,2,&Task4,1);
  xTaskCreatePinnedToCore(Task5code,"Task5",10000,NULL,1,&Task5,1);
}
void Task1code(void* pvParameters) {
  for (;;) {
    digitalWrite(led1, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    delay(1000);
  }
}

void Task2code(void* pvParameters) {
  for (;;) {
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    delay(500);
  }
}

void Task3code(void* pvParameters) {
  for (;;) {
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == LOW) {
          ledState = !ledState;
        }
      }
    }
    digitalWrite(led3, ledState);
    lastButtonState = reading;
  }
}

void Task4code(void* pvParameters) {
  for (;;) {
    int val = analogRead(vr);
    val = map(val, 0, 1023, 0, 255);
    analogWrite(led4, val);
    delay(10);
  }
}

void Task5code(void* pvParameters) {
  for (;;) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(LED[i], HIGH);
      delay(100);
      digitalWrite(LED[i], LOW);
      delay(100);
    }
    for (int i = 7; i >= 0; i--) {
      digitalWrite(LED[i], HIGH);
      delay(100);
      digitalWrite(LED[i], LOW);
      delay(100);
    }
  }
}

void loop() {
}
