#include <Arduino.h>
#include <Bounce.h>  // Bounce library makes button change detection easy
const int channel = 1;

Bounce button1 = Bounce(1, 5);  // 5 = 5 ms debounce time
Bounce button2 = Bounce(2, 5);  // 5 = 5 ms debounce time

void setup() {
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  usbMIDI.begin();
}

void loop() {
  button1.update();
  button2.update();

  if (button1.fallingEdge()) {
    usbMIDI.sendNoteOn(60, 99, channel);  // 60 = C4
  }
  if (button2.fallingEdge()) {
    usbMIDI.sendNoteOn(67, 99, channel);  // 67 = C?
  }

  if (button1.risingEdge()) {
    usbMIDI.sendNoteOff(60, 0, channel);  // 60 = C4
  }
    if (button2.risingEdge()) {
    usbMIDI.sendNoteOff(67, 99, channel);  // 67 = C?
  }
}