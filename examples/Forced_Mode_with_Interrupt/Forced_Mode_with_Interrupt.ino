/**
 **************************************************
 *
 * @file        Forced_Mode_with_Interrupt.ino
 * @brief       This example will show how to use BMP388 sensor with forced mode
 *              in combination with interrupts. Code will trigger forced measurement
 *              of the temperature and pressure and instead of waiting for conversion, it will
 *              receive interrupt event to know that new measurements are ready.
 *
 *              This could be usefull for low power devices or to just do something else
 *              in the code while waiting for new measurement data.
 *
 *              You can use easyC for I2C communication and a jumper
 *              wire for interrupt line.
 *
 *              Connect BMP388 INT pin to D2 if using Dasduino Core.
 *              For other Dasduino boards, you will need to modify
 *              pinMode and attachInterrupt functions.
 *
 *              You will need:
 *              - BMP388 sensor breakout: https://solde.red/333316
 *              - easyC cable: https://solde.red/333311
 *              - Jumper cables: https://solde.red/100862
 *              - Breadboard: https://solde.red/100871
 *
 * @authors     Borna Biro for soldered.com
 ***************************************************/

// Include Soldered BMP388 library.
#include <BMP388-SOLDERED.h>

// Flag for interrupt event.
volatile boolean dataReady = false;

// Create BMP388 sensor object.
Soldered_BMP388 bmp388;

// Interrupt handler function - It's called on interrput event.
// NOTE: ESP32 and ESP8266 use IRAM for ISR so it needs to be specified.
#if defined(ARDUINO_ESP32_DEV) || defined(ARDUINO_ESP8266_GENERIC)
IRAM_ATTR void interruptHandler()
{
    // Set interrupt event flag.
    dataReady = true;
}
#else
void interruptHandler()
{
    // Set interrupt event flag.
    dataReady = true;
}
#endif

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

    // Enable sensor interrupts.
    bmp388.enableInterrupt();

    // Connect sensor INT pin to the D2. Call interruptHandler function in case of interrupt event.
    attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);
}

void loop()
{
    // Variables for storing measurement data.
    float temperature, pressure, altitude;

    // Make a request for new measurement!
    bmp388.startForcedConversion();

    // Check if the new data is ready by reading interrupt event flag.
    // If the flag is set to true - new data is available, read it!
    if (dataReady)
    {
        // Get the new data from the sensor.
        bmp388.getMeasurements(temperature, pressure, altitude);

        // Print the results!
        Serial.print(temperature);
        Serial.print(F("*C   "));
        Serial.print(pressure);
        Serial.print(F("hPa   "));
        Serial.print(altitude);
        Serial.println(F("m"));

        // Clear the interrupt event flag (to be ready for next measurement).
        dataReady = false; // Clear the dataReady flag
    }
}