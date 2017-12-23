/* Buttons to USB Joystick Example

   You must select Joystick from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Bounce.h>

#define DB_TIME 10
#define BUTTON_COUNT 20
#define ESC_PIN 14
#define ESC_DELAY 400
// coin is 12
#define SERVICE_MOD_PIN 5
#define RESET_MOD_PIN   6
#define MENU_MOD_PIN    7

unsigned char *states;
Bounce *buttons;
unsigned long esc_hold_start;

void setup() {
  buttons = (Bounce *) malloc(sizeof(Bounce) * BUTTON_COUNT);
  states = (unsigned char *) malloc(sizeof(char) * BUTTON_COUNT);
  esc_hold_start = 0;
  int pinNo = 0;
  for (int i = 0; i < BUTTON_COUNT; i++) {
    buttons[i] = Bounce(pinNo, DB_TIME);
    states[i] = 0;
    pinMode(pinNo, INPUT_PULLUP);
    if (++pinNo == 13) {
      pinNo++;
    }
  }
}

void loop() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    buttons[i].update();
    if (buttons[i].fallingEdge()) {
      switch (i) {
        case 0:
          Joystick.Y(0);
          break;
        case 1:
          Joystick.X(1023);
          break;
        case 2:
          Joystick.Y(1023);
          break;
        case 3:
          Joystick.X(0);
          break;
        case ESC_PIN:
          esc_hold_start = millis();
          break;
        default:
          states[i] = 1;
          Joystick.button(i - 3, 1);
          break;
      }
    }
  }
  if (esc_hold_start > 0 && (millis() - esc_hold_start) >= ESC_DELAY) {
    if (states[SERVICE_MOD_PIN]) {
      Keyboard.press(KEY_F2);
    } else if (states[RESET_MOD_PIN]) {
      Keyboard.press(KEY_F3);
    } else if (states[MENU_MOD_PIN]) {
      Keyboard.press(KEY_TAB);
    } else {
      Keyboard.press(KEY_ESC);
    }
    esc_hold_start = 0;
  }
  for (int i = 0; i < BUTTON_COUNT; i++) {
    if (buttons[i].risingEdge()) {
      switch (i) {
        case 0:
        case 2:
          Joystick.Y(512);
          break;
        case 1:
        case 3:
          Joystick.X(512);
          break;
        case ESC_PIN:
          Keyboard.releaseAll();
          esc_hold_start = 0;
          break;
        default:
          states[i] = 0;
          Joystick.button(i - 3, 0);
          break;
      }
    }
  }
}

