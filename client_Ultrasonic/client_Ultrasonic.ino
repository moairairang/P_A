#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi credentials
const char* ssid = "MEAU";
const char* password = "123456789";

// Server URLs
const char* controlServerURL = "http://192.168.4.1/control";
const char* sensorServerURL = "http://192.168.4.1/sensor";

// Button pin definitions
int SWF = 26; // Forward button
int SWB = 27; // Backward button
int SWR = 14; // Right button
int SWL = 12; // Left button

String currentAction = "";
String prevResponse = ""; // Variable to keep track of previous response
bool actionSent = false; // To track if the action has been sent

// OLED display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  
  // Initialize buttons as input with pull-up resistors
  pinMode(SWF, INPUT_PULLUP);
  pinMode(SWB, INPUT_PULLUP);
  pinMode(SWR, INPUT_PULLUP);
  pinMode(SWL, INPUT_PULLUP);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the default I2C address for the OLED
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2);      // Set text size to 2 for larger font
  display.setTextColor(WHITE); // Set text color to white
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected to WiFi");
  display.println(WiFi.localIP());
  display.display();
}

void loop() {
  // Read button states
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

  // Send action to the server only if it changes
  if (action != currentAction) {
    if (action != "stop") {
      sendActionToServer(action);
      actionSent = true;
    } else if (actionSent) {
      sendActionToServer("stop"); // Stop the action when released
      actionSent = false;
    }
    currentAction = action;
  }

  // Get sensor data from the server periodically
  getSensorDataFromServer();

  delay(150);
}

// Function to send action commands to the server
void sendActionToServer(String action) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverPath = String(controlServerURL) + "?action=" + action;

    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Action sent from client: ");
      Serial.println(response);
      
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
    // Display WiFi error on OLED
    display.clearDisplay();
    display.setTextSize(2); // Set a consistent text size for readability
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("WiFi not connected");
    display.display();
  }
}

// Function to get sensor data from the server and display it on the OLED
void getSensorDataFromServer() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(sensorServerURL); // URL to get sensor data
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String sensorData = http.getString();
      Serial.print("Sensor data received: ");
      Serial.println(sensorData);

      // Show display with the current sensor data and action status
      showDisplay(sensorData, currentAction);
    } else {
      Serial.print("Error code while getting sensor data: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
    // Display WiFi error on OLED
    showDisplay("WiFi not connected", "");
  }
}

// Function to update the OLED display with sensor data and action status
void showDisplay(String sensorData, String action) {
  display.clearDisplay();
  display.setTextSize(2); // Increase text size to 2 for better visibility
  display.setTextColor(WHITE);

  // Display sensor data at the top
  display.setCursor(0, 0);
  display.println("Sensor:");
  display.setTextSize(2); // Larger size for the actual data
  display.println(sensorData);

  // Display action status at the bottom
  display.setTextSize(2); // Set text size to 2 for action display
  display.setTextColor(WHITE); // Set text color to white
  display.setCursor(0, SCREEN_HEIGHT - 32); // Position at the bottom
  display.println("Action:");
  display.setTextSize(2); // Larger size for better readability
  display.println(action);
  display.display();
}
