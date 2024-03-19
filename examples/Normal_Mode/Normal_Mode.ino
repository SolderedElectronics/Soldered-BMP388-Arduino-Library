/**
 **************************************************
 *
 * @file        Normal_Mode.ino
 * @brief       This example will show basic usage of the BMP388
 *              sensor. It will periodically read BMP388 for new
 *              measured data.
 *
 *              Connect easyC cable to sensor and Dasduino board, upload
 *              the code and open serial monitor.
 *
 *              You will need:
 *              - BMP388 sensor breakout: https://solde.red/
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
    // Also, set BMP388 sensor into sleep mode.
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

    // Set the standby time of each sample to be roughly 1.3 seconds.
    bmp388.setTimeStandby(TIME_STANDBY_1280MS);

    // Start BMP388 continuous conversion in normal mode.
    bmp388.startNormalConversion();
}

void loop() 
{
    // Variables for storing measurement data.
    float temperature, pressure, altitude;

    // Check if the FIFO data is ready.
    if (bmp388.getMeasurements(temperature, pressure, altitude))
    {
        // Print the results.
        Serial.print(temperature);
        Serial.print(F("*C   "));
        Serial.print(pressure);    
        Serial.print(F("hPa   "));
        Serial.print(altitude);
        Serial.println(F("m"));  
    }

    // Wait a little bit.
    delay(250);
}
