const int ledPins[] = {13, 14, 27, 26, 25, 33, 32, 19}; // อาร์เรย์สำหรับพินของ LED
const int Button1 = 35; // ปุ่มสำหรับวิ่งไฟจากซ้ายไปขวา
const int Button2 = 34; // ปุ่มสำหรับวิ่งไฟจากขวาไปซ้าย
int buttonState1 = 0;
int buttonState2 = 0;
bool running = false; // ตัวแปรเก็บสถานะการทำงานของ LED
bool direction = true; // ตัวแปรเก็บทิศทางการวิ่งของ LED

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT); // ตั้งค่าพินของ LED เป็น OUTPUT
  }
  pinMode(Button1, INPUT); // ตั้งค่าพินของสวิตช์เป็น INPUT
  pinMode(Button2, INPUT); // ตั้งค่าพินของสวิตช์เป็น INPUT
  Serial.println("Setup complete");
}

void loop() {
  buttonState1 = digitalRead(Button1); // อ่านค่าสถานะของสวิตช์ตัวแรก
  buttonState2 = digitalRead(Button2); // อ่านค่าสถานะของสวิตช์ตัวที่สอง
  // Serial.print(buttonState1);
  // Serial.print(" | ");
  // Serial.println(buttonState2);
  // delay(100);
  if (buttonState1 == HIGH) { // ถ้าสวิตช์ตัวแรกถูกกด
    running = true; // เริ่มวิ่งไฟ LED
    direction = true; // กำหนดทิศทางเป็นซ้ายไปขวา
  }
  
  if (buttonState2 == HIGH) { // ถ้าสวิตช์ตัวที่สองถูกกด
    running = true; // เริ่มวิ่งไฟ LED
    direction = false; // กำหนดทิศทางเป็นขวาไปซ้าย
  }

  if (running) {
    if (direction) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], HIGH); // เปิด LED ทีละดวงจากซ้ายไปขวา
        delay(100);
        digitalWrite(ledPins[i], LOW); // ปิด LED ทีละดวงจากซ้ายไปขวา
        delay(100);
      }
    } else {
      for (int i = 7; i >= 0; i--) {
        digitalWrite(ledPins[i], HIGH); // เปิด LED ทีละดวงจากขวาไปซ้าย
        delay(100);
        digitalWrite(ledPins[i], LOW); // ปิด LED ทีละดวงจากขวาไปซ้าย
        delay(100);
      }
    }
  }
}
