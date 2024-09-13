int LED[] = { 14, 27, 26, 25, 17, 16, 18, 19 };
int SW1 = 12;
void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  pinMode(SW1, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(SW1) == 1) {}
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED[i], HIGH);
    delay(200);
    digitalWrite(LED[i], LOW);
    delay(200);
  }
  while (digitalRead(SW1) == 1) {}
  for (int i = 7; i >= 0; i--) {
    digitalWrite(LED[i], HIGH);
    delay(200);
    digitalWrite(LED[i], LOW);
    delay(200);
  }
}
