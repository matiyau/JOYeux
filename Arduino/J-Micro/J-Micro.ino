#define H0 6
#define H1 7
#define H2 8
#define H3 9

#define V0 10
#define V1 11
#define V2 12
#define V3 13

//Array Of Pins Giving Supply To Key Matrix
uint8_t KEY_H_OUT[] = {H0,H1,H2,H3};

//Array Of Pins Reading State Of Key Matrix
uint8_t KEY_V_IN[] = {V0,V1,V2,V3};

//Array Of Key Map
char KEY_MAP[][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

bool KEY_PRESSED_NOW = false;
bool KEY_PRESSED_PREV = false;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i<4; i++) {
    pinMode(KEY_H_OUT[i], OUTPUT);
    digitalWrite(KEY_H_OUT[i], HIGH);
  }
  for (int i = 0; i<4; i++) {
    pinMode(KEY_V_IN[i], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i<4; i++) {
    for (int j = 0; j<4; j++) {
       digitalWrite(KEY_H_OUT[j], HIGH);
    }
    digitalWrite(KEY_H_OUT[i], LOW);
    for (int j = 0; j<4; j++) {
      if (!digitalRead(KEY_V_IN[j])) {
        KEY_PRESSED_NOW = true;
        if (!KEY_PRESSED_PREV) {
          Serial.println(KEY_MAP[i][j]);
        }
      }
    }
  }
  KEY_PRESSED_PREV = KEY_PRESSED_NOW;
  KEY_PRESSED_NOW = false;
}
