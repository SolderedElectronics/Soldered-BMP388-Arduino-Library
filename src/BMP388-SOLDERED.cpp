/**
 **************************************************
 *
 * @file        BMP388-SOLDERED.cpp
 * @brief       Soruce file for the BMP388 library wrapper.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Borna Biro for soldered.com
 ***************************************************/


#include "BMP388-SOLDERED.h"

/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Example parameter.
 */
uint8_t Soldered_BMP388::begin()
{
    return BMP388_DEV::begin(BMP388_I2C_ALT_ADDR);
}