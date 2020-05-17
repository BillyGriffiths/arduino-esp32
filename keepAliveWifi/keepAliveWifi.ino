#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

//include the wifi library
#include <WiFi.h>

// define some constants
#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"
#define WIFI_CHECK_INTERVAL_MS 10000 // How often to check if our WiFi connection is still alive
#define WIFI_TIMEOUT_MS 20000 // Amount of time to attempt a connection for (each attempt), before giving up
#define WIFI_RETRY_INTERVAL_MS 30000 // If no connection, how often do we want to attempt a connection.
#define SerialMon Serial

// define tasks
void keepAliveWifi(void * parameter);

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 115200 bits per second:
  SerialMon.begin(115200);
  delay(10);

  // the tasks to schedule:
  xTaskCreatePinnedToCore (
  keepAliveWifi,    // The task
  "keepAliveWifi",  // A friendly "human readable" task name
  5000,             // Stack size (memory allocation)
  NULL,             // Parameters
  1,                // Task priority
  NULL,             // Task handle
  0                 // Core assignment (We pin this to Core 0 as it is used by ESP32 radio functions)
  );

}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

/**
 * Task keepAliveWifi()
 *
 * Check and keep-alive the WiFi connection
 * Note: portTICK_PERIOD_MS =
 */
void keepAliveWifi(void * parameter)
{
    //do this forever
    for(;;)
    {
        //check the WiFi connection
        if (WiFi.status() == WL_CONNECTED){ //if we are connected
            vTaskDelay(WIFI_CHECK_INTERVAL_MS / portTICK_PERIOD_MS); //check again in WIFI_CHECK_INTERVAL_MS seconds
            continue;
        }

        //if not connected, attempt a connection
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.println("[keepAliveWifi] Connecting to " + (String)WIFI_SSID);

        //try connecting for WIFI_TIMEOUT_MS seconds before giving up
        unsigned long connectStartTime = millis();
        while (WiFi.status() != WL_CONNECTED && ((millis() - connectStartTime) < WIFI_TIMEOUT_MS)) {
          //visually indicate that we are busy trying. (remove the next 2 lines if you do not want the overhead)
          Serial.print(".");
          delay(500);
        }

        //if, after attempting to connect for WIFI_TIMEOUT_MS seconds, we still do not have a connection
        if (WiFi.status() != WL_CONNECTED) {
          Serial.println("");
          SerialMon.println("[keepAliveWifi] Connection failed. Retrying in " + (String)((int)WIFI_RETRY_INTERVAL_MS/1000) + " seconds.");
          vTaskDelay(WIFI_RETRY_INTERVAL_MS / portTICK_PERIOD_MS); //try again in WIFI_RETRY_INTERVAL_MS seconds
          continue;
        }

        //a successful connection was made, give us the IP
        Serial.println("");
        Serial.print("[keepAliveWifi] WiFi Connected. IP: ");
        Serial.print(WiFi.localIP());
    }
}