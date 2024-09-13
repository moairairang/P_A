const int ledPin = 25;
const int touchPin = 4; // Touch sensor pin 4 (T4 corresponds to GPIO4 on ESP32)
const int threshold = 30; // Adjust this value based on your sensor's sensitivity
const int debounceDelay = 10; // Debounce time in milliseconds
const int freq = 5000; //frequency of led
const int ledChannel = 0;// led channel
const int resolution = 12;

int touchValue = 0;
int lastTouchValue = 0;
unsigned long lastDebounceTime = 0;
bool touchState = false; // Current state of touch sensor
bool lastTouchState = false; // Last state of touch sensor
bool ledState = false; // Current state of LED

void setup() {
  Serial.begin(115200);
  touchAttachInterrupt(touchPin, NULL, threshold);
  delay(1000); // Give some time to initialize
  
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  touchValue = touchRead(touchPin);

  // Check if the touch value has changed
  if (touchValue != lastTouchValue) {
    lastDebounceTime = millis();
  }

  // If the reading has been stable for debounceDelay, consider it the actual state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Update the touch state
    touchState = touchValue < threshold;

    // Only toggle the LED state if the touch state has changed
    if (touchState != lastTouchState) {
      if (touchState) {
        Serial.println("Touch detected");
        ledState = !ledState; // Toggle the LED state
        ledcWrite(ledChannel, ledState ? 4095 : 0); // 4095 is the max value for 12-bit resolution
      }
      lastTouchState = touchState;
    }
  }

  // Save the last touch value
  lastTouchValue = touchValue;

  delay(10); // Small delay to avoid excessive CPU usage
}
