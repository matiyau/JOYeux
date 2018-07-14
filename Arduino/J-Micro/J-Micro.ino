#define KEY_H0 9
#define KEY_H1 8
#define KEY_H2 7
#define KEY_H3 6

#define KEY_V0 5
#define KEY_V1 4
#define KEY_V2 3
#define KEY_V3 2

#define JOY_X A3
#define JOY_Y A2
#define JOY_SW A1

#define STAT_LED A0

#define BUT_PRIM 16
#define BUT_SECN 10
#define BUT_SCRL 14
#define BUT_SHFT 15

#define MOUSE_SNST 0.25
#define MOUSE_WH_SNST 0.25

#define MOUS_REPORT_ID 0x01
#define KEYB_REPORT_ID 0x02
#define CONS_REPORT_ID 0x04

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4

#define MOD_LCTRL 0b00000001
#define MOD_LSHFT 0b00000010
#define MOD_LALT 0b00000100
#define MOD_LGUI 0b00001000

#define KEY_A 0x04
#define KEY_C 0x06
#define KEY_S 0x16
#define KEY_V 0x19
#define KEY_X 0x1B

#define KEY_1 0x1E
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_0 0x27

#define KEY_ENTER 0x28
#define KEY_ESC 0x29
#define KEY_BACKSPACE 0x2A
#define KEY_DELETE 0x4C

#define KEY_RIGHT 0x4F
#define KEY_LEFT 0x50
#define KEY_DOWN 0x51
#define KEY_UP 0x52

#define KEY_DIV 0x54
#define KEY_MUL 0x55
#define KEY_SUB 0x56
#define KEY_ADD 0x57

#define KEY_AGAIN 0x79
#define KEY_UNDO 0x7A
#define KEY_CUT 0x7B
#define KEY_COPY 0x7C
#define KEY_PASTE 0x7D

#define KEY_BROPN 0xB6
#define KEY_BRCLS 0xB7

#define KEY_VOLUME_MUTE 0xE2
#define KEY_VOLUME_UP 0xE9
#define KEY_VOLUME_DOWN 0xEA

#include "HID.h"

//Array Of Pins Giving Supply To Key Matrix
uint8_t KEY_H_OUT[] = {KEY_H0,KEY_H1,KEY_H2,KEY_H3};

//Array Of Pins Reading State Of Key Matrix
uint8_t KEY_V_IN[] = {KEY_V0,KEY_V1,KEY_V2,KEY_V3};

//Array Of Key Functionalities
uint8_t KEY_MAP[2][4][4] = {{{KEY_1, KEY_2, KEY_3, KEY_DIV}, {KEY_4, KEY_5, KEY_6, KEY_MUL}, {KEY_7, KEY_8, KEY_9, KEY_SUB}, {KEY_BROPN, KEY_0, KEY_BRCLS, KEY_ADD}}, {{KEY_BACKSPACE, KEY_UP, KEY_DELETE, KEY_X}, {KEY_LEFT, KEY_ENTER, KEY_RIGHT, KEY_C}, {KEY_ESC, KEY_DOWN, KEY_S, KEY_V}, {KEY_VOLUME_DOWN, KEY_VOLUME_MUTE, KEY_VOLUME_UP, KEY_A}}};

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
unsigned long JOY_RESPOND = 0;

struct {
  uint8_t buttonsStat;
  uint8_t xMove;
  uint8_t yMove;
  uint8_t whMove; 
} mousRprt;

struct {
  uint8_t modifierStat;
  uint8_t reservedByte;
  uint8_t keyCode;  
} keybRprt;

uint16_t consRprt;

