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
 * @brief                   BMP388 library initializer function.
 *
 * @return                  uint8_t - Success initializaton of the sensor.
 *                          1 - Sensor successfully initialized.
 *                          0 - Sensor initialization falied.
 */
uint8_t Soldered_BMP388::begin()
{
    // Call library specific init. function with 0x76 I2C address.
    return BMP388_DEV::begin(BMP388_I2C_ALT_ADDR);
}