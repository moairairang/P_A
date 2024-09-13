const int potPin = 34;
const int led1 = 27;
const int led2 = 26;
const int led3 = 25;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 12;
// variable for storing the potentiometer value
int potValue = 0;
void setup() {
 Serial.begin(115200);
 ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(27,0);
ledcAttachPin(26,0);
ledcAttachPin(25,0);
}
void loop() {
 // Reading potentiometer value
 potValue = analogRead(potPin);
 Serial.println(potValue);
 ledcWrite(0,potValue);
delay(15);
}