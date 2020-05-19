#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// define some constants
#define BUTTON_PIN 12 //The pin the button is connected to
#define SerialMon Serial

// define tasks
void logKeyPressToSerial(void * parameter);

// define semaphore and interrupt function
SemaphoreHandle_t xBinarySemaphore;
void IRAM_ATTR interruptHandler() { //note the IRAM_ATTR
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken); //give a semaphore
}

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize serial communication at 115200 bits per second:
    SerialMon.begin(115200);
    delay(10);

    // set the button up as an interrupt - we're pulling it high internally just to make wiring simpler
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), interruptHandler, RISING);
    xBinarySemaphore = xSemaphoreCreateBinary();
    if (xBinarySemaphore == NULL) {
        Serial.println("[NOTICE] Semaphore could not be created");
    }

    //the tasks to schedule:
    xTaskCreate (
        logKeyPressToSerial,    // The task
        "logKeyPressToSerial",  // A friendly "human readable" task name
        5000,                   // Stack size (memory allocation)
        NULL,                   // Parameters
        1,                      // Task priority
        NULL                    // Task handle
    );

    Serial.println("[SETUP] Ready! Press the interrupt button.");
}

void loop()
{
  //nothing to do here, everything is done in tasks
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

/*
 * Task: logKeyPressToSerial
 *
 * Task remains in a blocked/delayed state indefinitely (portMAX_DELAY) until it has a semaphore to "take"
 * and it was taken successfully (== pdPASS). It then simply writes a keypress counter to serial.
 */
void logKeyPressToSerial( void * parameter )
{
    int numToDisplay = 0;
    for (;;) {
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdPASS) { //if semaphore successfully taken
            numToDisplay++;
            Serial.println("[logKeyPressToSerial] " + (String)numToDisplay);
        }
    }
    vTaskDelete(NULL);
}
