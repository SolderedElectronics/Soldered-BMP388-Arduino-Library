/**
 **************************************************
 *
 * @file        ESP8266_Normal_Mode_with_Defined_Pins.ino
 * @brief       This example shows how to use ESP8266 (Soldered DasduinoCONNECT) with this sensor.
 *              Since ESP8266 has SW driven I2C, it can have I2C on almost any GPIO.
 *              This could be useful if there are device with the same I2C address as this sensor on
 *              default I2C pins.
 *
 *              Using jumper wires, connect:
 *                 BMP388                   DasduinoCONNECT
 *                    GND <---------------> GND
 *                    VCC <---------------> VCC
 *                    SDA <---------------> GPIO14
 *                    SCL <---------------> GPIO13
 *
 *              You will need:
 *              - BMP388 sensor breakout: https://solde.red/333316
 *              - Jumper cables: https://solde.red/100862
 *              - Breadboard: https://solde.red/100871
 *
 * @authors     Borna Biro for soldered.com
 ***************************************************/

// Include Soldered BMP388 library.
#include <BMP388-SOLDERED.h>

// Create BMP388 sensor object. Use GPIO14 as SDA and GPIO13 as I2C SCL.
Soldered_BMP388 bmp388(14, 13, Wire);

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

    // Set the standby time of each sample to be roughly 1.3 seconds.
    bmp388.setTimeStandby(TIME_STANDBY_1280MS);

    // Start BMP388 continuous conversion in normal mode.
    bmp388.startNormalConversion();
}

void loop()
{
    // Variables for storing measurement data.
    float temperature, pressure, altitude;

    // Check if the data is ready.
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
