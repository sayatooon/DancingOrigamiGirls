#include "PushButton.hpp"

void PushButton::init(uint8_t pin, uint8_t mode){
  _pin = pin;
  _mode = mode;
  _buttonState = HIGH;
  _lastButtonState = HIGH;
  _longPressState = false;
  _lastDebounceTime = millis();
  _doubleClickState = false;
  pinMode(pin, mode);
}

/* check the push button change state */
// 0: no changed
// 1: pushed
// 2: released
int PushButton::getChangeState(){
  int state = digitalRead(_pin);
    
    if (state != _lastButtonState) { // reset timer
        _lastDebounceTime = millis();
    }
  
    if ((millis() - _lastDebounceTime) > _debounceWindow) {
        if (state != _buttonState) {
            _buttonState = state;          
            if (_buttonState == LOW) { // pushed
                _lastButtonState = state;
                _longPressState = false;
                if(millis() - _pressedTime < _doubleClickInterval){
                  _doubleClickState = true;         
                }else{
                  _doubleClickState = false;
                }
                _pressedTime = millis();
                return 1;
            }
            if (_buttonState == HIGH) { // released
                _lastButtonState = state;
                if ((millis() - _pressedTime) > _longPressTime){
                  _longPressState = true;
                }
                return 2;
            }
        }
    }
    _lastButtonState = state;
    return 0;
}

/* get the push button state */
// HIGH: off
// LOW: on 
bool PushButton::getState(){
  return _buttonState;
}

void PushButton::setDebounceWindow(unsigned long time){
  _debounceWindow = time;
}

void PushButton::setLongPressTime(unsigned long time){
  _longPressTime = time;
}

bool PushButton::getLongPressState(){
  return _longPressState;
}

void PushButton::setDoubleClickInterval(unsigned long time){
  _doubleClickInterval = time;
}

bool PushButton::getDoubleClickState(){
  return _doubleClickState;
}

