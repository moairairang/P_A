#include "BluetoothSerial.h"
#include <NewPing.h>

const char *pin = "1234";

BluetoothSerial SerialBT;
String device_name = "TisticMeAu";

int IN1 = 16;
int IN2 = 17;
int IN3 = 5;
int IN4 = 18;

char lastCommand = 'S';

int distance;

#define TRIGGER_PIN 25
#define ECHO_PIN 26
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
}

void loop() {
  distance = sonar.ping_cm();
  SerialBT.println(distance);
  delay(50);
  if (SerialBT.available()) {
    char command = SerialBT.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  if (command == 'F') {
    if (distance > 0 && distance < 10) {
      stopMotors();
    } else {
      forward();
      delay(100);
    }
  } else if (command == 'B') {
    backward();
    delay(100);
  } else if (command == 'L') {
    turnleft();
    delay(100);
  } else if (command == 'R') {
    turnright();
    delay(100);
  } else {
    stopMotors();
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Moving Forward");
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Moving Backward");
}

void turnleft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turning Left");
}

void turnright() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Turning Right");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stopping Motors");
}
