#include <Arduino.h>
#include <Bounce.h>  // Bounce library makes button change detection easy
const int channel = 1;

const int oscillateNote = 0; // 0 for off, 1 for on
const int oscillateControl = 1;

const int led = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long previousControlMillis = 0;

const long interval = 250;

const long controlInterval = 50;
const int control = 10;
int controlState = 1;
int controlValue = 63;

Bounce button1 = Bounce(1, 5);  // 5 = 5 ms debounce time
Bounce button2 = Bounce(2, 5);  // 5 = 5 ms debounce time

void setup() {
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  usbMIDI.begin();

  Serial.begin(9600);
  digitalWrite(led, HIGH);
  delay(5000);
  digitalWrite(led, LOW);
  Serial.println("Stompy Online");
  delay(5000);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      if (oscillateNote == 1) {
        usbMIDI.sendNoteOn(60, 99, channel);
      }
    } else {
      ledState = LOW;
      if (oscillateNote == 1) {
        usbMIDI.sendNoteOff(60, 99, channel);
      }
    }

    // set the LED with the ledState of the variable:
    digitalWrite(led, ledState);
  }

  if (currentMillis - previousControlMillis >= controlInterval) {
    previousControlMillis = currentMillis;

    if (controlValue == 0) {
      controlState = 1;
    } else if (controlValue == 127) {
      controlState = -1;
    }
    controlValue += controlState;
    usbMIDI.sendControlChange(control, controlValue, channel);
    Serial.println(controlValue);
  }


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
  
  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }

}