# ESP32 - buttonInterruptSemaphore

An example of how to create an interrupt button using the ESP32, Arduino IDE and FreeRTOS. 

A single momentary button, mapped as an interrupt, using a semaphore to run a task that is in a perpetual blocked/delayed state.  
 
Example of serial output: 

```
19:00:04.934 -> [SETUP] Ready! Press the interrupt button.
19:00:08.934 -> [logKeyPressToSerial] 1
19:00:09.538 -> [logKeyPressToSerial] 2
19:00:09.979 -> [logKeyPressToSerial] 3
19:00:10.438 -> [logKeyPressToSerial] 4
19:00:10.877 -> [logKeyPressToSerial] 5
19:00:11.280 -> [logKeyPressToSerial] 6
19:00:11.678 -> [logKeyPressToSerial] 7
19:00:12.071 -> [logKeyPressToSerial] 8
19:00:12.531 -> [logKeyPressToSerial] 9
19:00:12.926 -> [logKeyPressToSerial] 10
19:00:13.380 -> [logKeyPressToSerial] 11
19:00:13.804 -> [logKeyPressToSerial] 12
19:00:14.241 -> [logKeyPressToSerial] 13

```