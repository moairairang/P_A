#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MEAU";
const char* password = "123456789";
const char* serverURL = "http://192.168.4.1/control";

int SWF = 26; 
int SWB = 27; 
int SWR = 14; 
int SWL = 12;

String currentAction = "";

void setup() {
  Serial.begin(115200);
  pinMode(SWF, INPUT_PULLUP);
  pinMode(SWB, INPUT_PULLUP);
  pinMode(SWR, INPUT_PULLUP);
  pinMode(SWL, INPUT_PULLUP);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  bool forwardPressed = digitalRead(SWF) == LOW;
  bool backwardPressed = digitalRead(SWB) == LOW;
  bool rightPressed = digitalRead(SWR) == LOW;
  bool leftPressed = digitalRead(SWL) == LOW;

  String action = "";
  if (forwardPressed) {
    action = "forward";
  } else if (backwardPressed) {
    action = "backward";
  } else if (rightPressed) {
    action = "right";
  } else if (leftPressed) {
    action = "left";
  } else {
    action = "stop";
  }

  if (action != currentAction) {
    sendActionToServer(action);
    currentAction = action;
  }
  delay(100); 
}
void sendActionToServer(String action) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverPath = String(serverURL) + "?action=" + action;
    
    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Action send by server: ");
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