static const uint8_t HID_reportDescriptor[] PROGMEM = {
  /* Mouse */
  0x05, 0x01,         // USAGE_PAGE (Generic Desktop)  // 54
  0x09, 0x02,         // USAGE (Mouse)
  0xa1, 0x01,         // COLLECTION (Application)
  0x09, 0x01,         //   USAGE (Pointer)
  0xa1, 0x00,         //   COLLECTION (Physical)
  0x85, 0x01,         //     REPORT_ID (1)
  0x05, 0x09,         //     USAGE_PAGE (Button)
  0x19, 0x01,         //     USAGE_MINIMUM (Button 1)
  0x29, 0x03,         //     USAGE_MAXIMUM (Button 3)
  0x15, 0x00,         //     LOGICAL_MINIMUM (0)
  0x25, 0x01,         //     LOGICAL_MAXIMUM (1)
  0x95, 0x03,         //     REPORT_COUNT (3)
  0x75, 0x01,         //     REPORT_SIZE (1)
  0x81, 0x02,         //     INPUT (Data,Var,Abs)
  0x95, 0x01,         //     REPORT_COUNT (1)
  0x75, 0x05,         //     REPORT_SIZE (5)
  0x81, 0x03,         //     INPUT (Cnst,Var,Abs)
  0x05, 0x01,         //     USAGE_PAGE (Generic Desktop)
  0x09, 0x30,         //     USAGE (X)
  0x09, 0x31,         //     USAGE (Y)
  0x09, 0x38,         //     USAGE (Wheel)
  0x15, 0x81,         //     LOGICAL_MINIMUM (-127)
  0x25, 0x7f,         //     LOGICAL_MAXIMUM (127)
  0x75, 0x08,         //     REPORT_SIZE (8)
  0x95, 0x03,         //     REPORT_COUNT (3)
  0x81, 0x06,         //     INPUT (Data,Var,Rel)
  0xc0,               //   END_COLLECTION
  0xc0,               // END_COLLECTION
  /* Keyboard Control */
  0x05, 0x01,         // USAGE_PAGE (Generic Desktop)  // 47
  0x09, 0x06,         // USAGE (Keyboard)
  0xa1, 0x01,         // COLLECTION (Application)
  0x85, 0x02,         //   REPORT_ID (2)
  0x05, 0x07,         //   USAGE_PAGE (Keyboard)
  0x19, 0xe0,         //   USAGE_MINIMUM (Keyboard LeftControl)
  0x29, 0xe7,         //   USAGE_MAXIMUM (Keyboard Right GUI)
  0x15, 0x00,         //   LOGICAL_MINIMUM (0)
  0x25, 0x01,         //   LOGICAL_MAXIMUM (1)
  0x75, 0x01,         //   REPORT_SIZE (1)
  0x95, 0x08,         //   REPORT_COUNT (8)
  0x81, 0x02,         //   INPUT (Data,Var,Abs)
  0x95, 0x01,         //   REPORT_COUNT (1)
  0x75, 0x08,         //   REPORT_SIZE (8)
  0x81, 0x03,         //   INPUT (Cnst,Var,Abs)
  0x95, 0x06,         //   REPORT_COUNT (1)
  0x75, 0x08,         //   REPORT_SIZE (8)
  0x15, 0x00,         //   LOGICAL_MINIMUM (0)
  0x25, 0x82,         //   LOGICAL_MAXIMUM (132)
  0x05, 0x07,         //   USAGE_PAGE (Keyboard)
  0x19, 0x00,         //   USAGE_MINIMUM (Reserved (no event indicated))
  0x29, 0x82,         //   USAGE_MAXIMUM (Keyboard Locking Caps Lock)
  0x81, 0x00,         //   INPUT (Data,Ary,Abs)
  0xc0,               // END_COLLECTION 
  /* Consumer Control */
  0x05, 0x0C,         // USAGE_PAGE (Consumer Device)
  0x09, 0x01,         // USAGE (Consumer Control)
  0xA1, 0x01,         // COLLECTION (Application)
  0x85, 0x04,         //    REPORT_ID (4)
  0x15, 0x00,         //    LOGICAL_MINIMUM (3FF)
  0x26, 0xFF, 0x03,   //    LOGICAL_MAXIMUM (3FF)
  0x19, 0x00,         //    USAGE_MINIMUM (0)
  0x2A, 0xFF, 0x03,   //    USAGE_MAXIMUM (0x3FF)
  0x95, 0x01,         //    REPORT_COUNT (1)
  0x75, 0x10,         //    REPORT_SIZE (16)
  0x81, 0x00,         //    INPUT (Data,Ary,Abs)
  0xC0,               //END_COLLECTION 
};

