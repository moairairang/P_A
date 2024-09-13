#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "MEAU";
const char* password = "123456789";
AsyncWebServer server(80);


int IN1 = 16;
int IN2 = 17;
int IN3 = 5;
int IN4 = 18;

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

  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("action")) {
      String action = request->getParam("action")->value();
      
      if (action == "forward") {
        forward();
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
      Serial.println("Action recieve: " + action);
    } else {
      request->send(400, "text/plain", "Missing action parameter");
    }
  });
  server.begin();
}

void loop() {

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


void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turning Left");
}


void turnRight() {
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
