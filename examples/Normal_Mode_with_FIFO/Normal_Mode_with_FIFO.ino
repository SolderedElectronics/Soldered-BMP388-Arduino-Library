/**
 **************************************************
 *
 * @file        Normal_Mode_with_FIFO.ino
 * @brief       This example will show how to use BMP388 built-in
 *
 *              You can use easyC for I2C communication.
 *              Alternatively, you can use jumper cables and header
 *              connection on the breakout if you are using 5V board.
 *
 *              Connect easyC cable to sensor and Dasduino board, upload
 *              the code and open serial monitor. After some time, measurement
 *              results should show.
 *
 *              You will need:
 *              - BMP388 sensor breakout: https://solde.red/
 *              - easyC cable: https://solde.red/333311
 *
 * @authors     Borna Biro for soldered.com
 ***************************************************/

// Include Soldered BMP388 library.
#include <BMP388-SOLDERED.h>

// Number of measurements to be stored in the FIFO.
#define NO_OF_MEASUREMENTS 10

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

    // Enable the BMP388's FIFO.
    bmp388.enableFIFO();

    // Store 10 measurements in the FIFO before reading. Can be changed by modifing NO_OF_MEASUREMENTS define macro.
    bmp388.setFIFONoOfMeasurements(NO_OF_MEASUREMENTS);

    // Set the standby time of each sample to be roughly 1.3 seconds.
    bmp388.setTimeStandby(TIME_STANDBY_1280MS);

    // Start BMP388 continuous conversion in normal mode.
    bmp388.startNormalConversion();

    // Print message for the user.
    Serial.println(F("Please wait for 13 seconds..."));
}

void loop()
{
    // Arrays to store measured data (array for temperature, pressure and altitude).
    float temperature[NO_OF_MEASUREMENTS];
    float pressure[NO_OF_MEASUREMENTS];
    float altitude[NO_OF_MEASUREMENTS];
    uint32_t sensorTime;

    // Check if the FIFO data is ready.
    // If the data is ready, get the 10 measurement readings.
    if (bmp388.getFIFOData(temperature, pressure, altitude, sensorTime))
    {
        // Print the results.
        for (uint16_t i = 0; i < NO_OF_MEASUREMENTS; i++)
        {
            Serial.print(i + 1);
            Serial.print(F(": "));
            Serial.print(temperature[i]);
            Serial.print(F("*C   "));
            Serial.print(pressure[i]);
            Serial.print(F("hPa   "));
            Serial.print(altitude[i]);
            Serial.println(F("m"));
        }

        // Print how long did it take to sample the measurement data into FIFO buffer.
        Serial.print(F("Sensor Time: "));
        Serial.println(sensorTime);
        Serial.println();

        // Print message for the user.
        Serial.println(F("Please wait for 13 seconds...")); // Wait message
    }
}
