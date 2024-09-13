#define interval_1 5000
#define interval_2 50

const int button = 17;
const int led1 = 16;
const int led2 = 5;

bool flg_off = true;
bool flg_mode = false;
bool flg_timer = true;

unsigned long timer = 0;

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}
void loop() {
  while (digitalRead(button) == LOW) {
    if (flg_timer) {
      timer = millis();
      flg_timer = false;
    }

    if (millis() - timer >= interval_1) {
      flg_off = true;
      flg_mode = false;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      Serial.println("Turn Off");
    } else if (millis() - timer >= interval_2) {
      flg_off = false;
      flg_mode = !flg_mode;
      Serial.println("Switch Mode");
      while(digitalRead(button) == LOW) {
        Serial.println(millis() - timer);
        if (millis() - timer >= interval_1) {
          flg_off = true;
          flg_mode = false;
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          Serial.println("Turn Off");
        }
      }
    }
    Serial.println(millis()-timer);
  }
  flg_timer = true;

  if(flg_off == false){
    if(flg_mode){
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
      Serial.println("Switch Mode 1");
    }
    else{
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      Serial.println("Switch Mode 2");
    }
  }
}
