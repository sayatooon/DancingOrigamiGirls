#pragma once
#include <Arduino.h>
#include <Servo.h>
#include <FastLED.h>

// pose
#define STAND 0
#define SQUAT 1
#define LEAN_R 2
#define LEAN_L 3
//#define BEND_R 4
//#define BEND_L 5
#define STRECH 6

// debut song
#define SONG_SIZE 95


class Dancing{
  private:
    uint8_t _pin[6];
    int _deg_r[7] = {90, 90+55, 90+55, 90-90, 90-30, 90-70, 90-50}; // The right leg degrees for each pose
    int _deg_l[7] = {90, 90-55, 90+90, 90-55, 90+70, 90+30, 90+50};// The left leg degrees for each pose
    int _wr_min = 500;  // [us], min pulse width range of MS18
    int _wr_max = 2500; // [us], max pulse width range of MS18
    int _ch[6] = {1, 2, 3, 4, 5, 6}; // servo motors channels
    Servo _servo[6];
    bool _led_normal = true;

  public:
    void init(const uint8_t* pin);
    void setDeg(uint8_t pose, int* deg);
    void setPose(uint8_t* pose);
    void setMove(uint8_t* pose1, uint8_t* pose2, unsigned long time, uint8_t div);
    int updateDance(unsigned long time, int last_beats, CRGB* led, uint8_t num);
};

