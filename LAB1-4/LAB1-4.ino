int LED[] = { 2, 0, 4, 16, 17, 5, 18, 19 };
int SW1 = 25;
int SW2 = 26; // New switch on pin 26
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool direction = true;
int buttonState = HIGH; // Initialize buttonState
const int vr = 34; // Potentiometer pin

unsigned long previousMillis = 0;
long interval = 100; // interval at which to blink (milliseconds)
int ledIndex = 0;
bool ledOn = false;
bool paused = false; // Flag to indicate if sequence is paused

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP); // Set SW2 as input with pull-up resistor
  pinMode(vr, INPUT);
  Serial.begin(115200);
}

void loop() {
  int reading = digitalRead(SW1);
  int pauseButton = digitalRead(SW2); // Read state of pause button

  if (pauseButton == LOW) {
    // Toggle pause state
    paused = !paused;
    delay(50); // Debounce delay for button press
  }

  // Only proceed with LED sequence if not paused
  if (!paused) {
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != buttonState) {
        buttonState = reading;

        // only toggle the direction if the new button state is LOW
        if (buttonState == LOW) {
          direction = !direction;
        }
      }
    }

    // Read potentiometer value
    int potValue = analogRead(vr);

    // Map potValue (0-1023) to interval (10-1000 ms)
    interval = map(potValue, 0, 1023, 10, 1000);

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // turn off the previous LED
      if (ledOn) {
        digitalWrite(LED[ledIndex], LOW);
      }

      // update the LED index
      if (direction) {
        ledIndex++;
        if (ledIndex >= 8) {
          ledIndex = 0;
        }v    
      } else {
        ledIndex--;
        if (ledIndex < 0) {
          ledIndex = 7;
        }
      }

      // turn on the current LED
      digitalWrite(LED[ledIndex], HIGH);
      ledOn = true;
    }
  } else {
    // LEDs are paused, turn all off
    for (int i = 0; i < 8; i++) {
      digitalWrite(LED[i], LOW);
    }
    ledOn = false;
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
