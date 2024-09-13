#include <EEPROM.h>
const int leds[] = {12, 13, 14, 15, 16, 17, 18, 19};
const int numLeds = sizeof(leds) / sizeof(leds[0]);

int lastLed = 0;  // เก็บค่าล่าสุดไว้
const int eepromAddrLed = 0;
const int eepromAddrDirection = 1;
const int buttong = 26;
const int buttony = 27; // เพิ่มสวิตช์
bool direction = true; // true: จากซ้ายไปขวา, false: จากขวาไปซ้าย

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttong, INPUT_PULLUP);
  pinMode(buttony, INPUT_PULLUP); // ตั้งค่าสวิตช์เป็น INPUT
  EEPROM.begin(sizeof(lastLed) + sizeof(direction));

  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }

  lastLed = EEPROM.read(eepromAddrLed);
  direction = EEPROM.read(eepromAddrDirection);

  digitalWrite(leds[lastLed], HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(buttony) == LOW) {
    direction = !direction;
    EEPROM.write(eepromAddrDirection, direction);
    EEPROM.commit();
    delay(200); // หน่วงเวลาเพื่อป้องกันการกดหลายครั้ง
  }

  // ตรวจสอบทิศทางการวิ่งของไฟ LED
  if (direction) {
    // จากซ้ายไปขวา
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(leds[lastLed], LOW);
      lastLed = (lastLed + 1) % numLeds;
      digitalWrite(leds[lastLed], HIGH);
      EEPROM.write(eepromAddrLed, lastLed);
      EEPROM.commit();
      Serial.println(i);
      delay(100);
    }
  } else {
    // จากขวาไปซ้าย
    for (int i = numLeds - 1; i >= 0; i--) {
      digitalWrite(leds[lastLed], LOW);
      lastLed = (lastLed - 1 + numLeds) % numLeds;
      digitalWrite(leds[lastLed], HIGH);
      EEPROM.write(eepromAddrLed, lastLed);
      EEPROM.commit();
      Serial.println(i);
      delay(100);
    }
  }
}