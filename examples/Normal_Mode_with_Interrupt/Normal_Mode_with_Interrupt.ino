/**
 **************************************************
 *
 * @file        Normal_Mode_with_Interrupt.ino
 * @brief       This example will use BMP388 interrupt pin to know
 *              when new measurement data is ready. This could
 *              be usefull for low power devices or to just do
 *              something else in the code while waiting for new
 *              measurement data.
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
// NOTE: ESP32 and ESP8266 use IRAM for ISR so if you are using ESP32 or ESP8266 uncomment
// this block of the code...
IRAM_ATTR void interruptHandler()
{
    // Set interrupt event flag.
    dataReady = true;
}
// ...and comment this block of code. Otherwise do the opposite.
// void interruptHandler()
// {
//     // Set interrupt event flag.
//     dataReady = true;
// }

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

    // Set D2 pin to input wuth pullup enabled.
    pinMode(2, INPUT_PULLUP);

    // Connect sensor INT pin to the D2. Call interruptHandler function in case of interrupt event.
    attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);

    // Set the standby time to roughly 1.3 seconds.
    bmp388.setTimeStandby(TIME_STANDBY_1280MS);

    // Start BMP388 continuous conversion in normal mode.
    bmp388.startNormalConversion();
}

void loop()
{
    // Variables for storing measurement data.
    float temperature, pressure, altitude;

    // Check if the interrupt event has occured (meaning the new data is ready).
    if (dataReady)
    {
        // Read the sensor data.
        bmp388.getMeasurements(temperature, pressure, altitude);

        // Printout measured data.
        Serial.print(temperature);
        Serial.print(F("*C   "));
        Serial.print(pressure);
        Serial.print(F("hPa   "));
        Serial.print(altitude);
        Serial.println(F("m"));

        // Clear the interrupt event flag (to be ready for next measurement).
        dataReady = false;
    }
}