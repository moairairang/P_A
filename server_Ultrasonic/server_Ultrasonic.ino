#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <NewPing.h>
#include <HTTPClient.h>

const char* ssid = "MEAU";
const char* password = "123456789";
AsyncWebServer server(80);

int distance;
#define TRIGGER_PIN 25
#define ECHO_PIN 26
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int IN1 = 16;
int IN2 = 17;
int IN3 = 5;
int IN4 = 18;

String action;

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  Serial.print("Setting AP...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Server setup to control robot actions
  server.on("/control", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam("action")) {
      action = request->getParam("action")->value();

      if (action == "forward") {
        if (distance > 0 && distance < 10) {
          stopMotors();
        } else {
          forward();
        }
      } else if (action == "backward") {
        backward();
      } else if (action == "left") {
        turnLeft();
      } else if (action == "right") {
        turnRight();
      } else if (action == "stop") {
        stopMotors();
      }

      // Send back the action received
      request->send(200, "text/plain", action);
      Serial.println("Action received: " + action);
    } else {
      request->send(400, "text/plain", "Missing action parameter");
    }
  });

  // Server setup to send sensor data
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest* request) {
    distance = sonar.ping_cm();
    String distanceStr = String(distance);
    request->send(200, "text/plain", distanceStr);
    Serial.println("Sensor data sent: " + distanceStr);
  });

  server.begin();
}

void loop() {
  distance = sonar.ping_cm();
  //Serial.println("Distance: " + String(distance) + " cm");
  delay(150);
  if(action == "forward") {
    if (distance > 0 && distance < 10) {
      stopMotors();
    }
  }
}

// Function to move forward
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Moving Forward");
}

// Function to move backward
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Moving Backward");
}

// Function to turn left
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turning Left");
}

// Function to turn right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Turning Right");
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stopping Motors");
}
