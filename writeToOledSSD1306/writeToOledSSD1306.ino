#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// include the display and I2C libraries
#include "SSD1306.h"
#include <Wire.h>

// define some constants
#define I2C_OLED_ADDRESS 0x3c // The I2C address of the OLED. (Yours might differ)
#define I2C_SDA 21 // The I2C SDA pin the OLED is connected to (SDA<-->SDA)
#define I2C_SCL 22 // The I2C SCL pin the OLED is connected to (SCL<-->SCL)
#define SerialMon Serial

// connect to the display
SSD1306 display(I2C_OLED_ADDRESS, I2C_SDA, I2C_SCL);

// define tasks
void taskWriteToOLED(void * parameter);

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize serial communication at 115200 bits per second:
  SerialMon.begin(115200);
  delay(10);

  // initialize the display
  display.init();
  display.flipScreenVertically(); //remove this if your display output is upside down
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "Hi there!");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 27, "Counter starting...");
  display.display();

  // the tasks to schedule:
  xTaskCreatePinnedToCore (
        taskWriteToOLED,    // The task
        "taskWriteToOLED",  // A friendly "human readable" task name
        10000,              // Stack size (memory allocation)
        NULL,               // Parameters
        1,                  // Task priority
        NULL,               // Task handle
        1                   // Pin display tasks to Core 1. Core 0 can sometimes be finicky as it has other priorities.
   );
}

void loop()
{
  //nothing to do here, everything is done in tasks
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

/*
*  Task: taskWriteToOLED
*
*  Wait 2 seconds and then start counting up from 0 to 60 repetitively
*/
void taskWriteToOLED( void * parameter )
{
    //wait 2 seconds - just to be nice and say "Hi there! before we start showing numbers
    vTaskDelay(2000 / portTICK_PERIOD_MS);; //

    int counter = 0;

    //do this forever
    for (;;) {
        counter++;
        if (counter > 60) { //lets limit the counter to 60
            counter = 0;
        }

        //clear the display and write the new value
        display.clear();
        display.setFont(ArialMT_Plain_24);
        display.drawString(0, 0, (String)counter);
        display.display();

        // delay the next task execution
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}