//-------------------------------------------------------------------------------------------------
//  Name: Marcus Korb
//  Projekt: Korb-Modular, FOLDER
//  Ver: 0.1
//  Date: 15.01.2017
//
//  ShiftRegister74HC595.h - Library available on https://github.com/Simsso/Shift-Register-74HC595-Arduino-Library
//  Bounce2.h.h - Library available on https://github.com/thomasfredericks/Bounce2
//-------------------------------------------------------------------------------------------------



#include <ShiftRegister74HC595.h>
#include <Bounce2.h>


int Wave_OSC1 = 1 ;
int Wave_OSC2 = 1;
int LED_OSC1 = 0x00;
int LED_OSC2 = 0x00;
int Switch_OSC1 = 0x00;
int Switch_OSC2 = 0x00;
int temp1 = 0;
int temp2 = 0;
int LED = 0x00;
int Switch = 0x00;

#define BUTTON_PIN_1 3
#define BUTTON_PIN_2 4

Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();



// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (2, 0, 2, 1);

void setup() {


  // Setup the first button with an internal pull-up :
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms

  // Setup the second button with an internal pull-up :
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(5); // interval in ms
}

void loop() {

  debouncer1.update();
  debouncer2.update();

  int value1 = debouncer1.read();
  int value2 = debouncer2.read();

  if (value1 == LOW) {
 //   Serial.println("test");
    if (temp1 == 0) {
      Wave_OSC1++;
      if (Wave_OSC1 > 4) Wave_OSC1 = 1;
      temp1 = 1;
    }
  }
  else {
    temp1 = 0;
  }

  if (value2 == LOW) {
    if (temp2 == 0) {
      Wave_OSC2++;
      if (Wave_OSC2 > 4) Wave_OSC2 = 1;
      temp2 = 1;
    }
  }
  else {
    temp2 = 0;
  }

  switch (Wave_OSC1) {
    case 1 :
      LED_OSC1 = 1 << 3;
      Switch_OSC1 = 0 << 0;
      break;
    case 2 :
      LED_OSC1 = 1 << 2;
      Switch_OSC1 = 1 << 0;
      break;
    case 3 :
      LED_OSC1 = 1 << 1;
      Switch_OSC1 = 2 << 0;
      break;
    case 4 :
      LED_OSC1 = 1 << 0;
      Switch_OSC1 = 3 << 0;
      break;
    case 5 :
      LED_OSC1 = 0 << 0;
      Switch_OSC1 = 4 << 0;
      break;
  }


  switch (Wave_OSC2) {
    case 1 :
      LED_OSC2 = 1 << 7;
      Switch_OSC2 = 0 << 3;
      break;
    case 2 :
      LED_OSC2 = 1 << 6;
      Switch_OSC2 = 1 << 3;
      break;
    case 3 :
      LED_OSC2 = 1 << 5;
      Switch_OSC2 = 2 << 3;
      break;
    case 4 :
      LED_OSC2 = 1 << 4;
      Switch_OSC2 = 3 << 3;
      break;
    case 5 :
      LED_OSC2 = 0 << 4;
      Switch_OSC2 = 4 << 3;
      break;
  }

  LED = LED_OSC1 | LED_OSC2;
  Switch = Switch_OSC1 | Switch_OSC2;

  uint8_t pinValues[] = { LED,  Switch };
  sr.setAll(pinValues);
}
