#include <Arduino.h>
#include <FastLED.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>
#include "PushButton.hpp"
#include "Dancing.hpp"

// state
#define INITIALIZING 0
#define STANDBY 1
#define PLAY 2
#define STOP 3

int state; // the machine state

// pin setting
const uint8_t PIN_LED_RGB = 42;              // RGB LED
const uint8_t PIN_SM[] = {2, 1, 5, 4, 7, 6}; // Servo motors for the girls, {0r, 0l, 1r, 1l, 2r, 2l}
const uint8_t PIN_BALL = 13;                 // Servo motors for the disco ball
const uint8_t PIN_BTN = 39;                  // Push button
const uint8_t PIN_VOL = 10;                  // Volume

// setting for the RGB LEDs
const int NUM_LEDS = 65; // last one is for the disco ball, the others are for the stages
CRGB leds[NUM_LEDS];

// setting for the speaker
DFRobotDFPlayerMini myDFPlayer;
HardwareSerial mySerial(0);

// setting for the servo motors
// const int CH_SM_G[] = {1, 2, 3, 4, 5, 6};                                // servo motors channels for the girls
const int CH_SM_B = 0; // servo motor channel for the disco ball
// const int WR_G_MINUS = 500, WR_G_MAXUS = 2500;                           // [us], Pulse width range of DS-007M and MG90S
const int WR_B_MINUS = 700, WR_B_MAXUS = 2300; // [us], Pulse width range of FS90
const int SM_RANGE[] = {-50, 60};              // 0-65 deg
const int SM_B_STOP = 85;                      // The stop degree is normally 90 deg but adjust with your FS90R.
const int SM_B_ROT = SM_B_STOP + 6;            // 0-180, the disco ball rotaiton speed
// Servo servoG[] = {Servo(), Servo(), Servo(), Servo(), Servo(), Servo()}; // servo motors for the girls
Servo servoB = Servo(); // Servo motor for the disco ball

// setting for the push button
PushButton button;
Dancing cranes; // Danching Origami Girls

// variables
int volume;
int last_beats;
unsigned long start_time, stop_time, tmp_time;

// function declarations
void setStandby();

void setup()
{
  state = INITIALIZING;
  // USBSerial.begin(115200);

  // for (int i = 0; i < 6; i++)
  //   servoG[i].attach(PIN_SM[i], CH_SM_G[i], WR_G_MINUS, WR_G_MAXUS);
  //   servoG[i].write(PIN_SM[i], 90);
  // }
  servoB.attach(PIN_BALL, CH_SM_B, WR_B_MINUS, WR_B_MAXUS);
  servoB.write(PIN_BALL, SM_B_STOP);

  cranes.init(PIN_SM);

  button.init(PIN_BTN, INPUT_PULLUP);
  button.setLongPressTime(1500);
  button.setDebounceWindow(20);
  pinMode(PIN_VOL, ANALOG);

  // speaker setting
  mySerial.begin(9600);
  delay(2000);

  if (!myDFPlayer.begin(mySerial))
  {
    // USBSerial.print("Failed to initialize DFPlayer");
    FastLED.setBrightness(50); // 0-255
    leds[NUM_LEDS - 1] = CRGB::Red;
    FastLED.show();
    while (1)
    {
      delay(2000);
    }
  }
  else
  {
    volume = map(analogRead(PIN_VOL), 0, 4095, 0, 30);
    myDFPlayer.volume(volume); // Set volume value. From 0 to 30
    delay(200);
  }
  setStandby();
}

void loop()
{
  int volume_tmp = map(analogRead(PIN_VOL), 0, 4095, 0, 30);
  if (volume != volume_tmp)
  {
    volume = volume_tmp;
    myDFPlayer.volume(volume);
    delay(180);
  }

  delay(20);

  switch (state)
  {
  case STANDBY:
    if (button.getChangeState() == 2)
    { // start
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
      delay(20);
      start_time = millis();
      myDFPlayer.play(1);
      delay(200);
      state = PLAY;
    }
    break;
  case PLAY:
    if (button.getChangeState() == 2)
    {
      servoB.write(PIN_BALL, SM_B_STOP);
      if (button.getLongPressState())
      { // reset
        setStandby();
        break;
      }
      else
      { // pause
        myDFPlayer.pause();
        tmp_time = millis();
        delay(200);
        state = STOP;
        break;
      }
    }
    last_beats = cranes.updateDance(millis() - start_time - stop_time, last_beats, leds, NUM_LEDS);
    if(last_beats <2){
      servoB.write(PIN_BALL, SM_B_STOP);
    }else if (last_beats > 2 && last_beats < 95)
    {
      servoB.write(PIN_BALL, SM_B_ROT);
    }
    else if (last_beats >= 95)
    {
      servoB.write(PIN_BALL, SM_B_STOP);
      if (last_beats > 96)
      {
        setStandby();
      }
    }

    break;
  case STOP:
    if (button.getChangeState() == 2)
    {
      if (button.getLongPressState())
      { // reset
        setStandby();
      }
      else
      { // resume
        myDFPlayer.start();
        stop_time += millis() - tmp_time;
        servoB.write(PIN_BALL, SM_B_ROT);
        delay(200);
        state = PLAY;
      }
    }
    break;
  default:
    break;
  }
}

/* set standby*/
void setStandby()
{
  // LED
  FastLED.setBrightness(50); // 0-255
  FastLED.addLeds<WS2812, PIN_LED_RGB, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  leds[NUM_LEDS - 1] = CRGB(255, 100, 0);
  for (int i = 0; i < NUM_LEDS - 1; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  // motors
  uint8_t pose[3] = {STAND, STAND, STAND};
  cranes.setPose(pose);
  servoB.write(PIN_BALL, SM_B_STOP);
  // mp3 player
  myDFPlayer.stop();
  delay(200);

  // init variables
  stop_time = 0;
  last_beats = -1;
  state = STANDBY;
}
