#define KEY_H0 6
#define KEY_H1 7
#define KEY_H2 8
#define KEY_H3 9

#define KEY_V0 10
#define KEY_V1 11
#define KEY_V2 12
#define KEY_V3 13

#define JOY_X A2
#define JOY_Y A1
#define JOY_SW A0

#define BUT_PRIM 2
#define BUT_SECN 3
#define BUT_SCRL 5
#define BUT_SHFT 4

//Array Of Pins Giving Supply To Key Matrix
uint8_t KEY_H_OUT[] = {KEY_H0,KEY_H1,KEY_H2,KEY_H3};

//Array Of Pins Reading State Of Key Matrix
uint8_t KEY_V_IN[] = {KEY_V0,KEY_V1,KEY_V2,KEY_V3};

//Array Of Key Lower Functionalities
char KEY_MAP0[][4] = {{'1', '2', '3', 'a'}, {'4', '5', '6', 'b'}, {'7', '8', '9', 'c'}, {'-', '0', '=', 'd'}};

//Array Of Key Upper Functionalities
char KEY_MAP1[][4] = {{'!', '@', '#', 'A'}, {'$', '%', '^', 'B'}, {'&', '*', '(', 'C'}, {'_', ')', '+', 'D'}};

bool KEY_PRESSED_NOW = false;
bool KEY_PRESSED_PREV = false;

bool JOY_PRESSED_NOW = false;
bool JOY_PRESSED_PREV = false;
bool JOY_SCR = false;

bool BUT_PY_PRESSED_NOW = false;
bool BUT_PY_PRESSED_PREV = false;
bool BUT_SY_PRESSED_NOW = false;
bool BUT_SY_PRESSED_PREV = false;
bool BUT_SL_PRESSED_NOW = false;
bool BUT_SL_PRESSED_PREV = false;
bool BUT_ST_PRESSED = false;

int16_t MOUSE_X = 0;
int16_t MOUSE_Y = 0;
int16_t MOUSE_WH = 0;

int16_t JOY_X_0 = 512;
int16_t JOY_Y_0 = 512;

void setup() {
  Serial.begin(9600);

  //Pin Config For KeyPad Matrix
  for (int i = 0; i<4; i++) {
    pinMode(KEY_H_OUT[i], OUTPUT);
    digitalWrite(KEY_H_OUT[i], HIGH);
  }
  for (int i = 0; i<4; i++) {
    pinMode(KEY_V_IN[i], INPUT_PULLUP);
  }

  //Pin Config For JoyStick
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT_PULLUP);

  //Pin Configuration For Push Buttons
  pinMode(BUT_PRIM, INPUT_PULLUP);
  pinMode(BUT_SECN, INPUT_PULLUP);
  pinMode(BUT_SCRL, INPUT_PULLUP);
  pinMode(BUT_SHFT, INPUT_PULLUP);

  //Calibrate JoyStick
  JOY_X_0 = analogRead(JOY_X);
  JOY_Y_0 = analogRead(JOY_Y);
}

void loop() { 
  BUT_ST_PRESSED = !digitalRead(BUT_SHFT);
   
  for (int i = 0; i<4; i++) {
    for (int j = 0; j<4; j++) {
       digitalWrite(KEY_H_OUT[j], HIGH);
    }
    digitalWrite(KEY_H_OUT[i], LOW);
    for (int j = 0; j<4; j++) {
      if (!digitalRead(KEY_V_IN[j])) {
        KEY_PRESSED_NOW = true;
        if (!KEY_PRESSED_PREV) {
          if (BUT_ST_PRESSED) {
            Serial.println(KEY_MAP1[i][j]);
          }
          else {
            Serial.println(KEY_MAP0[i][j]);
          }
        }
      }
    }
  }
  KEY_PRESSED_PREV = KEY_PRESSED_NOW;
  KEY_PRESSED_NOW = false;

  BUT_PY_PRESSED_NOW = !digitalRead(BUT_PRIM);
  if (BUT_PY_PRESSED_PREV != BUT_PY_PRESSED_NOW) {
    if (BUT_PY_PRESSED_NOW) {
      Serial.println("PY DN");
    }
    else {
      Serial.println("PY UP");
    }
  }
  BUT_PY_PRESSED_PREV = BUT_PY_PRESSED_NOW;

  BUT_SY_PRESSED_NOW = !digitalRead(BUT_SECN);
  if (BUT_SY_PRESSED_PREV != BUT_SY_PRESSED_NOW) {
    if (BUT_SY_PRESSED_NOW) {
      Serial.println("SY DN");
    }
    else {
      Serial.println("SY UP");
    }
  }
  BUT_SY_PRESSED_PREV = BUT_SY_PRESSED_NOW;
  
  BUT_SL_PRESSED_NOW = !digitalRead(BUT_SCRL);
  if (BUT_SL_PRESSED_PREV != BUT_SL_PRESSED_NOW) {
    if (BUT_SL_PRESSED_NOW) {
      Serial.println("SL DN");
    }
    else {
      Serial.println("SL UP");
    }
  }
  BUT_SL_PRESSED_PREV = BUT_SL_PRESSED_NOW;
  
  JOY_PRESSED_NOW = !digitalRead(JOY_SW);
  if (!JOY_PRESSED_PREV) {
    if (JOY_PRESSED_NOW) {
      JOY_SCR = !JOY_SCR;
    }
  }
  JOY_PRESSED_PREV = JOY_PRESSED_NOW;

  if (JOY_SCR) {
    MOUSE_X = 0;
    MOUSE_Y = 0;
    MOUSE_WH = analogRead(JOY_Y)-512;
  }
  else {
    MOUSE_X = analogRead(JOY_X)-JOY_X_0;
    MOUSE_Y = analogRead(JOY_Y)-JOY_Y_0;
    MOUSE_WH = 0;    
  }
  if (!(MOUSE_X<10 && MOUSE_X>-10 && MOUSE_Y<10 && MOUSE_Y>-10 && MOUSE_WH<10 && MOUSE_WH>-10)) {
    Serial.print("X : ");
    Serial.print(MOUSE_X);
    Serial.print(", ");
    Serial.print("Y : ");
    Serial.print(MOUSE_Y);
    Serial.print(", ");
    Serial.print("WH : ");
    Serial.println(MOUSE_WH); 
  }
}