//Create A Node For The HID Descriptor
static HIDSubDescriptor node(HID_reportDescriptor, sizeof(HID_reportDescriptor));

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

  //Set The Status Pun As Output
  pinMode(STAT_LED, OUTPUT);

  //Append The HID Report Descriptor
  HID().AppendDescriptor(&node);

  //Initialize By Sending A Blank Report
  memset(&mousRprt,0,sizeof(mousRprt));
  HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
  memset(&keybRprt,0,sizeof(keybRprt));
  HID().SendReport(KEYB_REPORT_ID, &keybRprt, sizeof(keybRprt));
  consRprt = 0;
  HID().SendReport(CONS_REPORT_ID,&consRprt, sizeof(consRprt));
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
          uint8_t KEY_CODE = KEY_MAP[BUT_ST_PRESSED][i][j];

          //Control Key Combinations
          if (KEY_CODE >= 0x04 && KEY_CODE <= 0x1B) {
            if (keybRprt.keyCode == 0x00) {
              keybRprt.modifierStat = keybRprt.modifierStat | MOD_LCTRL;
              keybRprt.keyCode = KEY_CODE;
              HID().SendReport(KEYB_REPORT_ID, &keybRprt, sizeof(keybRprt));
            }
          }
          
          //Digits, Enter, Backspace, Delete, Escape
          else if (KEY_CODE >= 0x1E && KEY_CODE <= 0x7D) {
            if (keybRprt.keyCode == 0x00) {
              keybRprt.keyCode = KEY_CODE;
              HID().SendReport(KEYB_REPORT_ID, &keybRprt, sizeof(keybRprt));
            }
          }

          //Open And Close Brackets
          else if (KEY_CODE == KEY_BROPN || KEY_CODE == KEY_BRCLS) {
            if (keybRprt.keyCode == 0x00) {
              keybRprt.modifierStat = keybRprt.modifierStat | MOD_LSHFT;
              keybRprt.keyCode = KEY_CODE;
              HID().SendReport(KEYB_REPORT_ID, &keybRprt, sizeof(keybRprt));
            }
          }

          //Media Keys
          else if (KEY_CODE >= 0xE2 && KEY_CODE <= 0xEA) {
            if (consRprt == 0x00) {
              consRprt = KEY_CODE;
              HID().SendReport(CONS_REPORT_ID, &consRprt, sizeof(consRprt));
            }
          }
        }
      }
    }
  }
  if (!KEY_PRESSED_NOW && KEY_PRESSED_PREV) {
    //Send Blank Report To Release Keys
    consRprt = 0;
    HID().SendReport(CONS_REPORT_ID,&consRprt, sizeof(consRprt));
    memset(&keybRprt,0,sizeof(keybRprt));
    HID().SendReport(KEYB_REPORT_ID,&keybRprt, sizeof(keybRprt));
  }
  KEY_PRESSED_PREV = KEY_PRESSED_NOW;
  KEY_PRESSED_NOW = false;

  BUT_PY_PRESSED_NOW = !digitalRead(BUT_PRIM);
  if (BUT_PY_PRESSED_PREV != BUT_PY_PRESSED_NOW) {
    if (BUT_PY_PRESSED_NOW) {
      mousRprt.xMove = 0;
      mousRprt.yMove = 0;
      mousRprt.whMove = 0;
      mousRprt.buttonsStat = mousRprt.buttonsStat | MOUSE_LEFT;
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
    }
    else {
      mousRprt.xMove = 0;
      mousRprt.yMove = 0;
      mousRprt.whMove = 0;
      mousRprt.buttonsStat = mousRprt.buttonsStat & (~MOUSE_LEFT);
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
    }
  }
  BUT_PY_PRESSED_PREV = BUT_PY_PRESSED_NOW;

  BUT_SY_PRESSED_NOW = !digitalRead(BUT_SECN);
  if (BUT_SY_PRESSED_PREV != BUT_SY_PRESSED_NOW) {
    if (BUT_SY_PRESSED_NOW) {
      mousRprt.xMove = 0;
      mousRprt.yMove = 0;
      mousRprt.whMove = 0;
      mousRprt.buttonsStat = mousRprt.buttonsStat | MOUSE_RIGHT;
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
    }
    else {
      mousRprt.xMove = 0;
      mousRprt.yMove = 0;
      mousRprt.whMove = 0;
      mousRprt.buttonsStat = mousRprt.buttonsStat & (~MOUSE_RIGHT);
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
    }
  }
  BUT_SY_PRESSED_PREV = BUT_SY_PRESSED_NOW;
  
  BUT_SL_PRESSED_NOW = !digitalRead(BUT_SCRL);
  if (BUT_SL_PRESSED_PREV != BUT_SL_PRESSED_NOW) {
    if (BUT_SL_PRESSED_NOW) {
      mousRprt.xMove = 0;
      mousRprt.yMove = 0;
      mousRprt.whMove = 0;
      mousRprt.buttonsStat = mousRprt.buttonsStat | MOUSE_MIDDLE;
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
    }
    else {
      mousRprt.xMove = 0;
      mousRprt.yMove = 0;
      mousRprt.whMove = 0;
      mousRprt.buttonsStat = mousRprt.buttonsStat & (~MOUSE_MIDDLE);
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
    }
  }
  BUT_SL_PRESSED_PREV = BUT_SL_PRESSED_NOW;
  
  JOY_PRESSED_NOW = !digitalRead(JOY_SW);
  if (!JOY_PRESSED_PREV) {
    if (JOY_PRESSED_NOW) {
      JOY_SCR = !JOY_SCR;
      digitalWrite(STAT_LED, JOY_SCR);
    }
  }
  JOY_PRESSED_PREV = JOY_PRESSED_NOW;

  if (JOY_SCR) {
    
    MOUSE_X = 0;
    MOUSE_Y = 0;
    MOUSE_WH = analogRead(JOY_Y)-JOY_Y_0;
  }
  else {
    MOUSE_X = analogRead(JOY_X)-JOY_X_0;
    MOUSE_Y = analogRead(JOY_Y)-JOY_Y_0;
    MOUSE_WH = 0;    
  }
  if (!(MOUSE_X<2 && MOUSE_X>-2 && MOUSE_Y<2 && MOUSE_Y>-2 && MOUSE_WH<2 && MOUSE_WH>-2)) {
    if (millis() - JOY_RESPOND > 100) {
      if (MOUSE_X > 0) {
        MOUSE_X = constrain(MOUSE_SNST * MOUSE_X, 1, 120);
      }
      else if (MOUSE_X < 0){
        MOUSE_X = constrain(MOUSE_SNST * MOUSE_X, -120, -1);
      }

      if (MOUSE_Y > 0) {
        MOUSE_Y = constrain(MOUSE_SNST * MOUSE_Y, 1, 120);
      }
      else if (MOUSE_Y < 0) {
        MOUSE_Y = constrain(MOUSE_SNST * MOUSE_Y, -120, -1);
      }

      if (MOUSE_WH > 0) {
        MOUSE_WH = constrain(MOUSE_WH_SNST * MOUSE_WH, 1, 120);
      }
      else if (MOUSE_WH < 0){
        MOUSE_WH = constrain(MOUSE_WH_SNST * MOUSE_WH, -120, -1);
      }

      mousRprt.xMove = MOUSE_X;
      mousRprt.yMove = MOUSE_Y;
      mousRprt.whMove = -MOUSE_WH;
      Serial.print(MOUSE_X);
      Serial.print(", ");
      Serial.println(MOUSE_Y);
      HID().SendReport(MOUS_REPORT_ID, &mousRprt, sizeof(mousRprt));
      JOY_RESPOND = millis();
    }
  }
}
