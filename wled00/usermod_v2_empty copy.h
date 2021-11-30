#pragma once

#include "wled.h"

#include "Adafruit_TLC5947.h"
#include <stdint.h>

// How many boards do you have chained?
const uint8_t TLC5974_count  = 1;

const uint8_t data_pin = 13;
const uint8_t clock_pin = 14;
const uint8_t latch_pin = 5;
//#define oe  -1  // set to -1 to not use the enable pin (its optional)

class UsermodTLC5947 : public Usermod {
  private:
    Adafruit_TLC5947 pwm;

    void set() {
      pwm.setLED(0, col[0] * bri / 255, col[1] * bri / 255, col[2] * bri / 255);
      pwm.setPWM(4, 4096 * bri / 255);
      pwm.write();
    }

  public:
    UsermodTLC5947() : pwm(TLC5974_count, clock_pin, data_pin, latch_pin) {
    }

    void setup() {
      if (!pwm.begin()) {
        DEBUG_PRINT("PWM init failed");
      }
    }

    void loop() {
      static uint8_t r, g, b, w, brightness;

      if (r != col[0] || g != col[1] || b != col[2] || w != col[3] || brightness != bri) {
        set();
        r = col[0];
        g = col[1];
        b = col[2];
        w = col[3];
        brightness = bri;
      }
    }
};