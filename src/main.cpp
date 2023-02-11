#include <Arduino.h>
#include <Bounce.h>  // Bounce library makes button change detection easy
const int channel = 1;

const int led = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 250;

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
      usbMIDI.sendNoteOn(60, 99, channel);
    } else {
      ledState = LOW;
      usbMIDI.sendNoteOff(60, 99, channel);
    }

    // set the LED with the ledState of the variable:
    digitalWrite(led, ledState);
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
  
}