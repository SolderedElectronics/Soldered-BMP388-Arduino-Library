/**
 **************************************************
 *
 * @file        BMP388-SOLDERED.h
 * @brief       Soruce file for the BMP388 library wrapper.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Borna Biro for soldered.com
 ***************************************************/

#ifndef __BMP388_SENSOR_SOLDERED__
#define __BMP388_SENSOR_SOLDERED__

#include "Arduino.h"

// Include Arduino Wire library.
#include <Wire.h>

// Include library for BMP388.
#include "libs/BMP388_DEV.h"

class Soldered_BMP388 : public BMP388_DEV
{
  public:
    uint8_t begin();

  protected:
  private:
};

#endif
