const int buttonPin1 = 25;
const int buttonPin2 = 26;
const int ledPin = 4;


volatile int count = 0; 
bool ledState = false;

unsigned long lastInterruptTime1 = 0;
unsigned long lastInterruptTime2 = 0;
const unsigned long deDelay = 50;  //กำหนดเวลา

unsigned long previousMillis = 0;
const long interval = 2000;  //2 วิ

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP); 

  attachInterrupt(digitalPinToInterrupt(buttonPin1), inCount, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), deCount, RISING);

  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); // ปิด
}

void loop() {
  unsigned long currentMillis = millis();  //อ่านเวลาปัจจุบัน
  if (currentMillis - previousMillis >= interval) {  //ถ้ามากกว่าหรือเท่ากับ2 วิ
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);  //สลับแสดงผลค่า 1 : 0
  }

  Serial.println(count);

  delay(100); 
}

void inCount() {  //บวกค่า
  unsigned long currentMillis = millis();
  if (currentMillis - lastInterruptTime1 >= deDelay) {
    count++;
    Serial.println("+1");
    lastInterruptTime1 = currentMillis;
  }
}


void deCount() { //ลบค่า
  unsigned long currentMillis = millis();
  if (currentMillis - lastInterruptTime2 >= deDelay) {
    count--;
    Serial.println("-1");
    lastInterruptTime2 = currentMillis;
  }
}