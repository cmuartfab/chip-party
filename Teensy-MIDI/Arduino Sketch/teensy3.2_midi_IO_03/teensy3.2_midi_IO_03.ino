#include <Bounce.h>


// the MIDI channel number to send messages
const int channel = 1;

//-------------PIN NUMBERS-----------------------
// these are the Arduino numbered pins to which are things are connected:

//LEDs (Analog Outputs/PWM or Digital Output)
const int ledPin1 = 5;    //a PWM pin
const int ledPin2 = 6;    //a PWM pin
const int ledPin3 = 20;    //a PWM pin 
const int ledPin4 = 21;   //a PWM pin

//faders and joysticks (Analog Inputs)
const int faderPin1 = A0;  
const int faderPin2 = A9;
const int faderPin3 = A20; 
const int faderPin4 = A10; 
const int faderPin5 = A11; 
const int faderPin6 = A12;  

const int joyPinH1 = A16;
const int joyPinV1 = A15;
const int joyPinH2 = A18;
const int joyPinV2 = A17;

const int joyButtonPin1 = 24;
const int joyButtonPin2 = 30;

//Push Buttons (Digital Inputs)
const int buttonPin1 = 13;
const int buttonPin2 = 14;


//const int motor




//-------------MIDI NUMBERS-----------------------


//LEDs are triggered by Note messages; velocity is mapped to brightness 
const int ledNote1 = 60;
const int ledNote2 = 61;
const int ledNote3 = 62;
const int ledNote4 = 63;

const int faderCtl1 = 14;
const int faderCtl2 = 15;
const int faderCtl3 = 16;
const int faderCtl4 = 17;
const int faderCtl5 = 18;
const int faderCtl6 = 19;

const int joyCtl1 = 20;
const int joyCtl2 = 21;

const int multiCtl1 = 22;
const int multiCtl2 = 23;

//Buttons trigger Note messages; velocity is 127 or 0

const int buttonNote1 = 61;
const int buttonNote2 = 62;
const int buttonNote3 = 63;
const int buttonNote4 = 64;
const int joyButtonNote1 = 65;
const int joyButtonNote2 = 66;

//-------------Continuous Control: send Changes only--------------
int faderPrev1 = -1;
int faderPrev2 = -1;
int faderPrev3 = -1;
int faderPrev4 = -1;
int faderPrev5 = -1;
int faderPrev6 = -1;
int joyPrev1 = -1;
int joyPrev2 = -1;

int multiPrev1 = -1;
int multiPrev2 = -1;


elapsedMillis msec = 0;

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

Bounce button1 = Bounce(buttonPin1, 5);  // 5 = 5 ms debounce time
Bounce button2 = Bounce(buttonPin2, 5);  // which is appropriate for good quality mechanical pushbuttons

Bounce joyButton1 = Bounce(joyButtonPin1, 5);
Bounce joyButton2 = Bounce(joyButtonPin2, 5);


//----------------------for SENDING MIDI-----------------------
void buttonInput(){
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button1.update();
  button2.update();

  joyButton1.update();
  joyButton2.update();

  // Check each button for "falling" edge.
  // Send a MIDI Note On message when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  // to low (pressed - button connects pin to ground)
 
  if (button1.fallingEdge()) {
    usbMIDI.sendNoteOn(buttonNote1, 127, channel);  // 61 = C#4
  }
  if (button2.fallingEdge()) {
    usbMIDI.sendNoteOn(buttonNote2, 127, channel);  // 62 = D4
  }

  if (joyButton1.fallingEdge()) {
    usbMIDI.sendNoteOn(joyButtonNote1, 127, channel);  
  }
  if (joyButton2.fallingEdge()) {
    usbMIDI.sendNoteOn(joyButtonNote2, 127, channel);  
  }
      // Check each button for "rising" edge
  // Send a MIDI Note Off message when each button releases
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)

  if (button1.risingEdge()) {
    usbMIDI.sendNoteOff(buttonNote1, 0, channel);  // 61 = C#4
  }
  if (button2.risingEdge()) {
    usbMIDI.sendNoteOff(buttonNote2, 0, channel);  // 62 = D4
  }

    if (joyButton1.risingEdge()) {
    usbMIDI.sendNoteOff(joyButtonNote1, 0, channel);  
  }
  if (joyButton2.risingEdge()) {
    usbMIDI.sendNoteOff(joyButtonNote2, 0, channel);  
  }
}


void faderInput() {
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  if (msec >= 20) {
    msec = 0;
    int f1 = analogRead(faderPin1) / 8;
    int f2 = analogRead(faderPin2) / 8;
    int f3 = analogRead(faderPin3) / 8;
    int f4 = analogRead(faderPin4) / 8;
    int f5 = analogRead(faderPin5) / 8;
    int f6 = analogRead(faderPin6) / 8;

    
    int j1 = analogRead(joyPinH1) / 8;
    int j2 = analogRead(joyPinH2) / 8;

    

    // only transmit MIDI messages if analog input changed
    if (f1 != faderPrev1) {
      usbMIDI.sendControlChange(faderCtl1, f1, channel);
      faderPrev1 = f1;
    }

    if (f2 != faderPrev2) {
      usbMIDI.sendControlChange(faderCtl2, f2, channel);
      faderPrev2 = f2;
    }

    if (f3 != faderPrev3) {
      usbMIDI.sendControlChange(faderCtl3, f3, channel);
      faderPrev3 = f3;
    }

    if (f4 != faderPrev4) {
      usbMIDI.sendControlChange(faderCtl4, f4, channel);
      faderPrev4 = f4;
    }

    if (f5 != faderPrev5) {
      usbMIDI.sendControlChange(faderCtl5, f5, channel);
      faderPrev5 = f5;
    }

    if (f6 != faderPrev6) {
      usbMIDI.sendControlChange(faderCtl6, f6, channel);
      faderPrev6 = f6;
    }

    if (j1 != joyPrev1) {
      usbMIDI.sendControlChange(joyCtl1, j1, channel);
      joyPrev1 = j1;
    }

    if (j2 != joyPrev2) {
      usbMIDI.sendControlChange(joyCtl2, j2, channel);
      joyPrev2 = j2;
    }


  }
}

unsigned long t=0;


//----------------------for RECEIVING MIDI-----------------------
void OnNoteOn(byte channel, byte note, byte velocity)
{
  if (note==ledNote1) {
    analogWrite(ledPin1, velocity*2);
  }

  if (note==ledNote2) {
    analogWrite(ledPin2, velocity*2);
  }

  if (note==ledNote3) {
    analogWrite(ledPin3, velocity*2);
  }

  if (note==ledNote4) {
    analogWrite(ledPin4, velocity*2);
  }
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  if (note==ledNote1) {
    analogWrite(ledPin1, 0);
  }

  if (note==ledNote2) {
    analogWrite(ledPin2, 0);
  }

  if (note==ledNote3) {
    analogWrite(ledPin3, 0);
  }

  if (note==ledNote4) {
    analogWrite(ledPin4, 0);
  }
}

void loop() {
  int type, note, velocity, channel, d1, d2;

  //---------for sending midi---------
  //process buttons
  buttonInput();

  //process faders
  faderInput();

  //--------for receiving midi---------

  
    // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  usbMIDI.read();
}

//----------------------SETUP-----------------------
void setup() {

  //pinMode(3, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;

// store previously sent values, to detect changes


// Configure the pins for input mode with pullup resistors.
// The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
 
  pinMode(joyButtonPin1, INPUT_PULLUP);
  pinMode(joyButtonPin2, INPUT_PULLUP);
  




}
