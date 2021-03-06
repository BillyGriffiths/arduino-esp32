#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// define some constants
#define VOLTAGE_PIN 35 //The pin we are reading voltage from
#define VOLTAGE_SAMPLES 10 //The number of samples we want to base our calculation on
#define VOLTAGE_CALCULATE_INTERVAL_MS 5000 //How often we want to refresh the battery voltage reading
#define SerialMon Serial

//define some variables
float batteryVoltage;

// define tasks
void calcBatteryVoltage(void * parameter);
void logBatteryVoltage(void * parameter);

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize serial communication at 115200 bits per second:
  SerialMon.begin(115200);
  delay(10);

  // the tasks to schedule:
    xTaskCreate (
        calcBatteryVoltage,     // The task
        "checkBatteryVoltage",  // A friendly "human readable" task name
        10000,                  // Stack size (memory allocation)
        NULL,                   // Parameters
        1,                      // Task priority
        NULL                    // Task handle
    );
    xTaskCreate (
        logBatteryVoltage,      // The task
        "logBatteryVoltage",    // A friendly "human readable" task name
        5000,                   // Stack size (memory allocation)
        NULL,                   // Parameters
        1,                      // Task priority
        NULL                    // Task handle
    );
 }

void loop()
{
  //nothing to do here, everything gets done in tasks
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

/**
 * Task logBatteryVoltage()
 *
 * Write the calculated battery voltage to serial
 */
void logBatteryVoltage(void * parameter)
{
    //do this forever
    for(;;)
    {
        if (batteryVoltage > 0) {
            SerialMon.println("[batteryVoltage] " + (String)batteryVoltage + "V");
        } else {
           SerialMon.println("[batteryVoltage] Waiting for measurement...");
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS); //write the calculated value to serial every 5 seconds
    }
}

/**
 * Task calcBatteryVoltage()
 *
 * Calculates the battery voltage
 */
void calcBatteryVoltage(void * parameter)
{
    //do this forever
    for(;;)
    {
        //take VOLTAGE_SAMPLES amount of samples and get the average
        int16_t avgReading = 0; //change this to (int32_t) if you increase VOLTAGE_SAMPLES
        for (int i = 0; i < VOLTAGE_SAMPLES; i++) {
          avgReading = avgReading + analogRead(VOLTAGE_PIN);
          delay(15);
        }
        avgReading = avgReading / VOLTAGE_SAMPLES;

        /*
         * Calculate the voltage based on our readings and write it to our globally defined variable float batteryVoltage
         *
         * After a lot of experimentation, this formula gave me the most accurate and
         * consistent results when compared to actual multimeter readings
         * Board: TTGO ESP32 SIM800L v1.3
         *
         * 3.3 : Operating voltage
         * 4095 : 12-bit ADC resolution - 1
         * 1.1 : Reference voltage
         * 2 : As per datasheet (double the reading)
         */
         batteryVoltage = ((3.3 / 4095) * avgReading) * 1.1 * 2;

          //do this again in VOLTAGE_CALCULATE_INTERVAL_MS seconds
          vTaskDelay(VOLTAGE_CALCULATE_INTERVAL_MS / portTICK_PERIOD_MS);
    }
}