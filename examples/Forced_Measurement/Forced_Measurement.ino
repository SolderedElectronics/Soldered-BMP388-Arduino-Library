/**
 **************************************************
 *
 * @file        Forced_Measurement.ino
 * @brief       This example shows how to use forced measurement functionallity of
 *              the sensor. In other words, you can make measurement on demand. Between
 *              measuremetns, sensor will be in the sleep mode to save the power.
 *
 *              You can use easyC for I2C communication or I2C header (if using 5V board without
 *              easyC connector).
 *
 *              You will need:
 *              - BMP388 sensor breakout: https://solde.red/333316
 *              - easyC cable: https://solde.red/333311
 *
 * @authors     Borna Biro for soldered.com
 ***************************************************/

// Include Soldered BMP388 library.
#include <BMP388-SOLDERED.h>

// Create BMP388 sensor object.
Soldered_BMP388 bmp388;

void setup()
{
    // Initialize serial communication at 115200 bauds.
    Serial.begin(115200);

    // Initialize sensor (check for sensor). Notify if init failed.
    // Also, this will set BMP388 sensor into sleep mode.
    if (!bmp388.begin())
    {
        // Print error message.
        Serial.println("Sensor not found! Check your wiring!");

        // Stop the code!
        while (1)
        {
            // Delay for ESP8266.
            delay(10);
        }
    }

    // Set current pressure at sea level to get accurate altitude readings.
    bmp388.setSeaLevelPressure(1025.0);
}

void loop()
{
    // Variables for storing measurement data.
    float temperature, pressure, altitude;

    // Make a request for new measurement!
    bmp388.startForcedConversion();

    // Check if the measurement is complete.
    if (bmp388.getMeasurements(temperature, pressure, altitude))
    {
        // If the measurement is complete, print results.
        Serial.print(temperature);
        Serial.print(F("*C   "));
        Serial.print(pressure);
        Serial.print(F("hPa   "));
        Serial.print(altitude);
        Serial.println(F("m"));
    }

    // Wait a little bit.
    delay(1000);
}
