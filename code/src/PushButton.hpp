#pragma once
#include <Arduino.h>

class PushButton{
  private:
    uint8_t _pin;
    uint8_t _mode;
    bool _buttonState;
    bool _lastButtonState;
    bool _longPressState;
    bool _doubleClickState;
    unsigned long _lastDebounceTime;
    unsigned long _pressedTime;
    unsigned long _debounceWindow = 5; // [ms] ajust depending on the buttons
    unsigned long _longPressTime = 2000; // [ms]
    unsigned long _doubleClickInterval = 500; // [ms]
  public:
    void init(uint8_t pin, uint8_t mode);
    int getChangeState();
    bool getState();
    void setDebounceWindow(unsigned long time);
    void setLongPressTime(unsigned long time);
    bool getLongPressState();
    void setDoubleClickInterval(unsigned long time);
    bool getDoubleClickState();
};