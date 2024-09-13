int LED1 = 16;
int LED2 = 5;
int SW1 = 17;
const long interval = 5000;
unsigned long previousmillis = 0;
int buttonState;            
int lastButtonState = LOW;  
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;   
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  Serial.begin(9600);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}
void loop() {
  while (digitalRead(SW1) == 1) {}
  while (digitalRead(SW1) == 0) {
    unsigned long currentmillis = millis();
    if (currentmillis - previousmillis >= interval) {
      previousmillis = currentmillis;
      Serial.println("All off"); 
      Mode3();
      while(digitalRead(SW1) == 0){}
      while(digitalRead(SW1) == 1){}
    } else {
      Serial.println("Mode 1");
      Mode1();
    }
  }
  while(digitalRead(SW1) == 1){
    Serial.println("Mode 1");
    Mode1();
    }
  while (digitalRead(SW1) == 1) {}
  while(digitalRead(SW1) == 0){
    unsigned long currentmillis = millis();
    if (currentmillis - previousmillis >= interval) {
      previousmillis = currentmillis;
      Serial.println("All off");
      Mode3();
      while(digitalRead(SW1) == 0){}
      while(digitalRead(SW1) == 1){}
    } else {
      Serial.println("Mode 2");
      Mode2();
    }
  }
  while(digitalRead(SW1) == 1){
    Serial.println("Mode 2");
    Mode2();
    }
}


void Mode1(){
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
}
void Mode2(){
  digitalWrite(LED2,HIGH);
  digitalWrite(LED1,LOW);
}
void Mode3(){
  digitalWrite(LED2,LOW);
  digitalWrite(LED1,LOW);
}